/*
**
** Implementation file for DStreamBuffer module
**
**
**
** exa
**
*/

#include "KernelInterface.hxx"

DStreamBuffer::DStreamBuffer(OpenMode _mode)
	: DStreamBase(_mode)
{
	switch (openMode) {
	case input:
		break;
	case output:
		break;
	default:
		throw DException("Unknown TCP stream mode");
	}
	//dgn( string("DStreamBuffer:") );
}

void DStreamBuffer::read (char* buffer, int len)
{
	extract_bytes(buffer, len);
	DStreamBase::read(buffer, len);
}

void DStreamBuffer::write (char* buffer, int len)
{
	add_bytes(buffer, len);
	DStreamBase::write(buffer, len);
}
