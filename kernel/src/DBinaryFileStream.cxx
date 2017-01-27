/*
**
** Implementation file for DStream module
**
** Dicom Stream
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif // _MSC_VER

#include "KernelInterface.hxx"
#include <File_System>

DBinaryFileStream::DBinaryFileStream(const char* fn, OpenMode _mode)
  : DStreamBase(_mode) { init(fn, _mode); }

DBinaryFileStream::DBinaryFileStream(string fn, OpenMode _mode)
  : DStreamBase(_mode) { init(fn.c_str(), _mode); }

void DBinaryFileStream::init(const char* fn, OpenMode _mode)
{
  try {
    switch (openMode) {
    case input: {
      // learn file's size
      int file_size;
      {
	File file(fn);
	file_size = file.get_size();
      }

      // it's a kind of magic
      mod_input_size(file_size);

      open(fn, ios::in | ios::binary );
      if ( !good() )
	throw DStreamReadException(string("unable to open file ") + fn + " for reading");
    }
      break;
    case output:
      open(fn, ios::out | ios::binary );
      if ( !good() )
	throw DStreamWriteException
	  (string("unable to open file ") + fn + " for writing " );
      break;
    }
   
    dgn( string("DICOM file stream i/o initiated") );
  } // try
#ifdef _MSC_VER
  catch (CFileException e) {	// CODE: move exception handling to platform
    e.ReportError();
    throw DException("Cannot open file");
  }
#endif
  catch ( ... ) {
    cerr << "yazik yazik" << endl;
  }
}

DBinaryFileStream::~DBinaryFileStream()
{
  close();
}

void DBinaryFileStream::read (char* buffer, int len) {
  fstream::read(buffer, len);
  if ( !good() )
    throw DStreamReadException(string(" read failed at position 0x") + int_to_hexstr(position) );
  DStreamBase::read(buffer, len);
}

void DBinaryFileStream::write (char* buffer, int len) {
  fstream::write(buffer, len);
  flush();
  if ( !good() )
    throw DStreamReadException(string(" write failed at position 0x") + int_to_hexstr(position) );
  DStreamBase::write(buffer, len);
}

