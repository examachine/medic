/*
** Implementation file for module
**
**
**
** exa
**
*/

#include "Attribute.hxx"
#include "DataSets.hxx"
#include "Parser.hxx"

Attribute::Attribute(Tag t, TagDef td, ReqType r, int d)
  : tag(t), is_data_set(0), tagdef(td), type(r), nesting(d)
{
  data_set = NULL;

  // Determine VR-VM class of attribute
  a_class = tagdef.vr;
  VM& vm=tagdef.vm;
  if (vm.variable==0)
    if (vm.least!=1)
      a_class+="f<0x"+Parser::itos(vm.least)+">"; else; // dangling
  else if (vm.variable==1)
    a_class+="r<0x"+Parser::itos(vm.least)+",0x"+Parser::itos(vm.most)+'>';
  else
    a_class+="v";

  // Determine parameter passing convention for this attribute
  if (
      //                   3?
      (tagdef.vm.variable <= 1) && (tagdef.vm.most <=2) &&
      ( (tagdef.vr=="AT") || 
	(tagdef.vr=="FL") || 
	(tagdef.vr=="FD") || 
	(tagdef.vr=="SL") || 
	(tagdef.vr=="SS") || 
	(tagdef.vr=="UL") || 
	(tagdef.vr=="US") ) )
    is_pass_ref = 0;
  else
    is_pass_ref = 1;
}

Attribute::Attribute(Tag t, TagDef td, string name, ReqType r, int d)
  : tag(t), is_data_set(1), tagdef(td), type(r), nesting(d) {
  data_set = new DataSet(name, d+1);
  a_class = "SQ<" + data_set->name + '>';
}

void Attribute::clean() {
  if (is_data_set)
    delete data_set;
}

void Attribute::gen_member_var( DataSet & scope)
{

  // KLUDGE
  if (tag.group.x) return;
	
  string bl;
  bl.append(nesting*2+2, ' ');

  // gen instance variable
  if (scope.parser->platform != Parser::vc5)
    if (is_data_set) {
      // gen declarations of nested data set
      data_set->begin_gen_nested(scope);
      data_set->gen_class();
    }

  if (!is_ptr) {
	
    (*(scope.outh)) << bl;

    *(scope.outh) << a_class + " \t" + a_name  << ";\n";
  }

}

// generate selector and modifier methods
void Attribute::gen_sel_mod( DataSet & scope)
{
//   if (tagdef.name=="ReferencedOverlaySequence0") {
//     cerr << "imdaaaaat**!" << endl;
//     cerr << " attr " << tagdef.name << endl;
//   }

  // KLUDGE
  if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');

  string ref;
  if (is_pass_ref) ref = '&';
  
  /*
   *scope.outh << bl + "const " + a_class + ref + " sel" + tagdef.name << "() const {\n"
   << bl + "  if (avail[0x" + Parser::itos(attr_num) + "]) "
   << bl + "return " + a_name + ";\n"
   << bl + "  else return " + a_class + "();\n"
   << bl + "}\n";
  */
//   if (tagdef.name=="ReferencedOverlaySequence") {
//     cerr << "imdaaaaat!" << endl;
//     cerr << " attr " << tagdef.name << endl;
//   }

  *scope.outh << bl + "const " + a_class + ref + " sel" + tagdef.name << "() const {\n"
	  << bl + "  return " + a_name + ";\n"
	  << bl + "}\n";


  *scope.outh << bl + "void mod" + tagdef.name << "( const "
	  << a_class + ref + " a) {\n"
	  << "    avail[0x" + Parser::itos(attr_num) + "] = true;\n"
	  << bl + "  " + a_name + " = a;\n"
	  << bl + "}\n";

  if ( is_seq || is_multi_vm() )
    *scope.outh << bl + a_class + ref + " ref" + tagdef.name << "() {"
	    << bl + " return " + a_name + ";}\n";

}

// generate abstract member
void Attribute::gen_abstract_member( DataSet & scope)
{

  // KLUDGE
  if (tag.group.x) return;
	
  string bl;
  bl.append(nesting*2+2, ' ');

  // gen instance variable
  if (scope.parser->platform != Parser::vc5)
    if (is_data_set) {
      // gen declarations of nested data set
      data_set->begin_gen_nested(scope);
      data_set->gen_class();
    }

}

