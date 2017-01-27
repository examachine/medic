/*
** Interface file for a TS module
**
**
**
** exa
**
*/

#ifndef ImplicitVRLittleEndian_Interface
#define ImplicitVRLittleEndian_Interface 1

#include "General.hxx"
#include "TransferSyntax.hxx"
#include "VR.hxx"

// Dicom default Transfer Syntax
// Implicit VR Little Endian Transfer Syntax
class ImplicitVRLittleEndian : public TransferSyntax {
public:
  ImplicitVRLittleEndian() {}

	static const UI UID;

	static const bool explicit_vr;

	// returns the last tag read
	static Tag decode_tag(DStream &d);
	// encode a tag
	static void encode_tag(DStream &d, Tag tag) {
		encode_short(d, tag.group);
		encode_short(d, tag.element);
	}

	// ignore a data element
	enum IgnoreType { group_length, private_elt, unspecified };
	static void ignore_elt(DStream& d, IgnoreType mode = unspecified );

  static bool check_data_elt_header(DStream& d, const Attribute & a);
  // decode a required data element header
  // return length of data field
  static int decode_req_data_elt_header(DStream& d, const Attribute & a);

  // decode an optional data element header
  // return length of data field
  static int decode_opt_data_elt_header(DStream& d, const Attribute & a);
	//static void encode_data_elt_header(DStream& d, const Attribute & a);
	// encode a data element header
	static void encode_data_elt_header(DStream& d, const Attribute & a, int del) {
		encode_tag(d, a.tag);
		encode_long(d, del);
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
    return a;
  }

  // decode binary long
  static long decode_long(DStream& d) {
    long a;
    //d >> a;
		d.read((char*)&a, sizeof(long));
    return a;
  }

  // decode binary 32-bit floating number
  static float decode_float(DStream& d) {
    float a;
    //d >> dec >> a >> hex;
		d.read((char*)&a, sizeof(float));
    return a;
  }

  // decode binary 64-bit floating number
  static double decode_double(DStream& d) {
    double a;
    //d >> dec >> a >> hex;
		d.read((char*)&a, sizeof(double));
    return a;
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
		d.write((char*)&a, sizeof(short));
  }

  // decode binary long
  static void encode_long(DStream& d, long a) {
		d.write((char*)&a, sizeof(long));
  }

  // decode binary 32-bit floating number
  static void encode_float(DStream& d, float a) {
		d.write((char*)&a, sizeof(float));
  }

  // decode binary 64-bit floating number
  static void encode_double(DStream& d, double a) {
		d.write((char*)&a, sizeof(double));
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

  // decode a character string of n bytes
  // better improve upon this
  static void encode_string(DStream& d, string &str, int n) {
		d.write((char *)str.c_str(), n);
  }

	static void decode_byte_array(DStream& d, void* array, int n) {
		d.read((char *)array, sizeof(char)*n);
	}

	static void decode_short_array(DStream& d, void* array, int n) {
		d.read((char *)array, sizeof(short)*n);
	}

	static void encode_byte_array(DStream& d, void* array, int n) {
		d.write((char *)array, sizeof(char)*n);
	}

	static void encode_short_array(DStream& d, void* array, int n) {
		d.write((char *)array, sizeof(short)*n);
	}


};


#endif
