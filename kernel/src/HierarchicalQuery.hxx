
#ifndef _HIERARCHICAL_QUERY
#define _HIERARCHICAL_QUERY
#include "KernelInterface.hxx"
#include "SOPClasses.hxx"

#ifdef _MSC_VER
#include <afxdb.h>
#endif /* _MSC_VER */

#include "PatientSet.h"
#include "StudySet.h"
#include "SeriesSet.h"
#include "ImageSet.h"

// very successful derivation..really like this one
class UIList:public UIv{
public:
  string toString()const {
    string str = "";
    if (!empty()) {
      const_iterator i = begin(), j = end();
      str += string("'")+i->toString()+string("'");
      i++;
      for (; i!=j ; i++)
	str += string(",") + i->toString();
    }
    return str ;
  }
};

// here we go, we wish to decouple all info from our DICOM object system
// these should have been nested VC50 bug again
class Patient_Info {
public:
  string patient_id;
  string patient_name;
  string patient_surname;
};

class Study_Info {
public:
  CTime study_date;
  string study_time;
  string accession_number;
  string study_id;
  string study_instance_uid;
};

class Series_Info {
public:
  string series_instance_uid;
  string modality;
  string series_number;
};

class Image_Info {
public:
  int image_number;
  string sop_instance_uid;
};


// this is a great class, but a bit messed up
class Hierarchical_Query
{
public:

  // always think of a class as something which has a temporary memory
  list<Patient_Info> patient_info_list;
  list<Study_Info> study_info_list;
  list<Series_Info> series_info_list;
  list<Image_Info> image_info_list;

  Hierarchical_Query() {infoModel=NULL; db_name="RAGARISDB";};
  ~Hierarchical_Query() {if (m_dbRagaris.IsOpen()) m_dbRagaris.Close();};
  inline void set_database_params(CString DbName, CString ULogin, CString UPwd){db_name=DbName;login_name=ULogin;pass_wd=UPwd;};
  void SetInfoModel(SOP*);
  void SetSQL(CString);
  CString PatientRootQueryStr(CString[]);
  void fetch();

  CString PatientRootQuery(void);
	
protected:
  void fetch_image();
  void fetch_series();
  void fetch_study();
  void fetch_patient();

  CString ListStrUID(CString );
  CString ListUID(UIv, CString);
  CString DateSQL(rangeDA, CString);
  CString TimeSQL(rangeTM, CString);
  CString SingleSQL(CString, CString);
  CString WildSQL(CString, CString);	

  CString TimeSQLStr(CString,CString, CString);
  CString ListUIDtoStr(CString);
  CString ListUIDStr(CString, CString);
  CString DateSQLStr(CString,CString,CString);

  void DateToStr(rangeDA, CString*, CString*);
  void TimeToStr(rangeTM, CString*, CString*);
  /*
    CString StudyRootQuery(*);
    CString PatientStudyQuery(*);
  */
  // cool, but inline keyword is kinda outdated
  inline CDatabase* ReturnDB() {return &m_dbRagaris;};
  inline BOOL IsConnected() const {return (m_dbRagaris.IsOpen());};
  inline BOOL ConnectDB(CString ULogin, CString UPwd) {return (m_dbRagaris.OpenEx(_T("DSN=RAGARISDB;UID=" + ULogin + ";PWD=" + UPwd),CDatabase::useCursorLib));};
  inline void ExecuteSql(CString & theSql) {AfxMessageBox(theSql); m_dbRagaris.ExecuteSQL(theSql);};

  CString db_name;
  CString login_name;
  CString pass_wd;
  CString SQL_str;
  CString hierarchy_level;
  CDatabase m_dbRagaris;
  SOP *infoModel;

};
#endif
