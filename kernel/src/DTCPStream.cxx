/*
**
** Implementation file for module DTCPStream
**
**
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif // _MSC_VER

#include "KernelInterface.hxx"
#include "ServerSocket.h"

DTCPStream::DTCPStream(CustomSocket & s, OpenMode _mode)
  : DStreamBase(_mode), socket(s)
{
  switch (openMode) {
  case input:
    break;
  case output:
    break;
  default:
    throw DException("Unknown TCP stream mode");
  }
  //dgn( string("DTCPStream online") );
}

DTCPStream::~DTCPStream()
{
}

PDUType DTCPStream::begin_read()
{
  //MSG dummy_msg;
  //GetMessage(&dummy_msg, NULL, WM_RECEIVE_PDU_COMPLETE, WM_RECEIVE_PDU_COMPLETE);
  socket.receive_pdu();

  //begin_access();

  mod_input_size(socket.pdu_length);

  // start reading a new PDU
  return socket.GetPDUType();

}

PDUType DTCPStream::continue_read (int _position)
{
  position = _position;
  if (position >= input_size)
    throw DException("DTCPStream: exceeded end of buffer");
  return socket.GetPDUType();
}

void DTCPStream::read_field (char* buffer, int len)
{
  // read data with P-DATA service
}

void DTCPStream::read (char* buffer, int length) {
  // read next PDU field
  memcpy(buffer, (& socket.pdu.front() )+ position, length);

  //dicom_app.report("DTCPStream: received " + int_to_str(length) + " bytes");
  DStreamBase::read(buffer, length);
}

void DTCPStream::end_read()
{
  // end reading the PDU
  //end_access();
}

void DTCPStream::begin_write(PDUType type)
{
  // begin writing a pdu
  out_pdu_type = type;

  //CODE: why following commented out?
  //out_pdu_buffers.clear();
}

void DTCPStream::write_field(char* buffer, int len)
{
  // write with P-DATA service
  write_field (buffer, len);
}

void DTCPStream::write(char* buffer, int len)
{
  // write next PDU field
  out_pdu_buffers.add_bytes(buffer, len);
	
  //dicom_app.report("DTCPStream: sent " + int_to_str(len) + " bytes");
  DStreamBase::write(buffer, len);
}

int DTCPStream::end_write()
{
  // finish writing and send PDU

  //socket.m_pThread->PostThreadMessage(WM_SEND_PDU, 0, (long)this);
  //MSG dummy_msg;
  //GetMessage(&dummy_msg, 0,WM_SEND_PDU_COMPLETE, WM_SEND_PDU_COMPLETE);

  socket.send_pdu(out_pdu_type, out_pdu_buffers);

  return out_pdu_buffers.length();
}






