/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef Attribute_h
#define Attribute_h 1

#include "General.hxx"
#include "Tag.hxx"

class DataSet;
class Parser;
class Attribute
{
public:
  enum ReqType {t1, t1c, t2, t2c, t3, t4};

  Attribute() {}
  Attribute(Tag t, TagDef td, ReqType, int d);
  Attribute(Tag t, TagDef td, string n, ReqType, int d);
  Tag tag;			// the famous tag
  TagDef tagdef;		// tag definition: name, vr, vm
  ReqType type;			// requirement type
  string a_class;		// attribute type -- VR + VM
  int is_pass_ref;		// pass by reference?
  string a_name;		// autogen variable name
  string meta_attr_name;	// autogen meta attribute name
  int nesting;
  int attr_num;			// number of attribute within its own scope
  int is_data_set;		// does the attribute contain a data set?
  bool is_seq;			// is the VR Sequential?
  bool is_ptr;			// is it part of a pointer
  vector<int> indicator;	// the attribute is an indicator for
                                // the following modules
  vector<int> modules;		// which modules am I in?

  // CODE: SUPPORT FOR LIST OF MODULES, AS A LIST OF DATA_SETS HERE? */

  DataSet* data_set;		// then that DataSet is revealed

  bool is_multi_vm() {
    return ( (tagdef.vm.variable!=0) || ( (tagdef.vm.variable==0) && (tagdef.vm.least>1) ) );
  }

  void clean();
  void gen_member_var(DataSet&);
  void gen_sel_mod(DataSet&);
  void gen_str(DataSet&);
  void gen_abstract_member(DataSet&);
  void gen_abstract_sel_mod(DataSet&);
  void gen_abstract_str(DataSet&);
  void gen_abstract_avl(DataSet&);
  void gen_avl(DataSet&);
  void gen_tag(DataSet&);
  void gen_decoder(DataSet&, int);
  void gen_encoder(DataSet&, int);
};

#endif









