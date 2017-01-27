// Pointer.hxx: interface for the Pointer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef Pointer_Interface
#define Pointer_Interface

class Parser;

class Pointer  
{
public:
  Pointer();
  Pointer(int, string, int, const Tag& tag);
  virtual ~Pointer();

  void gen_member_var(DataSet &);
  void gen_abstract_sel_mod(DataSet &);
  void gen_sel_mod(DataSet &);
  void gen_abstract_avl(DataSet &);
  void gen_avl(DataSet &);

  int p_number;
  string name;
  int nesting;
  Tag tag;

  int class_num;
  int instance_num;
};

#endif
