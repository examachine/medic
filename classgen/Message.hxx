//
//
// C++ Interface for module: Message
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Message_Interface
#define Message_Interface

#include "General.hxx"

#include "DataSet.hxx"

// DICOM message
class Message : public DataSet
{
public:
  Message() {}
  Message(string a, int d) : DataSet(a,d) {}
  virtual void begin_gen(Parser*);  // begin code generation
  //virtual void gen_class();  // gen corresponding class
  //virtual void gen_coder();	// gen coder class
  virtual void end_gen();    // end code generation
};

#endif
