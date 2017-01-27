//
//
// C++ Interface for module: Socket
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Socket_Interface
#define Socket_Interface

#include "General.hxx"

#ifndef _MSC_VER

// A socket abstraction, a place to which messages
// can be sent.
class Socket
{
public:
  Socket();

  int send(void* data, int size);
  int recv(void* data, int size);

};

#else

// encapsulate MFC socket
#include <afxsock.h>

class Socket : private CAsyncSocket
{
public:
  Socket() {
    CAsyncSocket::Create();
  }

  int send(void* data, int size) {
    return CAsyncSocket::Send(data, size);
  }
  int receive(void* data, int size) {
    return CAsyncSocket::Receive(data, size);
  }
  virtual void on_receive(int err) {}
  CAsyncSocket & get_mfc_socket() {
    return dynamic_cast<CAsyncSocket&>(*this);
  }
  void* operator new(size_t nSize) {
    return new CAsyncSocket; // HUGE KLUDGE BUG!!!  CODE! FIX! DO SOMETHING!
  }
  void operator delete(void* p) {
    CAsyncSocket::operator delete(p);
  }
  bool connect( string address, unsigned int port ) {
    return CAsyncSocket::Connect(address.c_str(), port);
  }

private:
  void OnReceive(int err) {
    on_receive(err);
  }
};

#endif // _MSC_VER

#endif
