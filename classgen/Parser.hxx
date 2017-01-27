/*
** Interface file for Parser module
**
**
**
** exa
**
*/

#ifndef Parser_h
#define Parser_h 1

#include "General.hxx"
#include "Tag.hxx"
#include "Attribute.hxx"
#include "DataSets.hxx"
#include "dicom.hxx"

class Parser
{
public:
  Parser::Parser(char *);

  enum platform_type {gxx, vc5, vc6};

  // lexical parameters
  string source_filename, interface_filename, implementation_filename;
  ofstream *outh;
  ofstream *outc;
  int is_logged;
  ofstream *log;
  int line_number;
  int total_number_of_lines;
  int no_punct;
  int strip_punct;
  int expect_id;
  int short_id;
  bool parsing_secondary;
  platform_type platform;
  string dir_prefix;

  void parse(const string &);

  static string* strip_chars(string);
  static string itos(int);

  int warnings;
  void warn(string warning);

  int errors;
  void error(string warning);


  // UID dictionary
  class uidmap : public map<string, string, less<string> > {
  public:
    void list_uid() {
      iterator start=begin(), stop=end();
      for (;start != stop; start++)
	cout << (*start).first << endl;
    }
  };
  uidmap sop_uid, metasop_uid, ts_uid;
  int number_of_uids;
  void add_uid(string *uid, string *desc, string *type);

  // Tag dictionary
  typedef map<int, map<int, TagDef, less<int> > , less<int> > tagmap;
  tagmap tag_td, xtag_td;
  int number_of_tags;
  Tag current_tag;
  TagDef current_td;
  void add_tg(int a, int b) { current_tag.group = TagGroup(a,b); }
  void add_te(int a, int b) { current_tag.element = TagElement(a,b); }
  void add_tid(string &id) { current_td.name = id ; }
  void add_tvr(const string &vr) { current_td.vr = vr ; }
  void add_tvm(VM vm) { current_td.vm = vm ; }
  void add_tagdef();
  TagDef get_tagdef(Tag);

  // Modules
  int nest_depth;		// nesting depth of current data set
  int prev_depth;
  int number_of_modules;
  int sq_cnt;
  Attribute::ReqType current_type;
  Module* module;
  typedef map<string, Module*> modmap;
  modmap modules;
  // better keep a list of modules
  list<DataSet*> stack;		// recursion stack
  void init_gen();
  void begin_module(string*);
  void set_ctype(string t);
  void add_attr();
  void gen_module();

  // IODs
  int current_mutex;		// which mutually exclusive part
  int number_of_iods;		// under consideration
  IOD* iod;
  typedef map<string, IOD*> iodmap;
  iodmap iods;
  void begin_iod(string *module_name);
  void add_module(string *module_name, string *req);
  void gen_iod();

  // Messages
  int number_of_msgs;
  Message* msg;
  typedef map<string, Message*> msgmap;
  msgmap msgs;
  void begin_message(string *msg_name);
  void gen_message();

  string scope;

  // Generation
  void generate();		// do generate classes

private:
  void find_shared_datasets();
};


#endif
