/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef DStreamBuffer_Interface
#define DStreamBuffer_Interface 1

#include "BufferTypes.hxx"

class DStreamBuffer : public DStreamBase, public DBufferList
{
public:
	DStreamBuffer(OpenMode);
	void read (char* buffer, int len);
	void write (char* buffer, int len);
};

#endif
