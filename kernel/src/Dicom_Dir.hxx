/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef Dicom_Dir_Interface
#define Dicom_Dir_Interface

#include "General.hxx"

struct File_Info {

	string patient_id;
	PN patient_name;
	UI study_instance_uid;
	string study_id;
	UI series_instance_uid;
	int series_number;
	UI sop_class_uid;
	UI sop_instance_uid;
  UI transfer_syntax_uid;
	int image_number;

	string modality;
	string pathname; // where's the file?
};

inline bool operator ==(File_Info a, File_Info b) {return false;}
inline bool operator !=(File_Info a, File_Info b) {return false;}
inline bool operator <(File_Info a, File_Info b) {return false;}
inline bool operator >(File_Info a, File_Info b) {return false;}

class Dicom_Dir {
public:
	Dicom_Dir(string root_path);

	const list<File_Info>& sel_dir_contents();
private:
	list<File_Info> dir_contents;
};

#endif
