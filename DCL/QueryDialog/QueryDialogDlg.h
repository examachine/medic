
// QueryDialogDlg.h : header file
//

#if !defined(AFX_QUERYDIALOGDLG_H__5F35AA04_CD11_11D2_A8F0_002048088976__INCLUDED_)
#define AFX_QUERYDIALOGDLG_H__5F35AA04_CD11_11D2_A8F0_002048088976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CQueryDialogDlg dialog
#include "KernelInterface.hxx"
#include "SOPClasses.hxx"
#include "DialogQuery.hxx"
#include "VR.hxx"


class CQueryDialogDlg : public CDialog
{
// Construction
private:
	UIv& ExtractVector(CString Input);
public:
	CQueryDialogDlg(CWnd* pParent = NULL);	// standard constructor
	list<UI>* QueryResultUID;

// Dialog Data
	//{{AFX_DATA(CQueryDialogDlg)
	enum { IDD = IDD_QUERYDIALOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQueryDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYDIALOGDLG_H__5F35AA04_CD11_11D2_A8F0_002048088976__INCLUDED_)
