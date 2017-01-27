//
// Interface file for DICOM Service Object Pair Classes
//
//
//
// exa
//
//

#ifndef DSOPClasses_Interface
#define DSOPClasses_Interface 1

#include "General.hxx"
#include "SOP.hxx"

#include <CRImageIOD.hxx>
#include <CTImageIOD.hxx>
#include <SCImageIOD.hxx>
#include <MRImageIOD.hxx>
#include <XRayAngiographicImageIOD.hxx>

#include <BasicDirectoryIOD.hxx>

#include <BasicFilmSessionIOD.hxx>
#include <BasicFilmBoxIOD.hxx>
#include <BasicImageBoxIOD.hxx>
#include <PatientRootQRMod.hxx>
#include <StudyRootQRMod.hxx>
#include <PatientStudyOnlyQRMod.hxx>

#include <PatientIOD.hxx>
#include <StudyIOD.hxx>
#include <StudyComponentIOD.hxx>
#include <ResultsIOD.hxx>

// Decorator for an IOD which makes it codable.

template <class IOD>
class Codable_IOD : public IOD, public SOP {
public:

  Codable_IOD(bool proto) : SOP(proto) {}

  bool check_ts(UI& ts_uid) {
    return sop_tss.check_class(ts_uid);
  }

  const list<UI> & list_ts() {  // VC bug
    //list<UI>& da_list = sop_tss.transfer_syntaxes;
    return sop_tss.list_ts();
  }

  void decode(DStream &d, UI ts_uid) throw( DException ) {
    // treat our DICOM address in a cool way
    //DPtr self = ptr();
    sop_tss.decode(d, *this, ts_uid);
  }

  void encode(DStream &d, UI ts_uid) throw ( DException ) {
    sop_tss.encode(d, *this, ts_uid);
  }
	
  void set(SOP& sop) {
    IOD::set( dynamic_cast<IOD&>(sop) );
  }

  string toString() { return IOD::toString(); }

  friend class SOPs;
protected:
  static SOP_TSs<IOD> sop_tss;
};

template <class IOD>
SOP_TSs<IOD>
  Codable_IOD<IOD>::sop_tss;

// Base Abstraction for a Service Object Pair Class
// Union of an Information Object Definition
// and a Service

template <class IOD, int ServiceNumber = 0>
class BaseSOPClass : public Codable_IOD<IOD>
{
public:
  typedef IOD IODClass;
  typedef Codable_IOD<IOD> Base;
  typedef BaseSOPClass<IODClass, ServiceNumber> Self;

  BaseSOPClass() : Base(false)
  {
    if ( !dicom_app.storage_manager.instance_in_memory(this) ) {
      // if instance is not in storage system this is a transient object
      modSOPInstanceUID(dicom_app.storage_manager.gen_instance_uid());
      dicom_app.storage_manager.make_transient_instance(*this);
    }
    else {
      dicom_app.storage_manager.make_persistent_instance(*this);
    }
  }

  BaseSOPClass(bool _prototype)
    : Base(_prototype) {
    //if (prototype)  // we are a prototype then
    //  ; // CODE: what kind of special initialization does a prototype need?
  }

  ~BaseSOPClass()
  {
    dicom_app.storage_manager.remove_instance(*this);
  }

  virtual SOP & gen() {
//#pragma message("gen()")
    return * new Self();
  }

  void* operator new(size_t size) {
    void* sop = ::operator new(size);
    // vtable not yet in!
    dicom_app.storage_manager.pre_make_persistent_instance
      (sop, dicom_app.storage_manager.gen_instance_uid());
    return sop;
  }

//  void operator delete(void *mem) {}

  SOP & gen(bool persistent) {
//#pragma message("gen(bool)")
    return * new(persistent) Self();
  }

  void* operator new(size_t size, bool persistent) {
    if (!persistent) {
      void* sop = ::operator new(size);
      return sop;
    }
    return ::operator new(size);
  }

//  void operator delete(void *address, bool persistent) {}

  virtual SOP & gen(const UI & instance_id) {
//#pragma message("gen(const UI&)")
   return * new(instance_id) Self();
  }

  void* operator new(size_t size, const UI & instance_id ) {
//#pragma message("placement new(const UI&) start")
    void* sop = ::operator new(size);
    dicom_app.storage_manager.pre_make_persistent_instance(sop, instance_id);
    return sop;
//#pragma message("placement new(const UI&) end")
  }

//  void operator delete(void *address, const UI & instance_id ) {}

  // CODE: write the delete operator (so that it makes some sense ;)
//  void operator delete(void *address) {
//   ::operator delete(address);
//  }

  const UI & sel_class_id() {
    return UID;
  }

  const UI sel_instance_id() {
    return selSOPInstanceUID();
  }

  void mod_instance_id(const UI& instance_id) {
    modSOPInstanceUID(instance_id);
  }

  static const UI UID;
};

template <class IOD, int ServiceNumber = 0>
class GenericSOPClass : public BaseSOPClass<IOD, ServiceNumber>
{
public:
  typedef IOD IODClass;
  typedef BaseSOPClass<IODClass, ServiceNumber> Base;
  typedef GenericSOPClass<IODClass, ServiceNumber> Self;

  GenericSOPClass() {}

  GenericSOPClass<IODClass, ServiceNumber>(bool _prototype)
    : Base(_prototype) {}

  SOP & gen() {
    return * new Self();
  }

  SOP & gen(const UI & instance_id) {
    return * new(instance_id) Self();
  }

  static Self Representative;
};

