#ifndef PLATFORM_DICOMCONSOLEDLG
#define PLATFORM_DICOMCONSOLEDLG

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// DicomConsoleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DicomConsoleDlg dialog

#ifdef _MSC_VER

#include "StdAfx.h"
#include "platform/res/MEDIC Resources.h"

class CDicomConsoleDlg : public CDialog
{
 public:
  enum { report_buffer_size = 1024 };

  // Construction
 public:
  void Report(const CString& s);
  CDicomConsoleDlg(CWnd* pParent = NULL);   // standard constructor

  // Dialog Data
  //{{AFX_DATA(CDicomConsoleDlg)
  enum { IDD = IDD_DICOMCONSOLE };
  // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA


  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDicomConsoleDlg)
 protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

  // Implementation
 protected:

  // Generated message map functions
  //{{AFX_MSG(CDicomConsoleDlg)
  // NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
    };

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#else

class CDicomConsoleDlg
{
 public:
  enum { report_buffer_size = 1024 };

 public:
  void Report(const string& s);
};

#endif

#endif
