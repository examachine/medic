#ifndef Platform_CustomSocket_Interface
#define Platform_CustomSocket_Interface

#include <BufferTypes.hxx>
#include <PDU.hxx>

#include <Socket.hxx>
#include <Thread>

class DTCPStream;

#ifndef _MSC_VER

class CustomSocket : public Socket
{
 public:
  CustomSocket();
  virtual ~CustomSocket();
  PDUType GetPDUType();
  void receive_pdu();
  void send_pdu(PDUType, DBufferList&);

 public:
  PDU pdu;
  int pdu_length;
  PDUType pdu_type;
  bool m_fPDUHeader;
  Thread* calling_thread;
  Thread* thread;
  DTCPStream* stream;
  Critical_Region critical_section;
 public:
  virtual void on_receive(int nErrorCode);

 protected:
};

#else

class CustomSocket : public Socket
{
// Attributes
public:
// Operations
public:
	CustomSocket();
	virtual ~CustomSocket();
	PDUType GetPDUType();
	void receive_pdu();
	void send_pdu(PDUType, DBufferList&);

// Overrides
public:
	PDU pdu;
	int pdu_length;
	PDUType pdu_type;
	bool m_fPDUHeader;
	CWinThread* m_pCallingThread;
	CWinThread* m_pThread;
	DTCPStream* m_pStream;
	CCriticalSection critical_section;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCustomSocket)
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
