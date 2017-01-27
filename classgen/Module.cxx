//
//
// C++ Implementation for module: Module
//
// Description: 
//
//
// Author: exa
//
//

#include "Module.hxx"
#include "Parser.hxx"


void Module::begin_gen(Parser* p)
{
  DataSet::begin_gen(p);
  *parser->outh << "#ifndef " + name << "_Interface" << endl;
  *parser->outh << "#define " + name << "_Interface" << endl << endl;
  *parser->outh << "// Module " + name << endl << endl;
}

void Module::gen_class()
{
  //DataSet::gen_class(p);
  DataSet::gen_abstract_class();
}

void Module::gen_coder()
{
  DataSet::gen_coder();
}

void Module::end_gen()
{
  DataSet::end_gen();

  *parser->outh << "\n// end of module \n\n\n";
  *parser->outh << "#endif" << endl;

}

