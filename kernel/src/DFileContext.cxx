/*
**
** Implementation file for DContext module
**
**
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif

#include "KernelInterface.hxx"
#include <DICOMFileMetaInformationMod.hxx>
#include "SOPClasses.hxx"

DFileContext::DFileContext(const string & s) : filename(s), header_read(false)
{
}

#ifdef _MSC_VER
DFileContext::DFileContext(CString & s) : filename( string((LPCTSTR)s) ), header_read(false)
{
}
#endif

const DFileHeader& DFileContext::sel_header()
{
  if (!header_read) {
    DBinaryFileStream stream(filename, DStream::input);
    read_header(stream, header);
    header_read = true;
  }
  return header;
}

// construct and return a new SOP instance as read from associated file
SOP& DFileContext::read()
{
  try {

    // open a file association
    DBinaryFileStream stream(filename, DStream::input);
		
    //DFileHeader header;
    read_header(stream, header);
    header_read = true;

    const UI& class_uid = header.class_id;
    const UI& instance_uid = header.instance_id;
    const UI& ts_uid = header.ts_id;

    // construct an SOP instance with Class UID class_uid, from representative object
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    SOP & sop = dicom_app.sops[class_uid]->gen(instance_uid);
		
    // decode object
    sop.decode(stream, ts_uid);
		
    return sop;
  }
  catch (DException e) {
    e.why();
    throw DException("DFileContext: error reading file");
  }
#ifdef _MSC_VER
  catch (CException e) {
    e.ReportError();
    throw DException("DFileContext: error reading file");
  }
#endif // _MSC_VER
}


// write an SOP instance into the associated file
void DFileContext::write(SOP& sop)
{
  try {
    // open a file association
    DBinaryFileStream stream(filename, DStream::output);
		
    // encode file header, obtain necessary information

    char buffer[256];
    long *buf = (long*)&buffer;
    for (int i=128/sizeof(long); i>0; i--)
      *(buf++) = 0;
    char *dicm_kw = "DICM";
		
    // file preamble
    stream.write(buffer, 128);
    stream.write(dicm_kw, 4);

    // encode file meta information
    AbstractSOPCommonMod& sopcommon = dynamic_cast<AbstractSOPCommonMod&>(sop);
    const UI& class_uid = sopcommon.selSOPClassUID();
    const UI& instance_uid = sopcommon.selSOPInstanceUID();
    const UI& ts_uid = ImplicitVRLittleEndian::UID;

    DICOMFileMetaInformationMod fileinfo;
    OB & ver = fileinfo.refFileMetaInformationVersion();
    ver.resize(2);
    ver[0] = 0; ver[1] = 1;
    fileinfo.modMediaStorageSOPClassUID(class_uid);
    fileinfo.modMediaStorageSOPInstanceUID(instance_uid);
    fileinfo.modTransferSyntaxUID(ts_uid);
    fileinfo.modImplementationClassUID(dicom_app.implementation_uid);
    fileinfo.modImplementationVersionName(dicom_app.implementation_version_name);
    fileinfo.modSourceApplicationEntityTitle(dicom_app.ae_title);

    DICOMFileMetaInformationMod::Coder<ExplicitVRLittleEndian> infocoder;
    infocoder.encode(stream, fileinfo);

    int offset = stream.position;

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // encode object
    sop.encode(stream, ts_uid);
		
    // fix the group length attribute
    // do it by the book...
    stream.position_write_head(0x8c);
    ExplicitVRLittleEndian::encode_long(stream, offset-0x90);
  }
  catch (DException e) {
    e.why();
    throw DException("DFileContext: error writing file");
  }

}

// write an SOP instance into the associated file with given TS UID
void DFileContext::write(SOP& sop, string ts_uid)
{
  try {
    // open a file association
    DBinaryFileStream stream(filename, DStream::output);
		
    // encode file header, obtain necessary information

    char buffer[256];
    long *buf = (long*)&buffer;
    for (int i=128/sizeof(long); i>0; i--)
      *(buf++) = 0;
    char *dicm_kw = "DICM";
		
    // file preamble
    stream.write(buffer, 128);
    stream.write(dicm_kw, 4);

    // encode file meta information
    AbstractSOPCommonMod& sopcommon = dynamic_cast<AbstractSOPCommonMod&>(sop);
    const UI& class_uid = sopcommon.selSOPClassUID();
    const UI& instance_uid = sopcommon.selSOPInstanceUID();
 
    DICOMFileMetaInformationMod fileinfo;
    OB & ver = fileinfo.refFileMetaInformationVersion();
    ver.resize(2);
    ver[0] = 0; ver[1] = 1;
    fileinfo.modMediaStorageSOPClassUID(class_uid);
    fileinfo.modMediaStorageSOPInstanceUID(instance_uid);
    fileinfo.modTransferSyntaxUID(ts_uid);
    fileinfo.modImplementationClassUID(dicom_app.implementation_uid);
    fileinfo.modImplementationVersionName(dicom_app.implementation_version_name);
    fileinfo.modSourceApplicationEntityTitle(dicom_app.ae_title);

    DICOMFileMetaInformationMod::Coder<ExplicitVRLittleEndian> infocoder;
    infocoder.encode(stream, fileinfo);

    int offset = stream.position;

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // encode object
    sop.encode(stream, ts_uid);
		
    // fix the group length attribute
    // do it by the book...
    stream.position_write_head(0x8c);
    ExplicitVRLittleEndian::encode_long(stream, offset-0x90);
  }
  catch (DException e) {
    e.why();
    throw DException("DFileContext: error writing file");
  }

}


// write an ImplicitVRLittleEndian image of an SOP instance
// to a dicom file with a specified length
void DFileContext::write(const UI& class_uid, const UI& instance_uid,
			 char* image, int image_length)
{
  try {
    // open a file association
    DBinaryFileStream stream(filename, DStream::output);
		
    // encode file header

    char buffer[256];
    long *buf = (long*)&buffer;
    for (int i=128/sizeof(long); i>0; i--)
      *(buf++) = 0;
    char *dicm_kw = "DICM";
		
    // file preamble
    stream.write(buffer, 128);
    stream.write(dicm_kw, 4);

    // encode file meta information
    const UI& ts_uid = ImplicitVRLittleEndian::UID;

    DICOMFileMetaInformationMod fileinfo;
    OB & ver = fileinfo.refFileMetaInformationVersion();
    ver.resize(2);
    ver[0] = 0; ver[1] = 1;
    fileinfo.modMediaStorageSOPClassUID(class_uid);
    fileinfo.modMediaStorageSOPInstanceUID(instance_uid);
    fileinfo.modTransferSyntaxUID(ts_uid);
    fileinfo.modImplementationClassUID(dicom_app.implementation_uid);
    fileinfo.modImplementationVersionName(dicom_app.implementation_version_name);
    fileinfo.modSourceApplicationEntityTitle(dicom_app.ae_title);

    DICOMFileMetaInformationMod::Coder<ExplicitVRLittleEndian> infocoder;
    infocoder.encode(stream, fileinfo);

    int offset = stream.position;

    // check validity of SOP class
    if (dicom_app.sops.find(class_uid) == dicom_app.sops.end())
      throw DException("Unknown SOP Class UID");

    // encode object
    stream.write(image, image_length);
		
    // fix the group length attribute
    // do it by the book...
    stream.position_write_head(0x8c);
    ExplicitVRLittleEndian::encode_long(stream, offset-0x90);
  }
  catch (DException e) {
    e.why();
    throw DException("DFileContext: error writing file");
  }

}

void DFileContext::read_header(DFileHeader& header)
{
  try {

    // open a file association
    DBinaryFileStream stream(filename, DStream::input);
		
    read_header(stream, header);

  }
  catch (DException e) {
    e.why();
    throw DException("DFileContext: error reading file");
  }

}

void DFileContext::read_header(DStream & stream, DFileHeader& header)
{
  // decode file header, obtain necessary information

  char buffer[256];

  // file preamble
  stream.read((char*)buffer, 128);

  stream.read((char*)buffer, 4);
  string dicm; dicm.assign((char*)buffer, 4);

  if (dicm != "DICM") {
    throw DException(filename + ": file format is not DICOM compliant");
  }

  // decode file meta information
  DICOMFileMetaInformationMod fileinfo;
  DICOMFileMetaInformationMod::Coder<ExplicitVRLittleEndian> infocoder;
  infocoder.decode(stream, fileinfo);

  header.class_id = fileinfo.selMediaStorageSOPClassUID();
  header.instance_id = fileinfo.selMediaStorageSOPInstanceUID();
  header.ts_id = fileinfo.selTransferSyntaxUID();
}

void DFileContext::write_header(DStream & stream, DFileHeader& header)
{
}
