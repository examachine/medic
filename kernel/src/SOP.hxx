/*
** Interface file for DICOM Service Object Pair Classes
**
**
**
** exa
**
*/

#ifndef DSOP_Interface
#define DSOP_Interface 1

#include "General.hxx"
#include "VR.hxx"

#include "TransferSyntaxes.hxx"
#include "DPtr.hxx"


// An abstract class representing SOP interfaces

class SOP
{
public:
  SOP(bool pt) : prototype(pt) {}
  virtual SOP & gen() = 0;
  virtual SOP & gen(const UI&) = 0;
  virtual SOP & gen(bool persistent) = 0;
  DPtr ptr() {
    return DPtr(sel_class_id(), sel_instance_id());
  }
  virtual const UI & sel_class_id() = 0;
  virtual const UI sel_instance_id() = 0;
  virtual void mod_instance_id(const UI &) = 0;
  virtual bool check_ts(UI& ts_uid) = 0;
  virtual const list<UI> & list_ts() = 0;
  virtual void decode(DStream &d, UI ts_uid) throw (DException) = 0;
  virtual void encode(DStream &d, UI ts_uid) throw (DException) = 0;
  virtual void set(SOP& sop) = 0;
  virtual string toString() = 0;
  bool prototype;
private:
};


class SOPs : public map< UI, SOP* >
{
public:
  void init_class();
  bool check_class(UI id) {
    return ( find(id) != end() );
  }
};


#endif
