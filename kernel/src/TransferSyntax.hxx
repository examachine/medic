/*
** Interface file for TransferSyntax module
**
**
**
** exa
**
*/

#ifndef TransferSyntax_Interface
#define TransferSyntax_Interface 1

#include "General.hxx"
#include "Tag.hxx"
#include "DStream.hxx"
#include "DException.hxx"

// Meta Data Element class
class DataElement {
public:
  DataElement() {}
};

// Value Multiplicity
class VM {
public:
  enum Type {single, fixed, range, var, evenvar};
  
  VM() {}
  VM(Type t, int l = 0, int u = 0) : type(t), lower(l), upper(u) {}

  Type type;
  int lower, upper; // bounds on number of values
  string toString() const {
    return string("(") + conv_to_string(type) + string(",") +
      conv_to_string(lower) + string(",") + conv_to_string(upper) + string(")");
  }
};

// Meta Attribute class
// This will exist within DataSet generating classes
class Attribute {
public:
  Attribute() {}
  Attribute(Tag c1, char* _name, char c2[3], VM c3, bool c4)
    : tag(c1), name(_name), vm(c3), sequence(c4) {
    strcpy(vr, c2);
  }

  Tag tag;			// tag of the attribute
  string name;			// name of attribute
  char vr[3];			// VR of attribute
  VM vm;			// VM of attribute
  bool sequence;		// is it a sequence?
  //type;	// C++ type of attribute
  // member pointer *** write this one
	string toString() const;
};

// base transfer syntax class for decode/encode operations
class TransferSyntax {
public:
  enum {TagNotFound = -2, UndefinedLength = -1};	// -1 = 0xffffffff

	TransferSyntax() {}

	static void dgn(string &s);

};


#endif
