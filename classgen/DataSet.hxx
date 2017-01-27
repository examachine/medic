/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef DataSet_h
#define DataSet_h 1

#include "General.hxx"
#include "Attribute.hxx"
#include "Pointer.hxx"

class Parser;
extern Parser* hack_parser;

typedef map<Tag, Attribute, less<Tag> > attrmap;
typedef map<string, Attribute*> attrnames;

// dicom dataset
// simple recursion tree
class DataSet
{
public:
  DataSet() : generated(false) {}
  DataSet(string, int d);	// a dataset with a certain nesting depth...
  ~DataSet();
  string name;			// name of data set
  string decl_scope;            // C++ scope in which this dataset was declared
  string scope;			// C++ scope name
  int nesting;			// nesting depth
  int attr_num;			// current attribute number
  int data_set_number;		// which dataset is this? **** NOT IMPLEMENTED
  bool generated;		// has this class already been generated?
  attrmap attributes;		// map of attributes
  attrnames attribute_names;	// attribute names
  list<Pointer> pointers;	// pointers

  bool is_duplicate(Attribute &);

  Parser *parser;
  virtual void begin_gen(Parser*); // begin code generation
  virtual void begin_gen_nested(DataSet &);
  virtual void gen_class(); // gen corresponding class
  virtual void gen_abstract_class(); // gen corresponding class with pure virtual functions
  virtual void gen_vc_abstract_coder(); // gen abstract coder for VC
  virtual void gen_class_header();
  virtual void gen_class_decl(string = "", bool = false);
  virtual void gen_includes();
  virtual void gen_bases(bool);
  virtual void gen_constructor();
  virtual void gen_imp_body();
  virtual void gen_coder(); // gen coder class
  virtual void gen_set(); // gen set method
  virtual void gen_str(); // gen toString method
  virtual void end_gen(); // end code generation
  virtual void add(Attribute&);	// add a new attribute to dataset
  virtual void add(Pointer);	// add a new pointer attribute to dataset

  bool has_class_ui(string name); // parsing aid for pointer recognition
  void add_class_ui(string name);

  string interface_filename, implementation_filename;
  ostream *outh, *outc, *templ_out;	// intf, impl, template impl output

private:
  void enter_scope(string prefix="");
  void exit_scope();
  set<string> recog_class_uis;
};

#endif
