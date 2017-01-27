/*
** Interface file for DStream module
**
** Dicom Stream
**
** exa
**
*/

#ifndef DStream_Interface
#define DStream_Interface 1

#include "General.hxx"
#include "DException.hxx"
#include "Tag.hxx"

// Base class for DICOM stream operations
class DStreamBase {
public:
	enum OpenMode {input, output};

  DStreamBase(OpenMode _mode)
			: is_valid_tag(false), openMode(_mode), position(0), input_size(0x7fffffff)  {}

  // read -- 2 different, first for big pieces, second for small ones
  // write -- there's only one method of output
  //char *buffer;
  //char buffer[buffer_size];

	OpenMode openMode;

	// routines for Tag parsing
	void new_tag(Tag t) { tag = t; is_valid_tag = true; }
	bool valid_tag() { return is_valid_tag; }
	void invalidate_tag() { is_valid_tag = false; }

	int position;
	int sel_unbuffered_position() {
		int pos = position;
		if (valid_tag())
			pos -= 4;
		return pos;
	}
	void forward (int len) { position += len; }

	int input_size; // total size of input, required for decoders
	void mod_input_size(int new_size) { input_size = new_size; }
	bool end_of_input() { return (position >= input_size); }

	virtual void read (char* buffer, int len) {
		if (openMode!=input) throw DStreamReadException("Stream not in input mode");
		forward(len);
	}
	virtual void write (char* buffer, int len) {
		if (openMode!=output) throw DStreamWriteException("Stream not in output mode");
		forward(len);
	}

	void dgn(string s);

	// always read tags in here
	Tag tag;
	bool is_valid_tag;
};

// Default Stream class
//typedef DBinaryFileStream DStream;

// Currently do polymorphic, we dun need speed
typedef DStreamBase DStream;
#endif