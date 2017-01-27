// QueryDialog.h : main header file for the QUERYDIALOG application
//

#if !defined(AFX_QUERYDIALOG_H__5F35AA02_CD11_11D2_A8F0_002048088976__INCLUDED_)
#define AFX_QUERYDIALOG_H__5F35AA02_CD11_11D2_A8F0_002048088976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQueryDialogApp:
// See QueryDialog.cpp for the implementation of this class
//

class CQueryDialogApp : public CWinApp
{
public:
	CQueryDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQueryDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYDIALOG_H__5F35AA02_CD11_11D2_A8F0_002048088976__INCLUDED_)
