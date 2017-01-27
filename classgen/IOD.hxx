//
//
// C++ Interface for module: IOD
//
// Description: 
//
//
// Author: exa
//
//

#ifndef IOD_Interface
#define IOD_Interface

#include "General.hxx"

#include "Module.hxx"

// DICOM IOD
class IOD : public DataSet
{
public:
  struct ModuleInfo {
    Module::ReqType req_type;
    int Mutex;			// which mutex
    int index;			// number of module
  };
  typedef map<string, Module* > modmap;
  typedef map<string, ModuleInfo > modinfomap;

  IOD() {}
  IOD(string a, int d) : DataSet(a,d), number_of_modules(0), num_attr(0) {}	// an IOD

  modmap modules;
  modinfomap modinfo;
  int number_of_modules;
  int num_attr;
  
  void add_module(Module&, Module::ReqType, int);
  virtual void begin_gen(Parser*); // begin code generation
  virtual void gen_class();      // gen corresponding class
  void gen_includes();
  void gen_bases(bool);
  virtual void gen_imp_body();
  virtual void gen_constructor();
  virtual void gen_coder();	// gen coder class
  virtual void end_gen(); // end code generation
};

#endif
