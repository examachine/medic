/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef BufferTypes_Interface
#define BufferTypes_Interface 1

#include "General.hxx"
#include "DStream.hxx"
#include "Socket.hxx"

enum PDUType {
  associate_rq_type = 0x1, associate_ac_type = 0x2, associate_rj_type = 0x3,
  p_data_tf_type = 0x4, a_release_rq_type = 0x5, a_release_rp_type = 0x6,
  a_abort_type = 0x7
} ;

enum ItemType {
  application_context_item_type = 0x10, rq_presentation_context_item_type = 0x20,
  abstract_syntax_item_type = 0x30, transfer_syntax_item_type = 0x40,
  user_information_item_type = 0x50 , ac_presentation_context_item_type = 0x21,
  maximum_length_subitem_type = 0x51, implementation_class_uid_subitem_type = 0x52,
  implementation_version_name_subitem_type = 0x55
};

// enum AACItemType {
//   application_context = 0x10, presentation_context = 0x21,
//   abstract_syntax = 0x30, transfer_syntax = 0x40,
//   user_information = 0x50
// };

class PDU : public vector<char> {
public:
};

class DBuffer {
public:
  enum { def_buffer_capacity = 8192 };

  DBuffer() : native(true)
  {
    alloc_buffer(def_buffer_capacity);
  }

  DBuffer(int capacity) : native(true)
  {
    alloc_buffer(capacity);
  }

  DBuffer(char* foreign_buffer, int capacity) : native(false)
  {
    data = foreign_buffer;
    pos = data;
    end = data + capacity;
  }

  ~DBuffer()
  {
    if (native)
      delete data;
  }

  void alloc_buffer( int alloc_size ) {
    data = new char[alloc_size];
    pos = data;
    end = data + alloc_size;
  }

  bool add_bytes( char *buffer, int len )
  {
    char* new_pos = pos+len;
    if (reinterpret_cast<int>(new_pos) > reinterpret_cast<int>(end) )
      return false; // data exceeds capacity of buffer
    else {
      memcpy(pos, buffer, len);
      pos = new_pos;
      return true;
    }
  }

  int extract_bytes ( char *buffer, int len )
  {
    char* new_pos = pos + len;
    if (reinterpret_cast<int>(new_pos) > reinterpret_cast<int>(end) ) {
      // data exceeds capacity of buffer, extract partially
      int length_to_end = reinterpret_cast<int>(end) - reinterpret_cast<int>(pos);
      memcpy (buffer, pos, length_to_end);
      pos = end;
      return length_to_end;
    }
    else {
      memcpy(buffer, pos, len);
      pos = new_pos;
      return len;
    }
  }

  bool at_end()
  {
    return (pos == end);
  }

  void trim_end()
  {
    end = pos;
  }

  int length()
  {
    int size;
    size = reinterpret_cast<int>(pos) - reinterpret_cast<int>(data);
    return size;
  }

  int send(Socket& socket)
  {
    int size;
    int sent_size = socket.send
      (data, size = reinterpret_cast<int>(pos)-reinterpret_cast<int>(data));
    if (sent_size != size)
      throw DException("DBuffer: Socket error" + int_to_str(sent_size));
    return sent_size;
  }

  int transfer(DStream& ds)
  {
    int size;
    ds.write(data, size = reinterpret_cast<int>(pos)-reinterpret_cast<int>(data));
    return size;
  }

  int load(DStream& ds, int length)
  {
    char* new_pos = pos + length;
    if (reinterpret_cast<int>(new_pos) > reinterpret_cast<int>(end) ) {
      // data exceeds capacity of buffer
      int length_to_end = reinterpret_cast<int>(end) - reinterpret_cast<int>(pos);
      ds.read(pos, length_to_end);
      pos = end;
      return length_to_end;
    }
    else {
      ds.read(pos, length);
      pos = new_pos;
      return true;
    }
  }

  char *data;
  char *pos;
  char *end;

  bool native;
};


class DBufferList : public list< DBuffer* > {
public:

  DBufferList() {
    append_buffer();
    input_buffer = begin(); /* aman aman */
  }

  void dispose() {
    iterator i = begin(), j = end();
    for (; i!=j; i++) delete *i;
  }

  void append_buffer() {
    push_back( new DBuffer());
  }

  void append_buffer(int len) {
    push_back( new DBuffer(len));
  }

  void append_buffer(char* buffer, int len) {
    push_back( new DBuffer(buffer, len));
  }

  bool input_buffer_at_end() {
    return ( (*input_buffer)->at_end() );
  }

  DBuffer* next_buffer() {
    if (input_buffer == end() )
      throw DException("DBufferList: internal messaging error");
    return *(++input_buffer);
  }

  void add_bytes(char *buffer, int len) {
    if (! back()->add_bytes(buffer, len) ) { // attempt adding at the end of buffer
      if (len >= DBuffer::def_buffer_capacity)
	append_buffer(len);
      else
	append_buffer();
      back()->add_bytes(buffer, len); // a single buffer containing the huge shit
    }
  }

  void begin_extract() {
    input_buffer = begin();
    iterator i = input_buffer, j = end();
    for (; i!=j; i++)
      (*i)->pos = (*i)->data;
  }

  void extract_bytes(char *dest, int len) {
    int received_length;
    for (; len > 0; len -= received_length, dest += received_length) {
      DBuffer *buffer;
      if (input_buffer_at_end() )
	buffer = next_buffer();
      else
	buffer = *input_buffer;
      received_length = buffer->extract_bytes(dest, len) ;
    }
  }

  // load a foreign buffer
  void load_buffer(char* buffer, int len) {
    back()->trim_end(); // trim off the end of buffer
    if (back()->length()==0)
      pop_back();
    append_buffer(buffer, len);
  }

  int length() {
    iterator i = begin(), j = end();
    int size = 0;
    for (; i!=j; i++)
      size += (*i)->length();
    return size;
  }

  int send(Socket& socket) {
    iterator i = begin(), j = end();
    int size = 0;
    for (; i!=j; i++)
      size += (*i)->send(socket);
    return size;
  }

  int transfer(DStream& ds) {
    iterator i = begin(), j = end();
    int size = 0;
    for (; i!=j; i++)
      size += (*i)->transfer(ds);
    return size;
  }

  void load(DStream& ds, int len) {
    // read that many bytes
    // KLLUDGE: read directly from the stream's buffers if possible
    back()->trim_end(); // trim off the end of buffer
    if (back()->length()==0)
      pop_back();
    append_buffer(len);
    back()->load(ds, len);
    begin_extract();
  }

  iterator input_buffer;

};


#endif
