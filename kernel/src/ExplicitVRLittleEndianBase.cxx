/*
**
** Implementation file for a TS module
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

const bool ExplicitVRLittleEndianBase::explicit_vr(true);

// returns the last tag read
Tag ExplicitVRLittleEndianBase::decode_tag(DStream &d) {
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

// Decode the VR field
// returns true if sequence vr
//CODE: type checking
bool ExplicitVRLittleEndianBase::decode_vr(DStream & d) {
  string vr;
  decode_string(d, vr, 2);
  if ((vr=="SQ") || (vr=="OB") || (vr=="OW")) {
    decode_short(d);
    return true;
  }
  else
    return false;
}


// ignore a data element
void ExplicitVRLittleEndianBase::ignore_elt(DStream& d, IgnoreType mode) {
  d.invalidate_tag();
  switch (mode) {
  case group_length: decode_short(d); decode_short(d); decode_long(d); break;
  case private_elt:
  case unspecified:
  default:
    // ignore atomic VRs here - KLUDGE
    int value_length;
    bool ignore_stream;
    // ignore vr
    if (decode_vr(d)) { // Ignore Sequential VR
      value_length = decode_long(d);
      if (value_length == UndefinedLength) {
	decode_tag(d);
	while (!is_seq_delim(d)) {
	  // ignore item
	  int item_len = decode_item_header(d);
	  if (item_len != UndefinedLength) {
	    int last_pos = d.position + item_len;
	    decode_tag(d);
	    ignore_elt(d); // recursive
	    if ( last_pos < d.position )
	      throw DItemEncodingException();
	  }
	  else {
	    decode_tag(d);
	    // this may deserve its own function:  check_and_decode_item_del
	    while ( ! (decode_tag(d) == Tag(0xfffe, 0xe00d))  )  { // item delimiter
	      ignore_elt(d); // recursive
	      decode_tag(d);
	    }
	    d.invalidate_tag();
	    decode_long(d);
	  }
	  decode_tag(d);
	}
	decode_seq_delim(d);
	ignore_stream = false;
      }
      else
	ignore_stream = true;
    }
    else { // Ignore Atomic VR
      value_length = decode_short(d);
      ignore_stream = true;
    }
    if (ignore_stream) {
      char *ignore = new char[value_length];
      d.read(ignore, value_length);
      delete ignore;
    }
  };
}

// check if a data element header exists
bool ExplicitVRLittleEndianBase::check_data_elt_header(DStream& d, const Attribute & a) {
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
int ExplicitVRLittleEndianBase::decode_req_data_elt_header(DStream& d, const Attribute & a) {
  // diagnostics
  //dgn( string("Decoding Attribute: ") + a.toString() );
  // fetch the tag
  do {
    Tag tag = decode_tag(d);
    if (tag == a.tag) {
      // we have caught the correct data element
      // return value length
      int value_length;
      if (decode_vr(d))
	value_length = decode_long(d);
      else
	value_length = decode_short(d);
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
int ExplicitVRLittleEndianBase::decode_opt_data_elt_header(DStream& d, const Attribute & a) {
  // diagnostics
  //dgn( "Decoding Attribute: " + a.toString());
  // check the tag
  do {
    Tag tag = decode_tag(d);
    if (tag == a.tag) {
      // we have caught the correct data element
      // return value length
      int value_length;
      if (decode_vr(d))
	value_length = decode_long(d);
      else
	value_length = decode_short(d);
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
int ExplicitVRLittleEndianBase::decode_item_header(DStream& d) {
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

bool ExplicitVRLittleEndianBase::is_seq_delim(DStream & d)
{
  if (decode_tag(d)==Tag(0xfffe, 0xe0dd))
    return true;
  else
    return false;
}

bool ExplicitVRLittleEndianBase::decode_seq_delim(DStream & d)
{
  if ( !( decode_tag(d) == Tag(0xfffe, 0xe0dd) ))
    throw DDETypeException();
  d.invalidate_tag();
  decode_long(d);
  return true;
}

bool ExplicitVRLittleEndianBase::decode_item_delim(DStream & d)
{
  if ( ! ( decode_tag(d) == Tag(0xfffe, 0xe00d) ))
    throw DDETypeException();
  d.invalidate_tag();
  decode_long(d);
  return true;
}

