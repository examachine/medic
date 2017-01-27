// ListenerSocket.cpp : implementation file
//

#ifdef __MSC_VER
#include "stdafx.h"
#include "dcl application.h"
#endif // __MSC_VER

#include "ListenerSocket.h"
#include "ServerThread.h"
#include "DApplication.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenerSocket

CListenerSocket::CListenerSocket()
{
}

CListenerSocket::~CListenerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenerSocket, CAsyncSocket)
  //{{AFX_MSG_MAP(CListenerSocket)
  //}}AFX_MSG_MAP
  END_MESSAGE_MAP()
#endif	// 0

  /////////////////////////////////////////////////////////////////////////////
  // CListenerSocket member functions

  void CListenerSocket::OnAccept(int nErrorCode) 
{
  dicom_app.report("CListenerSocket: Connection accepted");
  // New connection is being established

  CSocket soc;

  // Accept the connection using a temp CSocket object.
  Accept(soc);

  // Create a thread to handle the connection. The thread is created suspended so that we can
  // set variables in CConnectThread before it starts executing.
  CServerThread* pThread = (CServerThread*)AfxBeginThread(RUNTIME_CLASS(CServerThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
  if (!pThread)
    {
      soc.Close();
      TRACE("Could not create thread\n");
      return;
    }
  //CServerDlg* pDlg = (CServerDlg*) m_pWndDlg;

  // set members of CConnectThread.m_socket
  //pThread->m_socket.m_pCriticalSection = &pDlg->m_criticalSection;
  //pThread->m_socket.m_pLastString = &pDlg->m_lastString;

  // Pass the socket to the thread by passing the socket handle. You cannot pass
  // a CSocket object across threads.
  pThread->m_hSocket = soc.Detach();
  //pThread->m_Socket.m_pCallingThread = AfxGetThread();

  // Now start the thread.
  pThread->ResumeThread();
	
  CAsyncSocket::OnAccept(nErrorCode);
}
