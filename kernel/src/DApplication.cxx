/*
**
** Implementation file for DApplication module
**
**
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#include "dcl application.h"
#endif // _MSC_VER

//#include "KernelInterface.hxx"
//#include "SOPClasses.hxx"
#include <Thread>

#include "DApplication.hxx"
#include <ListenerThread.h>


DApplication dicom_app;

DApplication::DApplication()
  : implementation_uid("1.2.840.69"),
    implementation_version_name("MEDIC_01"),
    uid_org_root("1.2.840.696969")
{

}


// CODE: check whether the object_pool_dir is valid
void DApplication::init_class( Role _role, Thread* image_manager,
			       const string & obj_pool_dir)
{
  set_unexpected(exception_handler);
  set_terminate(exception_handler);

#ifdef _MSC_VER
#define IDP_SOCKETS_INIT_FAILED         103

  if (!AfxSocketInit())
    {
      AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
    }

  // initialize console
  dicom_console.Create(IDD_DICOMCONSOLE /*, AfxGetMainWnd()*/ );
  //SetWindowLong( dicom_console.m_hWnd, GWL_STYLE, WS_POPUP);
		
  CListBox * list = (CListBox*) dicom_console.GetDlgItem(IDC_DICOM_REPORTS);
  list->InitStorage(CDicomConsoleDlg::report_buffer_size, CDicomConsoleDlg::report_buffer_size*96);

  // don't show dicom console at startup
  dicom_console.ShowWindow(FALSE);	
#endif // _MSC_VER

  role = _role;

#ifdef MEDIC_PACS
  if (image_manager)
    image_stacker.image_manager = image_manager;
#endif MEDIC_PACS

  if (obj_pool_dir.size()!=0)
    object_pool_dir = obj_pool_dir;
  else
    if (role == archive_application)
      object_pool_dir = "//POSEIDON/STA/";
    else
      object_pool_dir = "object-pool/";
		
  read_config();

  // UID suffix
  uid_suffix = uid_org_root + ".455841." + serial_number;

  sops.init_class(); // initialize SOP classes

  // init virtual memory
  storage_manager.init_class();

  // initialize listening thread
#ifndef _MSC_VER
  // CODE: do it for POSIX
#else
  listening_thread = (CListenerThread*)AfxBeginThread(RUNTIME_CLASS(CListenerThread),
						      THREAD_PRIORITY_NORMAL, 0, 0);
#endif

}

void DApplication::read_config()
{
  // Read config files
  try {
    ifstream ae_title_file("etc/ae-config.txt");
    string ae;
    ae_title_file >> ae;
    ae_title = AE(ae);
    ae_title_file >> dicom_port;
    ae_title_file >> serial_number;
    ae_title_file.close();

    ifstream addy_file("etc/dicom-AEs.txt");
    while (!addy_file.eof()) {
      string ae, address;
      int port;
      addy_file >> ae >> address >> port;
      if ((ae.size()==0) || (address.size()==0)) break;
      address_book[AE(ae)].address = address;
      address_book[AE(ae)].port = port;
    }
    addy_file.close();
  }
  catch (DException e) {
    e.why();
    exit();
  }
  catch (...) {
    DException err("Error while accessing config file in ./etc");
    err.why();
    exit();
  }
}

//CODE: write config files
void DApplication::write_config()
{
}

void DApplication::report(const string & s)
{
  cout << s; // CODE: better next time ;)
#ifdef _MSC_VER
  dicom_console.Report(s.c_str());
#endif
}

#ifdef _MSC_VER

void DApplication::report(CString s)
{
  dicom_console.Report(s);
}

#endif

void DApplication::show_console()
{
#ifdef _MSC_VER
  dicom_console.ShowWindow(SW_SHOW);
#endif _MSC_VER
}

void DApplication::hide_console()
{
#ifdef _MSC_VER
  dicom_console.ShowWindow(SW_HIDE);
#endif _MSC_VER
}

void DApplication::exit(bool success)
{
  if (!success) {
#ifdef _MSC_VER
    AfxMessageBox("Fatal errror, terminating application");
#endif _MSC_VER
    ::exit(-1);
  }
  ::exit(0);
}

void DApplication::exception_handler()
{
  cerr << " An exception has been thrown. " << endl;
  dicom_app.exit();
}

string DApplication::sop_filename(const UI& uid)
{
  return object_pool_dir + ((UI&)uid).rep();
}
