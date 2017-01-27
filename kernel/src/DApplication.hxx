/*
** Interface file for DApplication module
**
** Abstracts DICOM Application Entities
**
** exa
**
*/

#ifndef Kernel_DICOM_Application_Interface
#define Kernel_DICOM_Application_Interface 1

#include "General.hxx"
#include "SOP.hxx"
#include "StorageManager.hxx"
#include <DicomConsoleDlg.h>

// Abstraction for a DICOM Application Entity
// Only a single instance per application is permitted

//class ListenerThread;
#include <ListenerThread.h>
class Thread;

class DApplication
{
public:
  enum { default_dicom_port = 104 };
  enum Role { viewing_application, archive_application };

  struct DAEInfo
  {
    string address;
    int port;
  };

  DApplication();

  void init_class(Role _role = viewing_application,
		  Thread* image_manager = NULL,
		  const string & obj_pool_dir = "");

  void read_config();
  void write_config();

  SOPs sops;
  //TransferSyntaxes transfer_syntaxes;
  StorageManager storage_manager;

  void report(const char *s) { report(string(s)); }
  void report(const string & s);
#ifdef _MSC_VER
  void report(CString s);
#endif // _MSC_VER

  void show_console();
  void hide_console();

  string sop_filename( const UI& );
  void exit(bool = false);

  Role role;
  UI implementation_uid;
  SH implementation_version_name;
  AE ae_title;
  int dicom_port;

  map<AE, DAEInfo> address_book;
  string object_pool_dir; // the directory where SOP instances go into

  string uid_org_root;
  string serial_number;
  string uid_suffix;

#ifndef _MSC_VER
  ListenerThread* listening_thread;
#else
  CListenerThread* listening_thread;
#endif

#ifdef MEDIC_PACS
  DImageStacker image_stacker;
#endif

  bool subsytem_initialized;
private:
  static void exception_handler();
#ifdef _MSC_VER
  CDicomConsoleDlg dicom_console;
#endif
};

extern DApplication dicom_app;

#endif
