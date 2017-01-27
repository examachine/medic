/*
** Implementation file for Parser module
**
**
**
** exa
**
*/

#include "Parser.hxx"

Parser* hack_parser;

// huge constructor
Parser::Parser(char* dir)
  : nest_depth(0), line_number(1), no_punct(0), is_logged(1),
    log(new ofstream("log.txt")), strip_punct(0), expect_id(0),
    short_id(0), number_of_uids(0), number_of_tags(0),
    dir_prefix(/*  cannot create dirs? :( */), prev_depth(0),
    number_of_modules(0), sq_cnt(0), total_number_of_lines(0),
    parsing_secondary(false) {
  hack_parser = this;
  warnings = 0;
  //cout << hex << showbase;
  //cerr << hex << showbase;
}

void Parser::parse(const string & filename) {
  source_filename = filename;
  if (yyin = fopen(filename.c_str(), "r")) {
    line_number = 1;
    yyparse();
  }
  else {
    cerr << filename << " cannot be opened" << endl;
    exit(0);
  }
}

string* Parser::strip_chars(string tmp) {
  string sep = " -/'()&[],:";
  int n = tmp.length();
  string *id = new string;
  int start = tmp.find_first_not_of(sep), stop;
  while ((start >=0) && (start <n)) {
    stop = tmp.find_first_of(sep, start);
    if ((stop <0) || (stop >n)) stop = n;
    *id += tmp.substr(start,stop-start);
    start = tmp.find_first_not_of(sep,stop+1); 
  }
  return id;
}

// convert integer to hexadecimal string
string Parser::itos(int n) {
  string s;
  for (int i=12; i>=0; i -= 4 ) {
    char digit =  (n >> i) & 0xf;
    if (digit <=9)
      digit += '0';
    else
      digit += 'A' - 10;
    s += digit;
    // fix dicom.flex then!
  }
  //for (int k= 4096; k>=1; k >>= 4) 
  //  s.append(1, (char) ( '0'+ ((n / k) % 16) ) );
  return s;
}
void Parser::warn(string warning) {
  warnings++;
  cerr << "warning: " << source_filename << ':' << line_number << ": "
       << warning << endl;
  if (is_logged)
    *log << "* warning: " << source_filename << ':' << line_number
	 << ": " << warning << endl;
}

void Parser::error(string warning) {
  errors++;
  cerr << "error: " << source_filename << ':' << line_number << ": " << warning << endl;
  if (is_logged)
    *log << "* error: " << source_filename << ':' << line_number << ": " << warning << endl;
}

void Parser::add_uid(string *uid, string *desc, string *type)
{
  if (*type == "SOP Class")
    sop_uid[*desc] = *uid;
  else if (*type == "META SOP Class")
    metasop_uid[*desc] = *uid;
  else if (*type == "Transfer Syntax") {
    ts_uid[*desc] = *uid;
    string* str = strip_chars(*desc);
    cout << "Transfer Syntax: " << *str << endl;
  }
  number_of_uids++;
}

void Parser::add_tagdef()
{
  // put current tag dictionary entry in data structures
  if (!current_tag.group.x) {
    for (int i=current_tag.element.number; i<=current_tag.element.number2; i++)
      tag_td[current_tag.group.number][i] = current_td;
  }
  else {
    for (int i=current_tag.element.number; i<=current_tag.element.number2; i++)
      xtag_td[current_tag.group.number][i] = current_td;
  }
  number_of_tags++;
}

TagDef Parser::get_tagdef(Tag tag)
{
  if (tag.element.number != tag.element.number2)
    error("cannot figure out a variable tag's description");
  else
    if (!tag.group.x) {
      if (tag_td.find(tag.group.number)!=tag_td.end())
	if (tag_td[tag.group.number].find(tag.element.number) != 
	    tag_td[tag.group.number].end())
	  return tag_td[tag.group.number][tag.element.number];
    }
    else {
      if (xtag_td.find(tag.group.number)!=xtag_td.end())
	if (xtag_td[tag.group.number].find(tag.element.number) != 
	    xtag_td[tag.group.number].end())
	  return xtag_td[tag.group.number][tag.element.number];
    }

  if (tag.group.x) {
    string tmp = itos(tag.group.number); 
    error(string("Tag (") + tmp[2] + tmp[3] + "xx,"
	  + itos(tag.element.number) + ") not found");
  }
  else
    error("Tag (" + itos(tag.group.number) + ','
	  + itos(tag.element.number) + ") not found");

  return TagDef();
}


// optimize for sequences of obj. ref
void Parser::init_gen() {
  //CODE: the common sequence datasets!
//   begin_module(new string("sqRef"));
}

void Parser::begin_module(string *s)
{
  string id = (*s) + "Mod"; delete s;
  nest_depth = 0;
  module = new Module(id, 0);
  module->scope = id;
  stack.push_back(module);
  modules[id]=module;
}

