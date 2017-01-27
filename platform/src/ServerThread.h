#if !defined(AFX_SERVERTHREAD_H__3067B090_0B4C_11D2_9728_002048088976__INCLUDED_)
#define AFX_SERVERTHREAD_H__3067B090_0B4C_11D2_9728_002048088976__INCLUDED_

#include "ServerSocket.h"	// Added by ClassView
#include "DTCPContext.hxx"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ServerThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerThread thread

class CServerThread : public CWinThread
{
	DECLARE_DYNCREATE(CServerThread)
protected:
	CServerThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	ServerSocket m_socket;
	SOCKET m_hSocket;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CServerThread();

	// Generated message map functions
	//{{AFX_MSG(CServerThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERTHREAD_H__3067B090_0B4C_11D2_9728_002048088976__INCLUDED_)
