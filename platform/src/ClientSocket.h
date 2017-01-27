#ifndef ClientSocket_Interface
#define ClientSocket_Interface

#include "CustomSocket.h"


class ClientSocket : public CustomSocket  
{
public:
	void OnReceive(int nErrorCode);
	ClientSocket();
	virtual ~ClientSocket();
};

#endif
