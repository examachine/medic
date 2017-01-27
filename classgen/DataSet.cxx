/*
** Implementation file for module
**
**
**
** exa
**
*/

#include "DataSet.hxx"
#include "Parser.hxx"

DataSet::DataSet(string n, int d)
  : name(n), nesting(d), attr_num(0), generated(false)
{}

DataSet::~DataSet() {
  attrmap::iterator start=attributes.begin(), stop=attributes.end();
  for (;start != stop; start++)
    (*start).second.clean();
}

void DataSet::add(Attribute& attr) {
  if ( is_duplicate(attr) ) {
    cerr << "Duplicate Attribute " +
      attributes[attr.tag].tagdef.name +
      " in DataSet " + name;
  }

  if (attr.tagdef.name=="ReferencedOverlaySequence") {
    cerr << "cuyaaaaak!" << endl;
    cerr << "dataset " << name << " attr " << attr.tagdef.name
	 << " with " << attr.tag << endl;
#ifndef _MSC_VER
    cerr << "in modules " << attr.modules << endl;
#endif
  }
  string oldname = attr.tagdef.name;
  while (attribute_names.find(attr.tagdef.name)!=attribute_names.end())
    attr.tagdef.name += '0';
//   if (oldname!=attr.tagdef.name)  cerr << name << "::" << attr.tagdef.name << endl;
  attributes[attr.tag]=attr;
  attribute_names[attr.tagdef.name]=&attributes[attr.tag];
}

void DataSet::add(Pointer p)		// add a new attribute to dataset
{
//   list<Pointer>::iterator start2 = pointers.begin(), stop2 = pointers.end();
//   for (;start2 != stop2; start2++)
//     if ( start2->p_number == p.p_number )
//       parser->warn("DataSet: " + name + " duplicate pointer " +
// 		   p.name);
//   // BUG: duplicate pointers?
//   if (name=="USImageIOD") {
//     cerr << "DataSet: " + name + " has a pointer " << p.p_number
// 	 << "named "  + p.name << "with tag " << p.tag << endl;
//   }
  pointers.push_back(p);
}

bool DataSet::is_duplicate(Attribute & a)
{
  return ( attributes.find(a.tag) != attributes.end() );
}

void DataSet::begin_gen(Parser *p) {
  parser = p;
  interface_filename = parser->interface_filename;
  implementation_filename = parser->implementation_filename;
  outc = parser->outc;
  outh = parser->outh;
  if (parser->platform==Parser::vc5)
    templ_out = parser->outc;
  else
    templ_out = new ostrstream();
}

void DataSet::end_gen() {
  if (parser->platform==Parser::vc5)
    ;
  else {
    *templ_out << ends;
    *parser->outh << dynamic_cast<ostrstream*>(templ_out)->str();
    delete templ_out;
  }
}

void DataSet::begin_gen_nested(DataSet &d)
{
  parser = d.parser;
  interface_filename = d.parser->interface_filename;
  implementation_filename = d.parser->implementation_filename;
  outc = d.outc;
  outh = d.outh;
  templ_out = d.templ_out;
}

void DataSet::enter_scope(string prefix)
{
  decl_scope = parser->scope;
  if (parser->scope!="")
    parser->scope += "::";
  parser->scope += prefix + name;
}

void DataSet::exit_scope()
{
  parser->scope = decl_scope;
}

// code generation
// a data set needs to know its scope
void DataSet::gen_class() {

  if (generated) return; // bail out if already generated
  enter_scope();

  if (parser->platform==Parser::gxx) {
  } else if (parser->platform==Parser::vc5) {
  }

  attrmap::iterator start=attributes.begin(), stop=attributes.end();
  string bl; bl.append(nesting*2, ' ');

  // generate pre-amble
  gen_class_header();

  if (parser->platform==Parser::vc5)
    gen_vc_abstract_coder();

  // generate declaration
  gen_class_decl();

  // generate body
  gen_imp_body();

  // end class declaration
  *parser->outh << bl << "}; \n";

  // generate operators
//   *parser->outh << bl << "inline bool operator ==(" << name <<" a, " <<
//     name << " b) {return false;}\n";
//   *parser->outh << bl << "inline bool operator !=(" << name <<" a, " <<
//     name << " b) {return false;}\n";
//   *parser->outh << bl << "inline bool operator <(" << name <<" a, " <<
//     name << " b) {return false;}\n";
//   *parser->outh << bl << "inline bool operator >(" << name <<" a, " <<
//     name << " b) {return false;}\n";

  generated = true;
  exit_scope();
}

