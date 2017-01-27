
#include "Get_Opt.h"

Option_Parser(int argc, char * const argv[], const vector<Option> & opt_vector)
  : opts(opt_vector)
{
  
  // initialize option maps
  vector<Option>::iterator opt = opts.begin(), opt_end opts.end();
  for (; opt!=opt_end; i++) {
    long_opt[opt->name] = &(*opt);
  }
}

Option_Parser::Iterator(Option_Parser & _parser)
  : parser(_parser)
{
}

const Option & Option_Parser::Iterator::read()
{
}

bool Option_Parser::Iterator::end() const
{
}

Option_Parser::Iterator::next()
{
}

