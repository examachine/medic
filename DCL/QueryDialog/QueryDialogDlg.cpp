// QueryDialogDlg.cpp : implementation file
//
#include "stdafx.h"
#include "QueryDialog.h"
#include "QueryDialogDlg.h"
#include "CFindQuery.hxx"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryDialogDlg dialog

CQueryDialogDlg::CQueryDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryDialogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQueryDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDialogDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQueryDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CQueryDialogDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDialogDlg message handlers

BOOL CQueryDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQueryDialogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQueryDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/*

UIv& CQueryDialogDlg::ExtractVector(CString Input){

	UIv OutVector;
	DStream OutStream(DStreamBase::OpenMode(0));

	int len=Input.GetLength();
	if (!len)
		return OutVector;
	else
	{
		int last=0;
		int lenStr=0;
		for (int i=0;i<len;i++){
			if (Input.GetAt(i)==',')
			{
				lenStr = i-last-1;
				char* strToken= (char*)malloc(sizeof(char)*lenStr+1);
				_tcscpy(strToken, Input.Mid( last, lenStr));
//				UI Token(strToken);
				OutStream.write(strToken, lenStr+1);
			}
		}
		lenStr = len-last-1;
		char* strToken= (char*)malloc(sizeof(char)*lenStr+1);
		_tcscpy(strToken, Input.Mid( last, lenStr));
		//UI Token(strToken);
		OutStream.write(strToken, lenStr+1);
	}
	return OutVector;
}

*/

void CQueryDialogDlg::OnOK() 
{
	// TODO: Add extra validation here

	CFind_Query QueryObj;
	CString SQLQuery;
	
	CString InputArr[16];
	for(int i=0; i++; i<16)
		InputArr[i].Empty();
	GetDlgItemText(IDC_EDIT1, InputArr[0]);
	GetDlgItemText(IDC_EDIT2, InputArr[1]);	
	GetDlgItemText(IDC_EDIT3, InputArr[2]);	
	GetDlgItemText(IDC_EDIT4, InputArr[3]);	
	GetDlgItemText(IDC_EDIT5, InputArr[4]);
	GetDlgItemText(IDC_EDIT6, InputArr[5]);
	GetDlgItemText(IDC_EDIT7, InputArr[6]);
	GetDlgItemText(IDC_EDIT8, InputArr[7]);
	GetDlgItemText(IDC_EDIT9, InputArr[8]);
	GetDlgItemText(IDC_EDIT10, InputArr[9]);
	GetDlgItemText(IDC_EDIT11, InputArr[10]);
	GetDlgItemText(IDC_EDIT12, InputArr[11]);
	GetDlgItemText(IDC_EDIT13, InputArr[12]);
	GetDlgItemText(IDC_EDIT14, InputArr[13]);
	GetDlgItemText(IDC_EDIT15, InputArr[14]);
	GetDlgItemText(IDC_EDIT16, InputArr[15]);	
/*
	AfxMessageBox(InputArr[0]+"/"+InputArr[1]+"/"+InputArr[2]);
	SQLQuery= " ISERIESINSTANCEUID IN";
	SQLQuery+= "(SELECT ESERIESINSTANCEUID FROM SERIES WHERE ESTUDYINSTANCEUID IN";
	SQLQuery+= "(SELECT TSTUDYINSTANCEUID FROM STUDY WHERE TPATIENTID IN";
	SQLQuery+= "(SELECT PPATIENTID FROM PATIENT WHERE";
	SQLQuery+= " PSURNAME='"+ InputArr[1]+"'";
	SQLQuery+= " AND PNAME='"+ InputArr[0]+"'";
//	SQLQuery+= " AND PPATIENTID='"+ InputArr[2]+"'";
	SQLQuery+= ")))";
	AfxMessageBox(SQLQuery);
*/
	SQLQuery=QueryObj.PatientRootQueryStr(InputArr);
	QueryObj.SetSQL(SQLQuery);
	AfxMessageBox(SQLQuery);
	QueryObj.fetch();

	list<Patient_Info>::iterator pbegin,pend;
	list<Study_Info>::iterator sbegin,send;
	list<Series_Info>::iterator rbegin,rend;
	list<Image_Info>::iterator ibegin,iend;

	pbegin=QueryObj.patient_info_list.begin();
	pend=QueryObj.patient_info_list.end();
	for(;pbegin!=pend;pbegin++){
		CString strp((pbegin->patient_id).data());
		AfxMessageBox(strp);
	}

	sbegin=QueryObj.study_info_list.begin();
	send=QueryObj.study_info_list.end();
	for(;sbegin!=send;sbegin++){
		CString strs((sbegin->study_instance_uid).data());
		AfxMessageBox(strs);
	}

	rbegin=QueryObj.series_info_list.begin();
	rend=QueryObj.series_info_list.end();
	for(;rbegin!=rend;rbegin++){
		CString strr((rbegin->series_instance_uid).data());
		AfxMessageBox(strr);
	}


	ibegin=QueryObj.image_info_list.begin();
	iend=QueryObj.image_info_list.end();
	for(;ibegin!=iend;ibegin++){
		CString stri((ibegin->sop_instance_uid).data());
		AfxMessageBox(stri);
	}


	CDialog::OnOK();
}

void CQueryDialogDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
}
