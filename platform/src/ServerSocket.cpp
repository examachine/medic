// ServerSocket.cpp: implementation of the ServerSocket class.
//
//////////////////////////////////////////////////////////////////////

#ifdef __MSC_VER
#include "stdafx.h"
#include "dcl application.h"
#endif // __MSC_VER

#include "ServerSocket.h"

#include <DApplication.hxx>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ServerSocket::ServerSocket()
  : server_context(DTCPContext::server)
{

}

ServerSocket::~ServerSocket()
{

}

void ServerSocket::on_receive(int nErrorCode)
{
	//CCustomSocket::OnReceive(nErrorCode);
	//CSocket::OnReceive(nErrorCode);

	dicom_app.report("ServerSocket: here");

	try {
	 server_context.serve(*this);
	}
	catch ( DException e) {
		e.why();
	}
	catch ( CException e) {
		e.ReportError();
	}
}
