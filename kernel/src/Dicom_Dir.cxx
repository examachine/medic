/*
**
** Implementation file for module
**
**
**
** exa
**
*/

#include "KernelInterface.hxx"

#include "SOPClasses.hxx"

class CustomStream : public DBinaryFileStream {
public:
  CustomStream(string fn) : DBinaryFileStream(fn, input) {}
  void position_read_head(int pos) {
    seekg(pos);
    forward(pos);
  }
};

typedef AbstractDirectoryInformationMod::DirectoryRecordSequence_t RecSeq;
typedef AbstractDirectoryInformationMod::DirectoryRecordSequence_t::iterator it;
typedef AbstractDirectoryInformationMod::DirectoryRecordSequence_t::value_type Rec;

class Traverser {
public:
  Traverser(list<File_Info> & f, string r) : file_list(f), root_path(r), num_nodes(0) {}
	
  //Offset_Map & offset_map;
  list<File_Info> & file_list;
  string root_path;
  File_Info file_info;
	
  int num_nodes;
	
  // process a given record, and iterate depth first
  void traverse(Rec & rec) {
		
    num_nodes++;
		
    if (*rec.selRecordInUseFlag()==0xFFFF) { // record in use
      //dicom_app.report(*rec_it->selDirectoryRecordType());
      string dir_type = *rec.selDirectoryRecordType();
      if (dir_type =="PATIENT") {
	dicom_app.report( string("Got patient ") + *rec.selPatientsName() ); 
	file_info.patient_id = *rec.selPatientID();
	file_info.patient_name = *rec.selPatientsName();
	traverse_lower_level(rec);
      }
      else if (dir_type == "STUDY") {
	file_info.study_instance_uid = rec.selStudyInstanceUID();
	file_info.study_id = *rec.selStudyID();
	dicom_app.report( string("Got study ") + file_info.study_id); 
	traverse_lower_level(rec);
      }
      else if (dir_type == "SERIES") {
	file_info.series_instance_uid = rec.selSeriesInstanceUID();
	file_info.series_number = *rec.selSeriesNumber();
	file_info.modality = *rec.selModality();
	dicom_app.report( string("Got series ") + int_to_str(file_info.series_number) );
	traverse_lower_level(rec);
      }
      else if (dir_type == "MRDR") {
	dicom_app.report( "Got MRDR, not supported "); 
      }
      //KLUDGE: ain't this a dirty hack to read those scum CDs ?
      else if (dir_type == "IMAGE" || dir_type == "PRIVATE") {
	// form pathname
	string pathname = root_path;
	CSr<0x0001,0x0008>::iterator fileid_it = rec.refReferencedFileID().begin(),
	  fileid_it_end = rec.refReferencedFileID().end();
	for (; fileid_it != fileid_it_end; fileid_it++, pathname += '\\' )
	  pathname += **fileid_it;
	pathname.erase(pathname.size()-1);
	file_info.pathname = pathname;
	file_info.sop_class_uid = rec.selReferencedSOPClassUIDInFile();
	file_info.sop_instance_uid = rec.selReferencedSOPInstanceUIDInFile();
	file_info.transfer_syntax_uid = rec.selReferencedTransferSyntaxUIDInFile();
	file_info.image_number = *rec.selImageNumber();
	dicom_app.report( string("Got image ") + int_to_str(file_info.image_number) ); 
	//CODE: add Icon Image Sequence
	file_list.push_back(file_info);
      }
      unsigned int offset_next = *rec.selOffsetOfTheNextDirectoryRecord();
      if (offset_next != 0) traverse(offset_next); // finish off the sibling records as well
    }
  }
	
  // Go to a lower level in the hierarchy
  void traverse_lower_level(Rec & rec) {
    unsigned int offset_next;
    unsigned int offset_lower = *rec.selOffsetOfTheReferencedLowerLevelDirectoryEntity();
    //dicom_app.report("Lower");
    traverse(offset_lower); // go depth
    offset_next = *rec.selOffsetOfTheNextDirectoryRecord();
    //dicom_app.report("Next");
    traverse(offset_next); // go sibling
  }
  void traverse(unsigned int offset) {
    if (offset!=0) // is there one actually ?
      {					
	dicom_app.report(string("Offset: ") + int_to_hexstr(offset));
	typedef AbstractDirectoryInformationMod::DirectoryRecordSequence_t RecSeq;
	typedef AbstractDirectoryInformationMod::DirectoryRecordSequence_t::value_type Rec;
	Rec item;
	try {
	  // read rec at offset
	  CustomStream d(root_path + "DICOMDIR");
	  d.position_read_head(offset);
	  // decode item
	  // BUG: probable VC bug, typenames banish
	  RecSeq::Coder<ExplicitVRLittleEndian> coder;
	  coder.decode_item(d, item);
	}
	catch (DException e) {
	  e.why();
	  throw e;
	}
	traverse(item);
      }
  }
};

Dicom_Dir::Dicom_Dir(string root_path)
{
  try {
    dicom_app.report("Reading DICOM directory at " + root_path);
    DFileContext d(root_path + "DICOMDIR");
    MediaStorageDirectoryStorage & dir = 
      dynamic_cast<MediaStorageDirectoryStorage &>(d.read());
    AbstractDirectoryInformationMod::DirectoryRecordSequence_t::const_iterator
      rec_it = dir.selDirectoryRecordSequence().begin(),
      rec_it_end = dir.selDirectoryRecordSequence().end();
    //CODE: add SOP Instance UID of DICOMDIR as File-Set UID value
    //CODE: add File-set ID and File-set Descriptor File ID attributes
    // from FileSetIdentification Module. It might be great to display those

    //typedef map<unsigned int, it> Offset_Map;
    //Offset_Map offset_map;
		
    /*
      unsigned int offset_next = 0;
      for (; rec_it != rec_it_end; rec_it++) {
      dicom_app.report(string("offset: ") + int_to_hexstr(offset_next)); 
      offset_map[offset_next] = rec_it;
      offset_next = *rec_it->selOffsetOfTheNextDirectoryRecord();
      }
    */
		
    rec_it = dir.selDirectoryRecordSequence().begin();
    rec_it_end = dir.selDirectoryRecordSequence().end();
    Traverser traverser(dir_contents, root_path);
    // for all 
    dicom_app.report("Dir size: " + int_to_str(dir.selDirectoryRecordSequence().size()));
    traverser.traverse(*dir.refDirectoryRecordSequence().begin());
    dicom_app.report("Extracted size: " + int_to_str(dir_contents.size()));
  }
  catch (DException e) {
    e.why();
    throw e;
  }
}

const list<File_Info>& Dicom_Dir::sel_dir_contents()
{
  return dir_contents;
}
