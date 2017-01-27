//
//
// C++ Implementation for module: IOD
//
// Description: 
//
//
// Author: exa
//
//

#include "IOD.hxx"
#include "Parser.hxx"

void IOD::add_module(Module& m, Module::ReqType req_type, int mutex)
{
  // bail out if this is a duplicate module
  if (modules.find(m.name)!=modules.end())
    return;

  modules[m.name]=&m;
  ModuleInfo mi = {req_type, mutex, number_of_modules++};
  modinfo[m.name]=mi;

  attrmap::iterator start=m.attributes.begin(), stop=m.attributes.end();
	
  for (;start != stop; start++) {
    Attribute a = start->second;
    if ( is_duplicate(a) )  {
      // Handle Duplicate Attribute
      // check overriding ***** TODO

      // Module usage
      if (start == m.attributes.begin()) { // first attribute
	attributes[a.tag].indicator.push_back(mi.index);
      }

      a.modules.push_back(mi.index);
		
    } else {
      a.attr_num = num_attr++;
      if (! a.is_ptr) {
	a.a_name = string("a_") + hack_parser->itos(a.attr_num);
	a.meta_attr_name = a.a_name + "_attr";
      } else {
	// make sure its DPtr is copied also
	//string num = hack_parser->itos(a.attr_num);
	//for (int i=0; i<4; i++)
					
      }

      // Module usage
      a.indicator.clear();
      if (start == m.attributes.begin())  // first attribute
	a.indicator.push_back(mi.index);

      a.modules.push_back(mi.index);

      add(a);
    }
  }

  list<Pointer>::iterator i2=m.pointers.begin(), j2=m.pointers.end(); 
  for (;i2 != j2; i2++) {
    Pointer p = *i2;
    add(p);
  }
}

void IOD::begin_gen(Parser* p)
{
  DataSet::begin_gen(p);
  *parser->outh << "#ifndef " + name << "_Interface" << endl;
  *parser->outh << "#define " + name << "_Interface" << endl;
  *parser->outh << "// IOD " + name << endl << endl;
}

void IOD::gen_class()
{
  DataSet::gen_class();  
}

void IOD::gen_includes()
{
  DataSet::gen_includes();
  modmap::iterator i=modules.begin(), j=modules.end();
  for (;i!=j;i++) {
    if (parser->platform==Parser::gxx) {
      *parser->outh << "#include \"" << i->second->name << ".hxx\"" << endl;
    } else {
      *parser->outh << "#include \"" << i->second->name << ".h\"" << endl;
    }
  }
}

void IOD::gen_bases(bool has_abstract)
{
  *parser->outh << "\n  :";
  modmap::iterator i=modules.begin(), j=modules.end();
  *parser->outh << " public Abstract" << i->second->name;
  for (i++; i!=j; i++) {
    *parser->outh << "\n  , public Abstract" << i->second->name;
  }
}

void IOD::gen_constructor()
{
  string bl; bl.append(nesting*2+2, ' ');
  *parser->outh << bl << "  "
		<< name << "() { avail.resize(" << attributes.size() << ");\n"
		<< "  skip.resize(" << modules.size() << ");\n" << "  }\n"; 
};

// generate implementation body
void IOD::gen_imp_body()
{
  DataSet::gen_imp_body();
  // skip flags
  string bl; bl.append(nesting*2+2, ' ');
  *parser->outh << bl << "  vector<bool> skip;\n";
}

void IOD::gen_coder()
{
  DataSet::gen_coder();
}

void IOD::end_gen()
{
  DataSet::end_gen();

  *parser->outh << "// end of IOD \n\n\n";
  *parser->outh << "#endif" << endl;

}
