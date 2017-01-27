#ifndef ListenerSocket_Interface
#define ListenerSocket_Interface

#include "Socket.hxx"

#ifndef _MSC_VER

// async socket?
class ListenerSocket : public Socket
{
 public:
  ListenerSocket();
  virtual ~ListenerSocket();

  virtual void on_accept(/*int nErrorCode*/);
 protected:
};

#else

class CListenerSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CListenerSocket();
	virtual ~CListenerSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif

#endif