// abstract class gen
// must be called after normal class generator
// assumed that they are in the same file
void DataSet::gen_abstract_class() {

  if (generated) return;
  enter_scope("Abstract");

  if (parser->platform==Parser::gxx) {
  } else if (parser->platform==Parser::vc5) {
  }

  attrmap::iterator start=attributes.begin(), stop=attributes.end();
  string bl; bl.append(nesting*2, ' ');

  // header
  gen_class_header();

  // generate declaration
  gen_class_decl("Abstract");

  *parser->outh << bl << "public:\n";
  			
  // generate members bers
  for (start=attributes.begin(); start != stop; start++)
    (*start).second.gen_abstract_member(*this);

  // generate selector/modifier methods
  for (start=attributes.begin(); start != stop; start++)
    (*start).second.gen_abstract_sel_mod(*this);

  // generate str methods of attributes
  for (start=attributes.begin(); start != stop; start++)
    (*start).second.gen_abstract_str(*this);

  // generate avl methods of attributes
  for (start=attributes.begin(); start != stop; start++)
    (*start).second.gen_abstract_avl(*this);

  // generate pointer sel/mod
  list<Pointer>::iterator start2 = pointers.begin(), stop2 = pointers.end();
  for (;start2 != stop2; start2++)
    start2->gen_abstract_sel_mod(*this);

  // generate pointer avl
  start2 = pointers.begin();
  for (;start2 != stop2; start2++)
    start2->gen_abstract_avl(*this);

  // end class declaration
  *parser->outh << bl << "}; \n\n";

  exit_scope();
  enter_scope();

  if (parser->platform==Parser::vc5)
    gen_vc_abstract_coder();

  // generate declaration
  gen_class_decl("", true );

  // generate body
  gen_imp_body();

  // end class declaration
  *parser->outh << bl << "}; \n";

  generated = true;
  exit_scope();
}


//VC abstract coder
void DataSet::gen_vc_abstract_coder()
{
  string abstract_coder = scope + "AbstractCoder";
  string bl; bl.append(nesting*2, ' ');
  // forward declaration
  *parser->outh << "class " + scope + ";" << endl;
  // abstract class
  *parser->outh << bl + "class " <<  abstract_coder << " {\n" <<
    bl + "public:\n";
  // decoder
  *parser->outh << bl + "  virtual void decode(DStream&," + scope  + "&) = 0;\n";  
  // decoder
  *parser->outh << bl + "  virtual void encode(DStream&," + scope  + "&) = 0;\n";  
  *parser->outh << bl + "}; \n";
}

// beginning of a class
void DataSet::gen_class_header()
{
  attrmap::iterator start=attributes.begin(), stop=attributes.end();
  string bl; bl.append(nesting*2, ' ');

#ifdef VC
  if (*parser->outc); // *** VC5.0 BUG!!!
#endif

  if (nesting==0)
    *parser->outc << "// DataSet " << name << endl;
  else
    *parser->outc << "// Nested DataSet " << name << endl;

  // include relevant header files
  gen_includes();

  // if VC5, do not create nested classes
  if (parser->platform==Parser::vc5) {
    // instead do recursion pre-order
    for (start=attributes.begin();start != stop; start++)
      if (start->second.is_data_set) {
	start->second.data_set->begin_gen(parser);
	start->second.data_set->gen_class();
      }
  }
}

void DataSet::gen_class_decl(string prefix, bool abstract)
{
  string bl; bl.append(nesting*2, ' ');
  // begin class declaration
  *parser->outh << bl << "class " << prefix+name;
  gen_bases(abstract);
  *parser->outh << " {\n" << bl;
}

