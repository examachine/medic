/*
** Interface file for a TS module
**
**
**
** exa
**
*/

#ifndef ExplicitVRBigEndian_Interface
#define ExplicitVRBigEndian_Interface 1

#include "General.hxx"
#include "TransferSyntax.hxx"
#ifdef _MSC_VER
#include <afxsock.h>
#endif

// Dicom default Transfer Syntax
// Explicit VR Big Endian Transfer Syntax
class ExplicitVRBigEndian : public TransferSyntax
{
public:
  ExplicitVRBigEndian() {}

  static const UI UID;

  static const bool explicit_vr;

  // returns the last tag read
  static Tag decode_tag(DStream &d);

  // decode suitable vr
  static bool decode_vr(DStream &d);

  // decode length
  //static void decode_length(DStream &d, const Attribute & a);

  // encode a tag
  static void encode_tag(DStream &d, Tag tag) {
    encode_short(d, tag.group);
    encode_short(d, tag.element);
  }
  // encode vr
  static void encode_vr(DStream & d, const Attribute & a) {
    encode_string(d, string(a.vr), 2);
    if (a.sequence)
      encode_short(d, 0);
  }

  // ignore a data element
  enum IgnoreType { group_length, private_elt, unspecified };
  static void ignore_elt(DStream& d, IgnoreType mode = unspecified );

  // decode a required data element header
  // return length of data field
  static int decode_req_data_elt_header(DStream& d, const Attribute & a);

  static bool check_data_elt_header(DStream& d, const Attribute & a);
  // decode an optional data element header
  // return length of data field
  static int decode_opt_data_elt_header(DStream& d, const Attribute & a);
  //static void encode_data_elt_header(DStream& d, const Attribute & a);
  // encode a data element header
  static void encode_data_elt_header(DStream& d, const Attribute & a, int del) {
    encode_tag(d, a.tag);
    encode_vr(d, a);
    if (a.sequence)
      encode_long(d, del);
    else
      encode_short(d, del);
  }

  // decode an item header
  static int decode_item_header(DStream& d);

  // decode delimiter
  static bool is_seq_delim(DStream & d);
  static bool decode_seq_delim(DStream & d);  // MAKE RETURN TYPE VOID
  static bool decode_item_delim(DStream & d);

  // encode an item header
  static void encode_item_header(DStream& d) {
    encode_tag(d, Tag(0xfffe, 0xe000));
    encode_long(d, UndefinedLength);
  }

  // encode delimiter
  static void encode_seq_delim(DStream & d)
  {
    encode_tag(d, Tag(short(0xfffe), short(0xe0dd)));
    encode_long(d, 0);
  }
	
  static void encode_item_delim(DStream & d)
  {
    encode_tag(d, Tag(short(0xfffe), short(0xe00d)));
    encode_long(d, 0);
  }

  // low-level access routines

  // decode binary byte
  static char decode_char(DStream& d) {
    char a;
    //d >> a;
    d.read((char*)&a, sizeof(char));
    return a;
  }

  // decode binary short
  static short decode_short(DStream& d) {
    short a;
    d.read((char*)&a, sizeof(short));
    return (short) ntohs(a);
  }

  // decode binary long
  static long decode_long(DStream& d) {
    long a;
    //d >> a;
    d.read((char*)&a, sizeof(long));
    return (long) ntohl(a);
  }

  // decode binary 32-bit floating number
  static float decode_float(DStream& d) {
    float conv_input;
    float conv_output;
    char* conv_src = reinterpret_cast<char*>(&conv_input);
    char* conv_dest = reinterpret_cast<char*>(&conv_output);
    int size = sizeof(float);
    d.read(conv_src, size);
    for (int i=0; i < size; i++) {
      conv_dest[size-i-1] = conv_src[i];
    }
    return conv_output;
  }

  // decode binary 64-bit floating number
  static double decode_double(DStream& d) {
    double a; double *b = &a;
    int *x1 = reinterpret_cast<int*>(&a),
      *x2 = x1 + 1;
    d.read((char*)&a, 8);
    int tmp = ntohl(*x1);
    *x1 = ntohl(*x2);
    *x2 = ntohl(tmp);
    return *b;
  }

  static void decode_binary(DStream& d, char& a) {
    a = decode_char(d);
  }

  static void decode_binary(DStream& d, short& a) {
    a = decode_short(d);
  }

  static void decode_binary(DStream& d, long& a) {
    a = decode_long(d);
  }

