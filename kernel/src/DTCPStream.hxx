/*
** Interface file for DTCPStream module
**
**
**
** exa
**
*/

#ifndef DTCPStream_Interface
#define DTCPSTream_Interface 1

#include "General.hxx"
class DTCPContext;
class CustomSocket;

class DTCPStream : public DStreamBase {
public:

  DTCPStream(CustomSocket &, OpenMode _mode);

	~DTCPStream();

	//void begin_access();

	//void end_access();

	PDUType begin_read ();

	PDUType continue_read (int position);

	virtual void read_field (char* buffer, int len);

	virtual void read (char* buffer, int len);

	virtual void end_read ();

	virtual void begin_write (PDUType);

	virtual void write_field (char* buffer, int len);

	virtual void write (char* buffer, int len);

	virtual int end_write();

//protected:
public:
	friend class DTCPContext;

	CustomSocket & socket;

	//CSingleLock *lock;

	PDUType out_pdu_type;
	DBufferList out_pdu_buffers;

};

#endif