template <class IOD, int ServiceNumber = 0>
class CompositeSOPClass : public BaseSOPClass<IOD, ServiceNumber>
{
public:
  typedef IOD IODClass;
  typedef BaseSOPClass<IODClass, ServiceNumber> Base;
  typedef CompositeSOPClass<IODClass, ServiceNumber> Self;

  CompositeSOPClass() : Base()
  {
    //IOD& iod = dynamic_cast<IOD>(*this);
    AbstractSOPCommonMod* sop_common = dynamic_cast<AbstractSOPCommonMod*>(this);
    sop_common->modSOPClassUID(sel_class_id());
  }

  CompositeSOPClass(bool _prototype) : Base(_prototype) {}

  // annihilate
  ~CompositeSOPClass() {
    ;// yeah?
  }

  SOP & gen() {
    return * new Self();
  }

  SOP & gen(const UI & instance_id) {
    return * new(instance_id) Self();
  }

  static Self Representative;
};

// the whole Null_IOD thing is a huge KLUDGE
class Null_IOD
{
public:
  class AbstractCoder {
  public:
    virtual void decode(DStream&,Null_IOD&) = 0;
    virtual void encode(DStream&,Null_IOD&) = 0;
  }; 

  void set(Null_IOD& a);
  void modSOPInstanceUID(const UI&) {}
  const UI selSOPInstanceUID() { return *new UI; }
  string toString() { return string("<Null_IOD>");}
  template<class TS> class Coder : public AbstractCoder {
  public:
    Coder() {}
    void decode(DStream&,Null_IOD&);
    void encode(DStream&,Null_IOD&);
  }; 
};

template <class IOD, int ServiceNumber = 0>
class InfoModelSOPClass : public Codable_IOD<IOD>
{
public:
  typedef IOD IODClass;
  typedef Codable_IOD<IOD> Base;
  typedef InfoModelSOPClass<IODClass, ServiceNumber> Self;

  InfoModelSOPClass() : Base(false)
  {
    //SOPCommonMod& sop_common = static_cast<SOPCommonMod&>(*this);
    //sop_common.modSOPClassUID(sel_class_id());
    if ( !dicom_app.storage_manager.instance_in_memory(this) ) {
      // if instance is not in storage system this is a transient object
      //modSOPInstanceUID(dicom_app.storage_manager.gen_instance_uid());
      dicom_app.storage_manager.make_transient_instance(*this);
    }
    else {
      dicom_app.storage_manager.make_persistent_instance(*this);
    }
  }

  InfoModelSOPClass(bool _prototype) : Base(_prototype) {
    //if (prototype);  // we are a prototype then
  }

  ~InfoModelSOPClass()
  {
    dicom_app.storage_manager.remove_instance(*this);
  }

  SOP & gen() {
    return * new Self();
  }

  void* operator new(size_t size) {
    void* sop = ::operator new(size);
    // vtable not yet in!
    dicom_app.storage_manager.pre_make_persistent_instance
      (sop, dicom_app.storage_manager.gen_instance_uid());
    return sop;
  }

//  void operator delete(void *mem) {}

  SOP & gen(bool persistent) {
    return * new(persistent) Self();
  }

  SOP & gen(const UI & instance_id) {
    return * new(instance_id) Self();
    //return * new Self();
  }

  void* operator new(size_t size, bool persistent) {
    if (!persistent) {
      void* sop = ::operator new(size);
      return sop;
    }
    return ::operator new(size);
  }

  void* operator new(size_t size, const UI & instance_id ) {
    void* sop = ::operator new(size);
    dicom_app.storage_manager.pre_make_persistent_instance(sop, instance_id);
    return sop;
  }


 // void operator delete(void *address, bool persistent) {}

//  void operator delete(void *address, const UI & instance_id ) {}

  const UI & sel_class_id() {
    return UID;
  }

  const UI sel_instance_id() {
    return InstanceUID;
  }

  void mod_instance_id(const UI& instance_id) {
    InstanceUID = instance_id;
  }

  UI InstanceUID;

  static const UI UID;
  static Self Representative;

};

typedef GenericSOPClass<Null_IOD> VerificationSOPClass;

typedef CompositeSOPClass<CRImageIOD> CRImageStorage;
typedef CompositeSOPClass<CTImageIOD> CTImageStorage;
typedef CompositeSOPClass<SCImageIOD> SecondaryCaptureImageStorage;
typedef CompositeSOPClass<MRImageIOD> MRImageStorage;
typedef CompositeSOPClass<XRayAngiographicImageIOD> XRayAngiographicImageStorage;


typedef CompositeSOPClass<BasicDirectoryIOD> MediaStorageDirectoryStorage;

typedef CompositeSOPClass<BasicFilmSessionIOD> BasicFilmSessionSOPClass;
typedef CompositeSOPClass<BasicFilmBoxIOD> BasicFilmBoxSOPClass;
typedef CompositeSOPClass<BasicImageBoxIOD> BasicGrayscaleImageBoxSOPClass;
typedef CompositeSOPClass<BasicImageBoxIOD,1> BasicColorImageBoxSOPClass;


typedef InfoModelSOPClass<PatientRootQRMod,0> PatientRootQRInfoModelFIND;
typedef InfoModelSOPClass<PatientRootQRMod,1> PatientRootQRInfoModelGET;
typedef InfoModelSOPClass<PatientRootQRMod,2> PatientRootQRInfoModelMOVE;

typedef CompositeSOPClass<PatientIOD> PatientManagement;
typedef CompositeSOPClass<StudyIOD> StudyManagement;
typedef CompositeSOPClass<StudyComponentIOD> StudyComponentManagement;
typedef CompositeSOPClass<ResultsIOD> ResultsManagement;

#endif
