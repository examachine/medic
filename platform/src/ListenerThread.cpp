// ListenerThread.cpp : implementation file
//

#ifdef __MSC_VER
#include "stdafx.h"
#include "dcl application.h"
#endif // __MSC_VER

#include <KernelInterface.hxx>
#include "ListenerThread.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenerThread

IMPLEMENT_DYNCREATE(CListenerThread, CWinThread)

CListenerThread::CListenerThread()
{
}

CListenerThread::~CListenerThread()
{
}

BOOL CListenerThread::InitInstance()
{
	// initialize socket
	m_ListenerSocket.Create(dicom_app.dicom_port);
	string server = "DICOM server [AE:" + *dicom_app.ae_title +
			"] [port:" + int_to_str(dicom_app.dicom_port) + "]";
	if (m_ListenerSocket.Listen())
		dicom_app.report("DApplication:  " + server + " initiated ");
	else
		dicom_app.report("DApplication: " + server + " failed to initalize");

	return TRUE;
}

int CListenerThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CListenerThread, CWinThread)
	//{{AFX_MSG_MAP(CListenerThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListenerThread message handlers