// generate abstract selector and modifier methods
void Attribute::gen_abstract_sel_mod( DataSet & scope)
{
  // KLUDGE
  if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');

  string ref;
  if (is_pass_ref) ref = '&';
  
  *scope.outh << bl + "virtual const " + a_class + ref + "  sel" + tagdef.name << " () const = 0;\n";
  *scope.outh << bl + "virtual void  mod" + tagdef.name << "(const "
	  << a_class + ref + " a) = 0;\n";

  if ( is_seq || is_multi_vm() ) {
    *scope.outh << bl + "typedef " + a_class + ' ' + tagdef.name + "_t;\n";
    *scope.outh << bl + "virtual " + a_class + ref + " ref" + tagdef.name << "() = 0;\n";
  }
}

// generate abstract available methods
void Attribute::gen_abstract_avl( DataSet & scope)
{
  // KLUDGE
  if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');
  
  *scope.outh << bl + "virtual bool avl" + tagdef.name << "() const = 0;\n";

}

// generate available methods
void Attribute::gen_avl( DataSet & scope)
{
  // KLUDGE
  if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');
  
  *scope.outh << bl + "bool avl" + tagdef.name << "() const"
	  << " { return avail[0x" + Parser::itos(attr_num) + "]; } \n";

}

// human readable form
void Attribute::gen_str( DataSet & scope)
{
  // KLUDGE
  if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');

  // KLUDGE
  if (tag.group.x) {
    *scope.outh << bl + "string str" + tagdef.name << "() { return \"NOT IMPLEMENTED\"; }\n";
    return;
  }

  *scope.outh << bl + "string str" + tagdef.name << "() { return " << a_name << ".toString(); }\n";
}

// abstract human readable form
void Attribute::gen_abstract_str( DataSet & scope)
{
  // KLUDGE
  if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');

  *scope.outh << bl + "virtual string str" + tagdef.name << "() = 0;\n";
}

// generate tags of attributes
void Attribute::gen_tag(DataSet & scope)
{
  // KLUDGE
  if (tag.group.x) return;

  string bl; bl.append(nesting*2+2, ' ');
  *scope.outh << bl << "static const Attribute " << meta_attr_name << ";\n";
  *scope.outc << "const Attribute " << scope.scope << "::" << meta_attr_name;
  *scope.outc << "(Tag(0x" << Parser::itos(tag.group.number)
	  << ",0x" << Parser::itos(tag.element.number)
	  << "), \"" << tagdef.name
	  << "\", \"" << tagdef.vr
	  << "\", " << "VM(";
  switch (tagdef.vm.variable) {
  case 0: {
    if (tagdef.vm.least==1)
      *scope.outc << "VM::single";
    else
      *scope.outc << "VM::fixed," << tagdef.vm.least;
  } break;
  case 1: *scope.outc << "VM::range," << tagdef.vm.least <<
	    ", " << tagdef.vm.most; break;
  case 2:  *scope.outc << "VM::var"; break;
  case 3:  *scope.outc << "VM::evenvar"; break;
  }
  *scope.outc << "), ";
  if (is_seq)
    *scope.outc << "true";
  else
    *scope.outc << "false";
  *scope.outc << ");" << endl;
}

