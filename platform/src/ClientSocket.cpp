// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER

#include "StdAfx.h"
#include "platform/res/MEDIC Resources.h"

#endif // _MSC_VER

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

#include "ClientSocket.h"
#include "DApplication.hxx"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{

}

void ClientSocket::OnReceive(int nErrorCode)
{
#ifdef _MSC_VER
  CustomSocket::OnReceive(nErrorCode);

  // tell the stream that the expected data has just arrived
  m_pCallingThread->PostThreadMessage(WM_RECEIVE_PDU_COMPLETE, 0, 0);
#else
  // CODE: portable thread messages!!
#endif
}

