#ifndef ServerSocket_Interface
#define ServerSocket_Interface

#include "CustomSocket.h"
#include <DTCPContext.hxx>	

class ServerSocket : public CustomSocket  
{
public:
	DTCPContext server_context;
	void on_receive(int err);
	ServerSocket();
	virtual ~ServerSocket();

};

#endif
