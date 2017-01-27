//
//
// C++ Implementation for module: Message
//
// Description: 
//
//
// Author: exa
//
//

#include "Message.hxx"
#include "Parser.hxx"

void Message::begin_gen(Parser* p)
{
  DataSet::begin_gen(p);
  
  *parser->outh << "#ifndef " + name << "_Interface" << endl;
  *parser->outh << "#define " + name << "_Interface" << endl << endl;
  *parser->outh << "// Message " + name << endl << endl;
}

/*void Message::gen_class(Parser& p) {
  DataSet::gen_class(p);
  //DataSet::gen_abstract_class(p);
}*/

//void Message::gen_coder(Parser& p) {
//  DataSet::gen_coder(p);
//}

void Message::end_gen()
{
  DataSet::end_gen();

  *parser->outh << "\n// end of Message \n\n\n";
  *parser->outh << "#endif" << endl;
}
