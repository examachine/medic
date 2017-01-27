/*
** Interface file for DICOM File Context module
**
**
**
** exa
**
*/

#ifndef MEDIC_FileContext_Interface
#define MEDIC_FileContext_Interface 1

#include "General.hxx"
#include "DContext.hxx"
#include "DBinaryFileStream.hxx"
#include "SOP.hxx"

class DFileHeader
{
public:
  UI class_id;
  UI instance_id;
  UI ts_id;
};

class DFileContext : public DContext {
public:

  DFileContext(const string & s);
#ifdef _MSC_VER
  DFileContext(CString & s);
#endif // _MSC_VER

  // construct and return a new SOP instance as read from associated file
  SOP& read();

  // write an SOP instance into the associated file with default TS: implicit vr little endian
  void write(SOP&);

  // write an SOP class with a given transfer syntax
  void write(SOP&, string ts_uid);

  // best guess?
  void write(const UI& class_uid, const UI& instance_uid,
	     char* image, int image_length);

  void read_header(DFileHeader& header);
  void read_header(DStream & stream, DFileHeader& header);
  void write_header(DStream & stream, DFileHeader& header);

  string filename;

  const DFileHeader& sel_header();
	
private:
  DFileHeader header;
  bool header_read;
};

#endif