  static void decode_binary(DStream& d, unsigned char& a) {
    a = decode_char(d);
  }

  static void decode_binary(DStream& d, unsigned short& a) {
    a = decode_short(d);
  }

  static void decode_binary(DStream& d, unsigned long& a) {
    a = decode_long(d);
  }

  static void decode_binary(DStream& d, float& a) {
    a = decode_float(d);
  }

  static void decode_binary(DStream& d, double& a) {
    a = decode_double(d);
  }

  // decode a character string of n bytes
  // better improve upon this
  static void decode_string(DStream& d, string &str, int n) {
    //d >> str;
    char *buf =  new char[n];
    d.read(buf, n);
    str.assign(buf, n);
    delete buf;
  }

  // decode a delimited character string of maximum n bytes
  // return number of byted decoded
  static int decode_delimited_string(DStream& d, string &str, int n) {
    //d >> str;
    char *buf =  new char[n];
    // Read from the input stream until a delimiter is met
    int len = 0, read_chars = 0;
    bool flag = true;
    do {
      char c = decode_char(d);
      read_chars++;
      if ( c == '\\' ) // if delimiter met
	flag = false;
      else {
	if (read_chars == n)  // last char
	  flag = false;
	buf[len++] = c;
      }
    } while ( flag );
    str.assign(buf, len);
    delete buf;
    return read_chars;
  }

  // decode binary byte
  static void encode_char(DStream& d, char a) {
    d.write((char*)&a, sizeof(char));
  }

  // decode binary short
  static void encode_short(DStream& d, short a) {
    a = htons(a);
    d.write((char*)&a, sizeof(short));
  }

  // decode binary long
  static void encode_long(DStream& d, long a) {
    a = htonl(a);
    d.write((char*)&a, sizeof(long));
  }

  // decode binary 32-bit floating number
  static void encode_float(DStream& d, float conv_input) {
    float conv_output;
    char* conv_src = reinterpret_cast<char*>(&conv_input);
    char* conv_dest = reinterpret_cast<char*>(&conv_output);
    int size = sizeof(float);
    d.read(conv_src, size);
    for (int i=0; i < size; i++) {
      conv_dest[size-i-1] = conv_src[i];
    }
    d.write(conv_dest, size);
  }

  // decode binary 64-bit floating number
  static void encode_double(DStream& d, double a) {
    double *b = &a;
    int *x1 = reinterpret_cast<int*>(&a),
      *x2 = x1 + 1;
    int tmp = *x1;
    *x1 = htonl(*x2);
    *x2 = htonl(tmp);
    d.write( (char*)b, 8 );
  }

  static void encode_binary(DStream& d, char& a) {
    encode_char(d, a);
  }

  static void encode_binary(DStream& d, short& a) {
    encode_short(d, a);
  }

  static void encode_binary(DStream& d, long& a) {
    encode_long(d, a);
  }

  static void encode_binary(DStream& d, unsigned char& a) {
    encode_char(d, a);
  }

  static void encode_binary(DStream& d, unsigned short& a) {
    encode_short(d, a);
  }

  static void encode_binary(DStream& d, unsigned long& a) {
    encode_long(d, a);
  }

  static void encode_binary(DStream& d, float& a) {
    encode_float(d, a);
  }

  static void encode_binary(DStream& d, double& a) {
    encode_double(d, a);
  }

  // encode a character string of n bytes
  // better improve upon this
  static void encode_string(DStream& d, const string &str, int n) { //KLUDGE: no length in here!!
    d.write((char *)str.c_str(), n);
  }

  static void decode_byte_array(DStream& d, void* array, int n) {
    d.read((char *)array, sizeof(char)*n);
  }

  static void decode_short_array(DStream& d, void* array, int n) {
    d.read((char *)array, sizeof(short)*n);
    // convert all to little endian
    short* start = (short*)array;
    short* end = ((short*)array) + n;
    for (; start != end; start++)
      *start = ntohs(*start);
  }

  static void encode_byte_array(DStream& d, void* array, int n) {
    d.write((char *)array, sizeof(char)*n);
  }

  static void encode_short_array(DStream& d, void* array, int n) {
    // convert all to big endian
    short* start = (short*)array;
    short* end = ((short*)array) + n;
    for (; start != end; start++)
      *start = htons(*start);
    d.write((char *)array, sizeof(short)*n);
  }

};


#endif
