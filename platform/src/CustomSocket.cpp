// CustomSocket.cpp : implementation file
//

#ifdef __MSC_VER
#include "stdafx.h"
#include "dcl application.h"
#endif // __MSC_VER

#include "CustomSocket.h"
#include <DApplication.hxx>
//#include <DException.hxx>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CustomSocket

CustomSocket::CustomSocket()
: m_pStream(0)
{
}

CustomSocket::~CustomSocket()
{
}

PDUType CustomSocket::GetPDUType()
{
	return pdu_type;
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CustomSocket, CSocket)
	//{{AFX_MSG_MAP(CustomSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CustomSocket member functions

void CustomSocket::OnReceive(int nErrorCode) 
{
	dicom_app.report("CustomSocket: Incoming data");
	// new data in TCP buffers, prepare for receipt

	/*
	// no other thread should be accessing
	CSingleLock lock(&critical_section, true);
	// Is this the head of a PDU or fields of it?
	if (m_fPDUHeader) {
		receive_pdu();
	else {
		throw DException("CustomSocket: expecting a PDU header, got garbage");
	}

  //throw DException("CustomSocket: Internal messaging error, stream link unavailable");

	CSocket::OnReceive(nErrorCode);
	*/
}

void CustomSocket::receive_pdu()
{	
	int length_read;
	// read in the header
	char type;
	char dummy;

	if ( (length_read = receive(&type, 1)) != 1)
		throw DException("CustomSocket: Unable to receive PDU");

	if ( (length_read = receive(&dummy, 1)) != 1)
		throw DException("CustomSocket: Unable to receive PDU");

	if ( (length_read = receive(&pdu_length, 4)) != 4)
		throw DException("CustomSocket: Unable to receive PDU");
	pdu_length = ntohl (pdu_length); // Big Endian
	pdu_type = static_cast<PDUType>(type);
		
	//dicom_app.report(string("CustomSocket: received PDU header for ") + int_to_str(pdu_length) + " bytes");

	if ((pdu_length>0) && (pdu_length <= 0x20000)) { 
	// do no touch the remains yet
	pdu.resize(pdu_length);

	// read the whole PDU, this may not be optimal but just suffice with it for now
	//length_read = Receive(&pdu.front(), pdu_length);
	//dicom_app.report(string("CustomSocket: received PDU , length") + int_to_str(length_read) + " bytes");

	char* receive_pos = &pdu.front();
	int remaining_bytes =  pdu_length;
	while ( remaining_bytes > 0 ) {
		length_read = receive(receive_pos, remaining_bytes);
		if (length_read < 0)
			throw DException("CustomSocket: Cannot receive PDU fragment, WINSOCK err: " + int_to_str(length_read));
		receive_pos += length_read;
		remaining_bytes -= length_read; 
		//dicom_app.report(string("CustomSocket: received PDU fragment , length") + int_to_str(length_read) + " bytes");
	}
	dicom_app.report(string("CustomSocket: received PDU, length ") + int_to_str(pdu_length) + " bytes");
	}
	else {
		//pdu.resize(0x20000);
	  throw DException("CustomSocket: PDU length exceeds 0x20000");
	}
}

void CustomSocket::send_pdu(PDUType out_pdu_type, DBufferList& out_pdu_buffers)
{
	char dummy = 0;
	int length, be_length;
	int sent_length;

	if ((sent_length = send(&out_pdu_type, 1)) != 1)
		throw DException("CustomSocket: Unable to send PDU Type");

	if ((sent_length = send(&dummy, 1)) != 1)
		throw DException("CustomSocket: Unable to send PDU header's dummy byte");

	length = out_pdu_buffers.length();
	be_length = htonl( length ); // Big Endian
	if ( (sent_length = send(&be_length, 4)) != 4 )
		throw DException("CustomSocket: Unable to send PDU Length");

	sent_length = out_pdu_buffers.send(*this);
	dicom_app.report(string("CustomSocket: sent PDU, length ") + int_to_str(sent_length) + " bytes");
}