// generate implementation body
void DataSet::gen_imp_body() {
  attrmap::iterator start=attributes.begin(), stop=attributes.end();
  string bl; bl.append(nesting*2, ' ');

  // private section
//   *parser->outh << bl << "private:\n";
  *parser->outh << bl << "public:\n"; // MEGA KLUDGE!!!

  // generate attributes
  for (start=attributes.begin();start != stop; start++)
    (*start).second.gen_member_var(*this);

  // generate pointer attributes
  list<Pointer>::iterator start2 = pointers.begin(), stop2 = pointers.end();
  for (;start2 != stop2; start2++)
    start2->gen_member_var(*this);
  
  // generate tags of attributes
  for (start=attributes.begin();start != stop; start++)
    (*start).second.gen_tag(*this );
  
  // vector of available attributes
  *parser->outh << bl << "  vector<bool> avail;\n";

  *parser->outh << bl << "public:\n";
  
  // constructor
  gen_constructor();

  // generate selector/modifier methods
  for (start=attributes.begin(); start != stop; start++)
    (*start).second.gen_sel_mod(*this);

  // generate pointer sel/mod
  start2 = pointers.begin();
  for (;start2 != stop2; start2++)
    start2->gen_sel_mod(*this);

  // generate pointer avl
  start2 = pointers.begin();
  for (;start2 != stop2; start2++)
    start2->gen_avl(*this);

  // generate str method of class
  gen_str();

  // generate str methods of attributes
  for (start=attributes.begin(); start != stop; start++)
    (*start).second.gen_str(*this);

  // generate avl methods of attributes
  for (start=attributes.begin(); start != stop; start++)
    (*start).second.gen_avl(*this);

  // generate set method of class
  gen_set();

  // generate nested coder class
//   if (parser->platform==Parser::vc5) {
//   }
  *parser->outh << bl << "public:\n";
  gen_coder();

}

void DataSet::gen_includes() {
  if (parser->platform==Parser::gxx) {
    // include if top-level class
    if (nesting==0) {
      *parser->outh << "#include \"KernelAutoGenInterface.hxx\"" << endl << endl;
      *parser->outc << "#include \"" << name << ".hxx\"" << endl;
    }
  }
  else if (parser->platform==Parser::vc5) {
    // include if top-level class
    if (nesting==0) {
      *parser->outh << "#include \"KernelAutoGenInterface.hxx\"" << endl << endl;
      *parser->outc << "#include \"BaseLib.hxx\"" << endl;
      //*parser->outc << "#include \"StdAfx.hxx\"" << endl;
      *parser->outc << "#pragma message ( __FILE__ \": compiling interface\" )" << endl;
      *parser->outc << "#include \"" << name << ".h\"" << endl;
      *parser->outc << "#pragma message ( __FILE__ \": compiling implementation\" )" << endl;
    }
  }
}

void DataSet::gen_bases(bool abstract_base) {
  if (abstract_base)
    *parser->outh << " : public Abstract" << name;
}

void DataSet::gen_constructor() {
  string bl; bl.append(nesting*2, ' ');
  *parser->outh << bl << "  " << name << "() { avail.resize(" << attributes.size() << "); }\n"; 
};