void Attribute::gen_decoder(DataSet & scope, int c_index)
{
  // KLUDGE
  if (tag.group.x) return;

  string coder_class;     	// return type of decoder method
  int assert_condition;		// assert a condition?
  string dcd_mode;		   // decode mode

  if (scope.parser->platform==Parser::gxx) {
    // *** NOT IMPLEMENTED
    // coder_class = a_class + "Coder<TS>";
    // kludge
    // these coder classes declared elsewhere
    if (is_data_set)		// SQ <--> Attribute contains data set
      coder_class = a_class + "::Coder<TS>";
    else
      coder_class = a_class + "::Coder<TS>";
  }
  else if (scope.parser->platform==Parser::vc5) {
    // these coder classes declared elsewhere
    if (is_data_set)		// SQ <--> Attribute contains data set
      coder_class = a_class + "::Coder<TS>";
    else
      coder_class = a_class + "::Coder<TS>";
  }

  // **** HANDLE REF HERE ALSO ??

  string c_name = "c_" + scope.parser->itos(c_index);

  *scope.templ_out << "  " + coder_class  + " " + c_name + ";\n";

  if (type == t1) {
    assert_condition = false;
    dcd_mode = "mandatory";
  }
  else if (type == t1c) {
    assert_condition = true;
    dcd_mode = "mandatory";
  }
  else if (type == t2) {
    assert_condition = false;
    dcd_mode = "required";
  }
  else if (type == t2c) {
    assert_condition = true;
    dcd_mode = "required";
  }
  else if (type == t3) {
    assert_condition = false;
    dcd_mode = "optional";
  }

  // KLUDGE!! REMOVE THIS IN THE FUTURE
  if (assert_condition) {
    assert_condition = false;
    dcd_mode = "optional";
  }

  if (assert_condition)
    *scope.templ_out << "  if (0) {\n";

  if (!indicator.empty()) {
    string s_name = a_name; s_name[0] = 's';
    *scope.templ_out <<
      "  bool " << s_name << " = !TS::check_data_elt_header(ds,obj." << meta_attr_name << ");\n";
    vector<int>::iterator i1=indicator.begin(), j1=indicator.end();
    for (;i1!=j1;i1++) {
      *scope.templ_out <<
	"  obj.skip[" << *i1 << "] = " << s_name << ";" << endl;
    }
  }

  // CODE: what's goin' on here? ;)
  bool skip_flag = false;
  if ((!modules.empty()) /*&& indicator.empty()*/ && (dcd_mode[0]=='m' || dcd_mode[0]=='r')) {
    *scope.templ_out << "  if (obj.skip[" << modules[0] << "]";
    int j2 = modules.size();
    for (int i2=1; i2< j2; i2++)
      *scope.templ_out << " || obj.skip[" << modules[i2] << "]";
    *scope.templ_out << ")\n";
    *scope.templ_out << "  obj.avail[0x" << scope.parser->itos(attr_num) << "] = ";
    *scope.templ_out <<
      c_name + ".decode_optional"+
      "(ds, obj." + a_name + ", obj."+ meta_attr_name + ");\n";
    *scope.templ_out << "else {\n";
    skip_flag = true;
  }

  switch (dcd_mode[0]) {
  case 'm':
    *scope.templ_out <<
      "  " + c_name + ".decode_" + dcd_mode +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name + ");\n";
    *scope.templ_out << "  obj.avail[0x" << scope.parser->itos(attr_num) << "] = true;\n";
    break;
  case 'r':
  case 'o':
    *scope.templ_out << "  obj.avail[0x" << scope.parser->itos(attr_num) << "] = ";
    *scope.templ_out <<
      c_name + ".decode_" + dcd_mode +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name +");\n";
    break;
  }
  if ( skip_flag )
    *scope.templ_out << "  }\n";

  if (assert_condition)
    *scope.templ_out << "  }\n";
}

void Attribute::gen_encoder(DataSet & scope, int c_index)
{
  // KLUDGE
  if (tag.group.x) return;

  string coder_class;		// return type of decoder method
  int assert_condition;		// assert a condition?
  string dcd_mode;		// decode mode

  if (scope.parser->platform==Parser::gxx) {
    // *** NOT IMPLEMENTED
    //coder_class = a_class + "Coder<TS>";
    // KLUDGE
    // these coder classes declared elsewhere
    if (is_data_set)		// SQ <--> Attribute contains data set
      coder_class = a_class + "::Coder<TS>";
    else
      coder_class = a_class + "::Coder<TS>";
  }
  else if (scope.parser->platform==Parser::vc5) {
    // these coder classes declared elsewhere
    if (is_data_set)		// SQ <--> Attribute contains data set
      coder_class = a_class + "::Coder<TS>";
    else
      coder_class = a_class + "::Coder<TS>";
  }

  string c_name = "c_" + scope.parser->itos(c_index);

  *scope.templ_out << "  " + coder_class + " " + c_name + ";\n";

  string str;

  switch (type) {
  case t1: {
    assert_condition = false;
    str = c_name + ".encode" +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name + ");\n";
  }
    break;
  case t1c: {
    assert_condition = true;
    str = c_name + ".encode" +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name + ");\n";
  }
    break;
  case t2: {
    assert_condition = false;
    str = "if (obj.avail[0x" + scope.parser->itos(attr_num) + "]) " +
      c_name + ".encode" +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name + ");\n" +
      "  else "  + c_name + ".encode_empty" +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name +");\n";
  }
    break;
  case t2c: {
    assert_condition = true;
    str = "if (obj.avail[0x" + scope.parser->itos(attr_num) + "]) " +
      c_name + ".encode" +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name +");\n" +
      "  else "  + c_name + ".encode_empty" +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name + ");\n";
  }
    break;
  case t3: {
    assert_condition = false;
    str = "if (obj.avail[0x" + scope.parser->itos(attr_num) + "]) " +
      c_name + ".encode" +
      "(ds, obj." + a_name + ", obj."+ meta_attr_name + ");\n";
  }
    break;
  }
  
  if (assert_condition)
    *scope.templ_out << "  if (0) {\n";

  *scope.templ_out << "  " << str;

  if (assert_condition)
    *scope.templ_out << "  }\n";


}
