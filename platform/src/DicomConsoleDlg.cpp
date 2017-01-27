// DicomConsoleDlg.cpp : implementation file
//

#ifdef __MSC_VER
#include "StdAfx.h"
#include "DCL Resources.h"
#endif // __MSC_VER

#include "DicomConsoleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDicomConsoleDlg dialog


CDicomConsoleDlg::CDicomConsoleDlg(CWnd* pParent /*= NULL*/ )
	: CDialog(CDicomConsoleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDicomConsoleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDicomConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDicomConsoleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDicomConsoleDlg, CDialog)
	//{{AFX_MSG_MAP(CDicomConsoleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDicomConsoleDlg message handlers

void CDicomConsoleDlg::Report(const CString & s)
{
	CListBox* list = (CListBox*) GetDlgItem(IDC_DICOM_REPORTS);
	list->AddString(s);
	if (list->GetCount() > report_buffer_size) {
		list->DeleteString(0);
	}
}
