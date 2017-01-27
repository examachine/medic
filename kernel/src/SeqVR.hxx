/*
** Interface file for SeqVR module
**
**
**
** exa
**
*/

#ifndef SeqVR_Interface
#define SeqVR_Interface 1

#include "VR.hxx"

template <class Item> class SQ : public list< Item >
{
public:
	
  typedef SQ<Item> Self;
	
//   Self() {}
  SQ<Item>() {}			// KLUDGE: possible g++ bug
	
  string toString() {
    string str = "<";
    if (!empty()) {
      iterator i = begin(), j = end();
      str += i->toString();
      i++;
      for (; i!=j ; i++)
	str += string(",") + i->toString();
    }
    return str + ">";
  }
	
  static const char* selName() { return "SQ"; }
	
  Item & genElement()
  {
    push_back(Item());
    iterator last = end();
    last--;
    return *last; // allocate a new VR at the end of vector
  }
	
  template<class TS = ImplicitVRLittleEndian>
  class Coder : public VR::Coder {
  public:
    void decode_item(DStream & d, Item & item) {
      int item_len = TS::decode_item_header(d);
      if (item_len != TS::UndefinedLength) {
	int last_pos = d.position + item_len;
	typename Item::Coder<TS> coder;
	coder.decode(d, item);
	if ( last_pos < d.position )
	  throw DItemEncodingException();
      }
      else {
	typename Item::Coder<TS> coder;
	coder.decode(d, item);
	if ( ! (TS::decode_item_delim(d)) )  // mandatory here
	  throw DItemEncodingException();
      }
    }
		
    bool do_decode(DStream & d, Self & a, int del) {
      a.erase(a.begin(), a.end()); // cleanse storage
      int number_of_elts = 0;
      int pos = d.position;
      int last_pos;
      if (del != TS::UndefinedLength) {
	last_pos = pos + del;
	while ( d.position < last_pos ) {
	  Item & item = a.genElement();
	  decode_item(d, item);
	}
      }
      else {
	while ( ! (TS::is_seq_delim(d)) ) {
	  Item & item = a.genElement();
	  decode_item(d, item);					
	}
	TS::decode_seq_delim(d);
      }
      return true;
    }
		
    void decode_mandatory(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (!do_decode(d, a, del))
	throw DVREncodingException();
    }
		
    bool decode_required(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (del == 0) {				// no value field
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }
		
    bool decode_optional(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_opt_data_elt_header(d, attr_info);
      if ((del==0) || (del == TransferSyntax::TagNotFound) ) {
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }

    void encode_item(DStream & d, Item & item) {
      TS::encode_item_header(d);
      typename Item::Coder<TS> coder;
      coder.encode(d, item);
      TS::encode_item_delim(d);
    }
		
    void encode_empty(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, 0);
    }

    void encode(DStream & d, Self & a, const Attribute & attr_info) {
      TS::encode_data_elt_header(d, attr_info, TS::UndefinedLength);
      Self::iterator i=a.begin(), j=a.end();
      for ( ; i!=j ; i++ ) {
	encode_item(d, *i);					
      }
      TS::encode_seq_delim(d);
    }
		
  };
	
};

class OB : public vector<unsigned char>
{
public:

  typedef OB Self;

  OB() {}			// KLUDGE: possible g++ bug
  int get_length() { return size()*sizeof(char); }
  string toString() {
    return string("<OB : ") + size() +">"; 
  }
  /*
    string toString() {
    string str = "<";
    int len = size();
    int i = 0;
    if (! len ) {
    str += (*this)[i];
    i++;
    for (; i < len ; i++)
    str += string(",") + (*this)[i];
    }
    return str + ">";
    }*/
  string selName() { return name; }
  static const char name[3];

  unsigned char* data() { return &front(); }
  void free() { clear(); }

  template<class TS = ImplicitVRLittleEndian>
  class Coder : public VR::Coder {
  public:
    bool do_decode(DStream & d, Self & a, int del) {
      int number_of_elts = del/sizeof(char);
      a.resize(number_of_elts);
      unsigned char *data = a.data();
      TS::decode_byte_array(d, data, number_of_elts);
      return true;
    }
		
    void decode_mandatory(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (!do_decode(d, a, del))
	throw DVREncodingException();
    }
		
    bool decode_required(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (del == 0) {				// no value field
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }
		
    bool decode_optional(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_opt_data_elt_header(d, attr_info);
      if ((del==0) || (del == TransferSyntax::TagNotFound)) {
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }

    void encode_empty(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, 0);
    }

    void encode(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, a.get_length());
      TS::encode_byte_array(d, a.data(), a.size());
    }

  };

};

class OW : public vector<unsigned short>
{
public:

  typedef OW Self;
  typedef unsigned short elt_t;

  OW() : ob(false) {}		// BUG: can't use Self here
  int get_length() { return size()*sizeof(elt_t); }
  string toString() {
    return string("<OW : ") + size() +">"; 
  }
  string selName() { return name; }
  static const char name[3];
	
  unsigned short *data() { return &front(); }
  unsigned char *ob_data() { return (unsigned char *)&front(); } // Return OB data!
  int ob_length() { return get_length(); } // Return ob length! SOMEWHAT KLUDGE
  const bool is_ob() { return ob; } // Is the type OB instead of OW?
  void free() { clear(); }

  template<class TS = ImplicitVRLittleEndian>
  class Coder : public VR::Coder {
  public:
    // KLUDGE: I handle pixel data attribute here
    bool do_decode(DStream & d, Self & a, const Attribute & attr_info, int del) {
      // KLUDGE:NOTE: In OB, there's 0 padding to even boundary.
      // KLUDGE: This is damn wrong!, can't get full size from network!
      // will only work with files!
      if (del == TS::UndefinedLength)
	del = d.input_size - d.position;
      int number_of_elts = del/sizeof(elt_t);
      a.resize(number_of_elts);
      unsigned short *data = a.data();
      if (pixel_data(attr_info) && TS::explicit_vr) {
	a.ob = true;
	TS::decode_byte_array(d, data, del);
      }
      else
	TS::decode_short_array(d, data, number_of_elts);
      return true;
    }
		
    // KLUDGE: handle pixel data attribute here
    bool pixel_data(const Attribute & attr_info) {
      return attr_info.tag==Tag(0x7fe0,0x0010);
    }

    void decode_mandatory(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (!do_decode(d, a, attr_info, del))
	throw DVREncodingException();
    }
		
    bool decode_required(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (del == 0) {				// no value field
	return false;
      }
      else if (do_decode(d, a, attr_info, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }
		
    bool decode_optional(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_opt_data_elt_header(d, attr_info);
      if ( (del == 0) || (del == TransferSyntax::TagNotFound) ) {
	return false;
      }
      else if (do_decode(d, a, attr_info, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }

    void encode_empty(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, 0);
    }

    void encode(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, a.get_length());
      TS::encode_short_array(d, a.data(), a.size());
    }


  };

  //private:
  bool ob;

};


#endif
