/*
**
** Implementation file for ImplicitVRLittleEndian module
**
**
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif // _MSC_VER

#include "KernelInterface.hxx"

const UI ImplicitVRLittleEndian::UID("1.2.840.10008.1.2");

const bool ImplicitVRLittleEndian::explicit_vr(false);

// returns the last tag read
Tag ImplicitVRLittleEndian::decode_tag(DStream &d) {
	if (!d.valid_tag()) {
		Tag tag;
		if (d.end_of_input()) {
			tag.group = 0xfffe;
			tag.element = 0xffff;
		}
		else {
			tag.group = decode_short(d);
			tag.element = decode_short(d);
		}
		//dgn (string("Tag: ") + tag.toString() );
		d.new_tag(tag);
		return tag;
	}
	else
		return d.tag;
}


// ignore a data element
void ImplicitVRLittleEndian::ignore_elt(DStream& d, IgnoreType mode) {
	d.invalidate_tag();
	switch (mode) {
	case group_length: decode_long(d); decode_long(d); break;
	case private_elt: decode_long(d); break; // find out Attribute related from tag
	case unspecified:
	default:
		// ignore atomic VRs here
		int n;
		char *ignore = new char[n=decode_long(d)];
		d.read(ignore, n);
		delete ignore;
	};
}

// check if a data element header exists
bool ImplicitVRLittleEndian::check_data_elt_header(DStream& d, const Attribute & a) {
	// diagnostics
	//dgn( "Decoding Attribute: " + a.toString());
  // check the tag
  do {
	  Tag tag = decode_tag(d);
    if (tag == a.tag) {
      // we have caught the correct data element
			return true;
    }
    else if (tag.element == 0) { // group length
	    ignore_elt(d, group_length);
    }
		  else if (odd(tag.group)) {
			ignore_elt(d, private_elt);
		}
      else if (tag > a.tag) {
      return false; // there's a data element of a different type
    }
		else {
			// ignore it, proceeding to the next element
			ignore_elt(d);
		}
  }
  while(true);
}

// decode a required data element header
// return length of data field
int ImplicitVRLittleEndian::decode_req_data_elt_header(DStream& d, const Attribute & a) {
	// diagnostics
	//dgn( string("Decoding Attribute: ") + a.toString() );
  // fetch the tag
  do {
		Tag tag = decode_tag(d);
    if (tag == a.tag) {
      // we have caught the correct data element
      // return value length
      int value_length = decode_long(d);
      //if ((value_length == 0) && !a.sequence ) // length of value field shall not be zero.
      //  throw DDETypeException();
      //else {
				d.invalidate_tag();
        return value_length;
			//}
    }
    else if (tag.element == 0) { // group length
			ignore_elt(d, group_length);
    }
		else if (odd(tag.group)) {
			ignore_elt(d, private_elt);
		}
    else if (tag > a.tag) {
      throw DDETypeException(); // Protocol Violation, data element not present
    }
		else {
			// ignore it, proceeding to the next element
			ignore_elt(d);
		}
  }
  while(true);
}

// decode an optional data element header
// return length of data field
int ImplicitVRLittleEndian::decode_opt_data_elt_header(DStream& d, const Attribute & a) {
	// diagnostics
	//dgn( "Decoding Attribute: " + a.toString());
  // check the tag
  do {
	  Tag tag = decode_tag(d);
    if (tag == a.tag) {
      // we have caught the correct data element
      // return value length
      int value_length = decode_long(d);
			d.invalidate_tag();
      return value_length;
    }
    else if (tag.element == 0) { // group length
	    ignore_elt(d, group_length);
    }
		  else if (odd(tag.group)) {
			ignore_elt(d, private_elt);
		}
      else if (tag > a.tag) {
      return TransferSyntax::TagNotFound; // there's a data element of a different type
    }
		else {
			// ignore it, proceeding to the next element
			ignore_elt(d);
		}
  }
  while(true);
}


// decode an item element header
// items are always required
// return length of item
int ImplicitVRLittleEndian::decode_item_header(DStream& d) {
	// diagnostics
	//dgn(string("decoding item header"));
  // fetch the tag
  do {
		Tag tag = decode_tag(d);
    if (tag == Tag(0xfffe,0xe000)) {        // if Item Tag
      int value_length = decode_long(d);
			d.invalidate_tag();
      return value_length;
    }
    else if (tag.element == 0) { // group length
			ignore_elt(d, group_length);
    }
		else if (odd(tag.group)) {
			ignore_elt(d, private_elt);
		}
		else {
      throw DDETypeException(); // Protocol Violation, item not present
		}
  }
  while(true);
}

bool ImplicitVRLittleEndian::is_seq_delim(DStream & d)
{
	if (decode_tag(d)==Tag(0xfffe, 0xe0dd))
		return true;
	else
		return false;
}

bool ImplicitVRLittleEndian::decode_seq_delim(DStream & d)
{
	if ( !( decode_tag(d) == Tag(0xfffe, 0xe0dd) ))
		throw DDETypeException();
	d.invalidate_tag();
	decode_long(d);
	return true;
}

bool ImplicitVRLittleEndian::decode_item_delim(DStream & d)
{
	if ( ! ( decode_tag(d) == Tag(0xfffe, 0xe00d) ))
		throw DDETypeException();
	d.invalidate_tag();
	decode_long(d);
	return true;
}

