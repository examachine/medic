//
//
// C++ Interface for module: Module
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Module_Interface
#define Module_Interface

#include "General.hxx"
#include "DataSet.hxx"

// DICOM module
class Module : public DataSet
{
public:
  enum ReqType {m,c,u};
  Module() {}
  Module(string a, int d) : DataSet(a,d) {}	// a module
  virtual void begin_gen(Parser*); // begin code generation
  //   virtual void gen_abstract_class(Parser&); // gen corresponding abstract class
  virtual void gen_class();      // gen corresponding class
  virtual void gen_coder();	// gen coder class
  virtual void end_gen(); // end code generation
};


#endif
