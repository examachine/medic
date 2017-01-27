// ServerThread.cpp : implementation file
//


#ifdef __MSC_VER
#include "stdafx.h"
#include "dcl application.h"
#endif // __MSC_VER

#include "ServerThread.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerThread

IMPLEMENT_DYNCREATE(CServerThread, CWinThread)

CServerThread::CServerThread()
{
	m_socket.m_pThread = this;
}

CServerThread::~CServerThread()
{
}

BOOL CServerThread::InitInstance()
{
	// Attach the socket here
	m_socket.get_mfc_socket().Attach(m_hSocket);
	//m_socket.m_pThread = this;
	return TRUE;
}

int CServerThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CServerThread, CWinThread)
	//{{AFX_MSG_MAP(CServerThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerThread message handlers
