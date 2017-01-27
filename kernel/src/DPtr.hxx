/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef Kernel_DPtr_Interface
#define Kernel_DPtr_Interface 1

#include "General.hxx"

class SOP;

class DPtr
 {
  public:

    DPtr() {}
    
    DPtr(const UI& b) : instance_id(b) {}
    DPtr(const UI& a, const UI& b) : class_id(a), instance_id(b) {}
    UI class_id;
    UI instance_id;
    SOP & operator *() const;
    SOP & operator ->() const{ return operator*(); }
    bool exists() const;
    static DPtr Null;
 };

#endif