void DataSet::gen_coder() {
  string bl; bl.append(nesting*2+2, ' ');
  const string & scope = parser->scope;

  if (parser->platform==Parser::gxx) {
  }
  else if (parser->platform==Parser::vc5) {
//     decl_scope = "";
//     scopestr+="::";
  }
  attrmap::iterator start=attributes.begin(), stop=attributes.end();

  string abstract_coder;
  if (parser->platform == Parser::gxx) {
    // abstract class
    *parser->outh << bl + "class AbstractCoder {\n" <<
      bl + "public:\n";
    // decoder
    *parser->outh << bl + "  virtual void decode(DStream&," + name  + "&) = 0;\n";  
    // decoder
    *parser->outh << bl + "  virtual void encode(DStream&," + name + "&) = 0;\n";  
    *parser->outh << bl + "}; \n";
    abstract_coder = "AbstractCoder";
  }
  else
    abstract_coder = scope + "AbstractCoder";

  // class declaration
  if (parser->platform==Parser::vc5) {
    *parser->outh << bl + "template<class TS> class " << decl_scope <<
      "Coder : public " + abstract_coder + " {\n" <<
      bl + "public:\n";
  }
  else {
    *outh << bl + "template<class TS> class "
	  << "Coder : public " + abstract_coder + "{"
	  << endl << bl + "public:\n";
  }

  // constructor
  *parser->outh << bl + "  Coder() {}\n";


  // decoder
  *parser->outh << bl + "  void decode(DStream&," + scope  + "&);\n";  
  if (parser->platform==Parser::vc5) {
    *parser->outc << "template<class TS> void " << scope
		  << "Coder<TS>::decode(DStream& ds," + scope  + "& obj) {\n";
  } else {
    *templ_out << "template<class TS> void " << scope
	      << "::Coder<TS>::decode(DStream& ds," + scope  + "& obj) {\n";
  }

  if (!start->second.modules.empty())
    *templ_out << "  vector<bool>::iterator i1=obj.skip.begin(), j1 = obj.skip.end();\n"
	       << "  for (;i1!=j1;i1++) *i1 = false;\n";
  *templ_out << "  vector<bool>::iterator i2=obj.avail.begin(), j2 = obj.avail.end();\n"
	     << "  for (;i2!=j2;i2++) *i2 = false;\n";
  int c_index;
  for (c_index=0;start != stop; start++, c_index++)
    (*start).second.gen_decoder(*this, c_index);
  *templ_out << "};\n";

  // encoder
  *parser->outh << bl + "  void encode(DStream&," + scope  + "&);\n";  
  if (parser->platform==Parser::vc5) {
    *parser->outc << "template<class TS> void " << scope
		  << "Coder<TS>::encode(DStream& ds," + scope  + "& obj) {\n";
  } else {
    *templ_out << "template<class TS> void " << scope
	       << "::Coder<TS>::encode(DStream& ds," + scope  + "& obj) {\n";
  }
  for (c_index=0, start = attributes.begin(); start != stop; start++, c_index++)
    start->second.gen_encoder(*this, c_index);
  *templ_out << "};\n";

  *parser->outh << bl + "}; \n";


  // template access and instantiation

  if (parser->platform==Parser::vc5) {
    *parser->outh << bl << "friend class " << "Coder<"
		  << "ImplicitVRLittleEndian" << ">;" << endl;
    *parser->outc << "template class " << scope << "Coder<"
		  << "ImplicitVRLittleEndian" << ">;" << endl;

    *parser->outh << bl << "friend class " << "Coder<"
		  << "ExplicitVRLittleEndian" << ">;" << endl;
    *parser->outc << "template class " << scope << "Coder<"
		  << "ExplicitVRLittleEndian" << ">;" << endl;

    *parser->outh << bl << "friend class " << "Coder<"
		  << "ExplicitVRBigEndian" << ">;" << endl;
    *parser->outc << "template class " << scope << "Coder<"
		  << "ExplicitVRBigEndian" << ">;" << endl;

    *parser->outh << bl << "friend class " << "Coder<"
		  << "JPEGBaseLineP1" << ">;" << endl;
    *parser->outc << "template class " << scope << "Coder<"
		  << "JPEGBaseLineP1" << ">;" << endl;

    *parser->outh << bl << "friend class " << "Coder<"
		  << "JPEGExtendedP4" << ">;" << endl;
    *parser->outc << "template class " << scope << "Coder<"
		  << "JPEGExtendedP4" << ">;" << endl;

    *parser->outh << bl << "friend class " << "Coder<"
		  << "JPEGLosslessNHFOP14" << ">;" << endl;
    *parser->outc << "template class " << scope << "Coder<"
		  << "JPEGLosslessNHFOP14" << ">;" << endl;
  } else {
//     *parser->outh << bl << "friend class " << "Coder<"
// 		  << "ImplicitVRLittleEndian" << ">;" << endl;
//     *parser->outh << "template class " << scope << "::Coder<"
// 		  << "ImplicitVRLittleEndian" << ">;" << endl;

//     *parser->outh << bl << "friend class " << "Coder<"
// 		  << "ExplicitVRLittleEndian" << ">;" << endl;
//     *parser->outh << "template class " << scope << "::Coder<"
// 		  << "ExplicitVRLittleEndian" << ">;" << endl;

//     *parser->outh << bl << "friend class " << "Coder<"
// 		  << "ExplicitVRBigEndian" << ">;" << endl;
//     *parser->outh << "template class " << scope << "::Coder<"
// 		  << "ExplicitVRBigEndian" << ">;" << endl;

//     *parser->outh << bl << "friend class " << "Coder<"
// 		  << "JPEGBaseLineP1" << ">;" << endl;
//     *parser->outh << "template class " << scope << "::Coder<"
// 		  << "JPEGBaseLineP1" << ">;" << endl;

//     *parser->outh << bl << "friend class " << "Coder<"
// 		  << "JPEGExtendedP4" << ">;" << endl;
//     *parser->outh << "template class " << scope << "::Coder<"
// 		  << "JPEGExtendedP4" << ">;" << endl;

//     *parser->outh << bl << "friend class " << "Coder<"
// 		  << "JPEGLosslessNHFOP14" << ">;" << endl;
//     *parser->outh << "template class " << scope << "::Coder<"
// 		  << "JPEGLosslessNHFOP14" << ">;" << endl;
  }

  // SOP_TS's for double dispatch
  if (parser->platform==Parser::vc5) {
    *parser->outh << bl << "static SOP_TSs<" + scope + ","
      + scope + "::" + abstract_coder + "> sop_tss;" << endl;
    *parser->outc << bl << "SOP_TSs<" + scope + ","
      + scope + "::" + abstract_coder + "> " + scope + "::sop_tss;" <<
        endl;
  }
}