void Parser::set_ctype(string t)
{
  if (t=="1") current_type = Attribute::t1;
  else
    if (t=="1c") current_type = Attribute::t1c;
    else
      if (t=="2") current_type = Attribute::t2;
      else
	if (t=="2c") current_type = Attribute::t2c;
	else
	  if (t=="3") current_type = Attribute::t3;
	  else
	    if (t=="4") current_type = Attribute::t4;

  // ******* COERCION *********** KLUDGE
  if ( (current_type == Attribute::t1c) || (current_type == Attribute::t2c) )
    current_type = Attribute::t3;
  if (current_type == Attribute::t4)
    current_type = Attribute::t3;
}

void Parser::add_attr()
{
  current_td = get_tagdef(current_tag);

  // is nested data set over?
  if (nest_depth < prev_depth) {
    stack.pop_back();
  }

  DataSet *dataset = stack.back();
  
  if ( current_td.vr == "SQ" ) {
    // create a nested data set
    // an attribute which refers to a sequence of a data set
    string str = "Seq_" + itos(sq_cnt++);
    Attribute a(current_tag, current_td,
		str, current_type, nest_depth );
    a.attr_num = dataset->attr_num;
    a.a_name = "a_" + itos(a.attr_num);
    a.meta_attr_name = a.a_name + "_attr";
    a.is_seq = true;
    a.is_ptr = false;
    if (platform == gxx)
      a.data_set->scope = dataset->scope + "::" + str;
    else if (platform==vc5)
      a.data_set->scope = str;
    dataset->add(a);
    // to fill in the data set, we expect attributes
    stack.push_back(a.data_set);
  }
  else if ( current_td.vr == "UI" &&
	    ( (current_td.name.find("SOPClassUID") != string::npos) ||
	      ( (current_td.name.find("SOPInstanceUID") != string::npos) && !parsing_secondary) )
	    ) {
    Attribute a(current_tag, current_td, current_type, nest_depth );
    a.attr_num = dataset->attr_num;
    string ptr_member;
    int ptr_number = a.attr_num;
    string ptr_name = current_td.name;
    int wpos = ptr_name.find("SOPClassUID");
    if (wpos == string::npos)
      wpos = ptr_name.find("SOPInstanceUID");
    ptr_name.erase(wpos);
    if ( ! dataset->has_class_ui(ptr_name) ) {
      ptr_member = "class_id";
      dataset->add_class_ui(ptr_name);
      ptr_name += "SOPPointer";
      dataset->add(Pointer(ptr_number, ptr_name, nest_depth, current_tag));
      Pointer & pointer = dataset->pointers.back();
      pointer.class_num = a.attr_num;
    }
    else {
      Pointer& pointer = dataset->pointers.back();
      pointer.instance_num = a.attr_num;
      ptr_number = pointer.p_number;
      ptr_member = "instance_id";
    }
    a.a_name = "p_" + itos(ptr_number) + "." + ptr_member;
    a.meta_attr_name = "p_" + itos(ptr_number) + ptr_member + "_attr";
    a.is_seq = false;
    a.is_ptr = true;
    dataset->add(a);
  } else {
    Attribute a(current_tag, current_td, current_type, nest_depth );
    a.attr_num = dataset->attr_num;
    a.a_name = "a_" + itos(a.attr_num);
    a.meta_attr_name = a.a_name + "_attr";
    a.is_seq = ((current_td.vr == "OB") || (current_td.vr=="OW"));
    a.is_ptr = false;
    dataset->add(a);
  }
  dataset->attr_num++;
}

char *make_str(string& s) {
  char *buffer = new char[s.size()+1];
  int i; for (i=0; i<s.size(); i++)
    buffer[i] = s[i];
  buffer[i] = 0;
  return buffer;
}

ofstream* open_of(const string& s) {
  ofstream* output_file = new ofstream(s.c_str());
  return output_file;
}

void Parser::gen_module() {
  if (platform==gxx) {
    interface_filename = module->name + ".hxx";
    implementation_filename = module->name + ".cxx";
    outh = new ofstream(interface_filename.c_str());
    outc = new ofstream(implementation_filename.c_str());
    module->begin_gen(this);
    module->gen_class();
    module->end_gen();
  }
  else if (platform==vc5) {
    interface_filename = module->name + ".h";
    implementation_filename = module->name + ".cpp";
    outh = new ofstream(interface_filename.c_str());
    outc = new ofstream(implementation_filename.c_str());
    module->begin_gen(this);
    module->gen_class();
    module->end_gen();
  }
  number_of_modules++;
  cout << '.'; // let's see progress
}

void Parser::begin_iod(string *s) {
  string id = (*s) + "IOD"; delete s;
  current_mutex;
  iod = new IOD(id, 0);
  iod->scope = id;
  iods[id]=iod;
  //warn("Processing " + id + " IOD");
}

