#ifndef GET_OPT_H
#define GET_OPT_H

#include "General.hxx"

// Describes a command line option

class Option {
 public:

  Option(const string & _name, bool _has_arg, int *_flag, int
  default_val)
    : name(_name), has_arg(_has_arg), flag(_flag), val(default_val) {}

  string name;
  bool has_arg;
  int *flag;
  int val;
};


class Option_Parser()
{
 public:
  Option_Parser(const vector<Option> & opt_vector);
  
  class Iterator {
    Iterator(Option_Parser & _parser);
    const Option & read();
    bool end() const;
    void next();
  private:
    Option_Parser & parser;
  };

  

 private:
  const vector<Option> & opts;
  map<string, Option*> long_opt;
  map<char, Option*> short_opt;
};

#endif
