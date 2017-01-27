#ifndef ListenerThread_Interface
#define ListenerThread_Interface

#include "ListenerSocket.h"

#ifdef _MSC_VER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CListenerThread : public CWinThread
{
	DECLARE_DYNCREATE(CListenerThread)
protected:
	CListenerThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CListenerSocket m_ListenerSocket;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenerThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CListenerThread();

	// Generated message map functions
	//{{AFX_MSG(CListenerThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

//typedef CListenerThread ListenerThread;

#else

class ListenerThread;

#endif


#endif
