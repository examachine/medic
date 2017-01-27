/*
** Interface file for DBinaryFileStream module
**
** Dicom Stream
**
** exa
**
*/

#ifndef DBFStream_Interface
#define DBFStream_Interface 1

#include "DStream.hxx"

class DFileContext;

class DBinaryFileStream : public DStreamBase, protected fstream {
public:
  DBinaryFileStream(const char* fn, OpenMode _mode);

  DBinaryFileStream(string fn, OpenMode _mode);

	~DBinaryFileStream();

	void read (char* buffer, int len);

	void write (char* buffer, int len);
protected:
	void init(const char* fn, OpenMode _mode);

	void position_write_head(int pos) { seekp(pos); }

	friend class DFileContext;
};


#endif