void DataSet::gen_set() {
  const string & scope = parser->scope;
  string bl; bl.append(nesting*2+2, ' ');

  if (parser->platform==Parser::gxx) {
  }
  else if (parser->platform==Parser::vc5) {
    decl_scope = "";
//    scopestr+="::" ;
  }
  attrmap::iterator start=attributes.begin(), stop=attributes.end();

  // we're already in the scope, so no need to mention declaration scope
  *parser->outh << bl << "void set(" << name << "&);\n";

  if (parser->platform==Parser::vc5) {
    *parser->outc << "void " + decl_scope + "::" + name + "::"
		  << "set(" << decl_scope + "::" + name + "& a) {\n";
  } else {
    *parser->outc << "void " + scope + "::"
		  << "set(" << scope + "& a) {\n";
  }

  for (; start != stop; start++) {
    if (start->second.tag.group.x) continue; // KLUDGE
    string aname = start->second.tagdef.name;
    *parser->outc << "  if ( a.avl" + aname + "() )" << endl;
    *parser->outc << "    mod" + aname + "( a.sel" + aname + "() ); " << endl;
  }

  *parser->outc << endl << "}" << endl;
}

void DataSet::gen_str() {
  string scopestr = scope;
  string bl; bl.append(nesting*2+2, ' ');

  if (parser->platform==Parser::gxx) {
  }
  else if (parser->platform==Parser::vc5) {
    //    decl_scope = "";
    scopestr+="::";
  }
  attrmap::iterator start=attributes.begin(), stop=attributes.end();

  *parser->outh << bl << "string toString() {\n";
  *parser->outh << bl << "  string s;\n";
  for (; start != stop; start++) {
    if (start->second.tag.group.x) continue;
    *parser->outh << bl << "  s += " 
	    << "\"" << start->second.tagdef.name << ":\" + "
	    << "str" << start->second.tagdef.name << "()"
	    <<  " + \"\\n\" ;\n" ;
  }
  *parser->outh << bl << "  return s;\n";
  *parser->outh << bl << "};\n";
}

bool DataSet::has_class_ui(string name)
{
  return (recog_class_uis.find(name)!=recog_class_uis.end());
}

void DataSet::add_class_ui(string name)
{
  if (has_class_ui(name))
    cerr << "add_class_ui: error " << endl;

  recog_class_uis.insert(name);
}
