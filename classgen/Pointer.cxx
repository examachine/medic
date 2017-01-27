// Pointer.cxx: implementation of the Pointer class.
//
//////////////////////////////////////////////////////////////////////

#include "Attribute.hxx"
#include "DataSets.hxx"
#include "Parser.hxx"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Pointer::Pointer()
{

}

Pointer::Pointer(int number, string _name, int nest, const Tag& t)
  : p_number(number), name(_name), nesting(nest), tag(t)
{

}

Pointer::~Pointer()
{

}

void Pointer::gen_member_var(DataSet & scope)
{
  string bl;
  bl.append(nesting*2+2, ' ');

  (*(scope.outh)) << bl;

  *(scope.outh) << "DPtr \tp_" + scope.parser->itos(p_number) << ";\n";

}

// generate abstract selector and modifier methods
void Pointer::gen_abstract_sel_mod( DataSet & scope) {
  // KLUDGE
  //if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');

  *scope.outh << bl + "virtual const  DPtr&  sel" + name << " () const = 0;\n";
  *scope.outh << bl + "virtual void  mod" + name << "(const DPtr& a) = 0;\n";

}

// generate selector and modifier methods
void Pointer::gen_sel_mod( DataSet & scope) {
  // KLUDGE
  //if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');

  *scope.outh << bl + "const  DPtr&  sel" + name << " () const {\n"
	  << " return p_" + Parser::itos(p_number) + ";}" << endl ;
  *scope.outh << bl + "void  mod" + name << "(const DPtr& a) {\n"
	  << "    avail[0x" + Parser::itos(class_num) + "] = true;\n"
	  << bl + "  p_" + Parser::itos(p_number) + " = a;\n"
	  << bl + "}\n";

}

// generate abstract available methods
void Pointer::gen_abstract_avl( DataSet & scope) {
  // KLUDGE
  //if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');
  
  *scope.outh << bl + "virtual bool avl" + name << "() const = 0;\n";

}

// generate available methods
void Pointer::gen_avl( DataSet & scope) {
  // KLUDGE
  //if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');
  
  *scope.outh << bl + "bool avl" + name << "() const"
	  << " { return avail[0x" + Parser::itos(class_num) + "]; } \n";
}