void Parser::add_module(string *s, string *req) {
  Module::ReqType req_type;
  if (*req=="m") 
    req_type=Module::m;
  else if (*req=="c")
    req_type=Module::c;
  else if (*req=="u")
    req_type=Module::u;
  else
    warn("Requirement type invalid");
  delete req;
  string mod_id=*s + "Mod" ; delete s;

  if (modules.find(mod_id) == modules.end())
    error("No such module as " + mod_id + " found");
  else {
    iod->add_module(*modules[mod_id], req_type, current_mutex);
  }
}

void Parser::gen_iod() {
  if (platform==gxx) {
    interface_filename = iod->name + ".hxx";
    implementation_filename = iod->name + ".cxx";
    outh = new ofstream(interface_filename.c_str());
    outc = new ofstream(implementation_filename.c_str());
    iod->begin_gen(this);
    iod->gen_class();
    iod->end_gen();
  }
  else if (platform==vc5) {
    interface_filename = iod->name + ".h";
    implementation_filename = iod->name + ".cpp";
    outh = new ofstream(interface_filename.c_str());
    outc = new ofstream(implementation_filename.c_str());
    iod->begin_gen(this);
    iod->gen_class();
    iod->end_gen();
  }
  number_of_iods++;
}

void Parser::begin_message(string *s) {
  string id = (*s) + "Msg"; delete s;
  nest_depth = 0;
  msg = new Message(id, 0);
  msg->scope = id;
  stack.push_back(msg);
  msgs[id]=msg;
}

void Parser::gen_message() {
  if (platform==gxx) {
    interface_filename = msg->name + ".hxx";
    implementation_filename = msg->name + ".cxx";
    outh = new ofstream(interface_filename.c_str());
    outc = new ofstream(implementation_filename.c_str());
    msg->begin_gen(this);
    msg->gen_class();
    msg->end_gen();
  }
  else if (platform==vc5) {
    interface_filename = msg->name + ".h";
    implementation_filename = msg->name + ".cpp";
    outh = open_of(interface_filename);
    outc = open_of(implementation_filename);
    msg->begin_gen(this);
    msg->gen_class();
    msg->end_gen();
  }
  number_of_msgs++;
}

void Parser::generate()
{

  find_shared_datasets();

  // Generate modules
  cout << "Generating modules" << endl;
  modmap::iterator mod_i=modules.begin(), mod_i_end=modules.end();
  for (; mod_i != mod_i_end; mod_i++) {
    module = mod_i->second;
    gen_module();
    cout << '.'; // progress
  }
  cout << "[ " << modules.size() << " modules generated ]" << endl;

  // Generate IODs
  cout << "Generating IODs" << endl;
  iodmap::iterator iod_i=iods.begin(), iod_i_end=iods.end();
  for (; iod_i != iod_i_end; iod_i++) {
    iod = iod_i->second;
    gen_iod();
    cout << '.'; // progress
  }
  cout << "[ " << iods.size() << " IODs generated ]" << endl;

  // Generate Messages
  cout << "Generating Messages" << endl;
  msgmap::iterator msg_i=msgs.begin(), msg_i_end=msgs.end();
  for (; msg_i != msg_i_end; msg_i++) {
    msg = msg_i->second;
    gen_message();
    cout << '.'; // progress
  }
  cout << "[ " << msgs.size() << " Messages generated ]" << endl;

  // generate library initialization point(s)
//   ofstream base_cxx("Dicom_Base.cxx");
// //   for (mod_i=modules.begin(); mod_i != mod_i_end; mod_i++)
// //     base_cxx << "#include \"" << mod_i->second->implementation_filename  << "\"" <<endl; 
//   for (iod_i=iods.begin(); iod_i != iod_i_end; iod_i++)
//     base_cxx << "#include \"" << iod_i->second->implementation_filename  << "\"" <<endl; 
//   for (msg_i=msgs.begin(); msg_i != msg_i_end; msg_i++)
//     base_cxx << "#include \"" << msg_i->second->implementation_filename  << "\"" <<endl; 
}

void Parser::find_shared_datasets()
{
  // iterate over all attributes in IODs

  iodmap::iterator iod_i=iods.begin(), iod_i_end=iods.end();
  for (; iod_i != iod_i_end; iod_i++) {
    IOD *iod = iod_i->second;
    cout << "IOD: " << iod->name << endl; 
    attrmap::iterator start=iod->attributes.begin(),
      stop=iod->attributes.end();
    for (;start != stop; start++) {
      Attribute &attr = start->second;
#ifndef _MSC_VER
      cout << "attribute: " << attr.tagdef.name
	   << " dataset? " << attr.is_data_set
	   << " modules " << attr.modules << endl;
#endif
      if (attr.is_data_set && attr.modules.size()>1) {
	cout << "shared dataset: " << attr.tagdef.name << endl;
      }
    }
  }

}



