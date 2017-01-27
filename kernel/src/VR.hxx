/*
** Interface file for VR module
**
** Value Representation
**
** exa
**
*/

#ifndef VR_Interface
#define VR_Interface 1


#include "General.hxx"
#include "Tag.hxx"
#include "DStream.hxx"
#include "DException.hxx"
#include "TransferSyntax.hxx"
#include "Time.hxx"

// Base Value Representation class
// a VR class holds internal representation for a specific DICOM VR
// * operator is used to retrieve semantic content.
// rep function is used to retrieve internal representation
// VM of a VR is always static, thus a VR, VM pair makes a distinct class

class VR {
public:

  bool zero_length;

  VR() : zero_length(false) {};
  //virtual const char* selName() const = 0;
  //virtual string toString() const = 0;

  // diagnostics
  void dgn(string s);
  // zero length extract
  void check_zero_length(int len) { zero_length = (len==0); }

  // Base coder class
  class Coder {
  public:
    void dgn(string s);
  };
};


class AtomicVR: public VR {
public:
  AtomicVR() {};
};

// forward declaration
class rangeDA;
class rangeTM;

// Character String VRs
// backslash is seperator for VM > 1
// may have virtual methods
class StringVR : public AtomicVR {
public:
  // constructors
  StringVR() {}
  StringVR(char* s) : value(s) {}
  StringVR(const string & s) : value(s) {}
	
  // operators
  const string & operator*() const { return value; }
	string & rep() { return value; }
	const string * operator -> () const { return &value; }
  StringVR& operator=(const char *s) {
		value = s;
    return *this;
  }
  StringVR& operator=(const char c) {
		value = c;
    return *this;
  }
	
  // default toString
  string toString() const { return value; }
	
  // coder class
public:
	
protected:
  string value;
  
  // friends
  friend bool operator<(const StringVR, const StringVR);
  friend bool operator==(const StringVR, const StringVR);
  friend class rangeDA;
  friend class rangeTM;
};

inline bool operator <(const StringVR lhs, const StringVR rhs) { return lhs.value < rhs.value; }
inline bool operator ==(const StringVR lhs, const StringVR rhs) { return lhs.value == rhs.value; }


// Ignorer Classes

class IgnoreNone {
public:
  void operator()(string &s) {
  }
};

class IgnoreLTSpaces {
public:
  void operator()(string &s) {
    int pos = s.find_first_not_of(' ');
    if (pos>0 && pos!=string::npos) s.erase(0,pos);
    pos = s.find_last_not_of(' ');
    if (pos!=string::npos) s.erase(pos+1);
  }
};

class IgnoreTSpaces {
public:
  void operator()(string &s) {
    int pos = s.find_last_not_of(' ');
    if (pos!=string::npos) s.erase(pos+1);
  }
};

class IgnoreTNull {
public:
  void operator()(string &s) {
    int last;
    if ( ! (last = s.size()) ) return; // bug fix!
    last -= 1;
    if (s[last]=='\0') s.erase(last); // VC bug with the preceding approach here I presume
  }
};

// Character Repertoire Classes

class CharRep {
public:
  enum {LF=0xa, FF=0xc, CR=0xd, ESC=0x1b};
};

class CharRepDef : public CharRep {
public:
  bool operator()(string &s) {
    return true;
  }
};

template<const char **MINUS>
class CharRepDefMinus : public CharRep {
public:
  bool operator()(string &s) {
    int pos = s.find_first_of(*MINUS);
    return (pos==string::npos);
  }
};

template <const char **PLUS>
class CharRepDigitPlus : public CharRep {
public:
  bool operator()(string &s) {
    string str = "0123456789";
    str.append(*PLUS);
    int pos = s.find_first_not_of( str );
    return (pos==string::npos);
  }
};

template <const char **PLUS>
class CharRepAlphaNumPlus : public CharRep
{
public:
  bool operator()(string &s) {
    for (int i=0; i<s.size(); i++) {
      char a = s[i];
      if ( ! ( (a>='0' && a<='9') || (a>='A' && a<='Z')
	       || (string(*PLUS).find(a)!=string::npos) ) )
	return false;
    }
    return true;
  }
};

template <unsigned int arity>
class FixedSize
{
public:
  int operator()() {
    return (arity);
  }
  string toString() const { return string("length:") + arity; }
};

template <unsigned int arity>
class FixedLenCheck
{
public:
  bool operator()(int s) {
    return (s==arity);
  }
};

template <unsigned int max> class UBSize
{
public:
  int operator()() {
    return (max);
  }
  string toString() const { return string("maximum length:") + max; }
};

template <unsigned int max> class UBLenCheck
{
public:
  bool operator()(int s) {
    return (s<=max);
  }
};

template <char p> class CharPadder
{
public:
  void operator()(string & s) {
    if (s.size() % 2 == 1)
      s.append(1, p);
  }
};

class ImplicitVRLittleEndian;	// not declared yet

// Base class for string VR's (generic)
template<class SizeFun, class CheckLenFun, class Ignorer,
	 class Chars = CharRepDef,class _Padder = CharPadder<' '> >
class GenericStringVR : public StringVR
{
public:
  typedef _Padder Padder;
  typedef GenericStringVR<SizeFun, CheckLenFun, Ignorer, Chars, Padder> Self;

  SizeFun get_length;
  CheckLenFun check_length_fun;
  bool check_length(int len) {
    check_zero_length(len);
    return check_length_fun(len);
  }
  Ignorer ignorer;
  Chars charRep;
  Padder padder;

  GenericStringVR() {}
  GenericStringVR(const char *s) : StringVR(s) {
    update_rep();
  }
  GenericStringVR(const string &s) : StringVR(s) {
    update_rep();
  }

  Self operator =(const char *s) {
    value = s;
    update_rep();
    return *this;
  }

  Self operator =(const string & s) {
    value = s;
    update_rep();
    return *this;
  }

  void update_rep() {
    if (!check_length(value.size()))
      throw DVREncodingException(string("length of string must be equal to ")
				 + get_length() + " bytes");
    // apply ignorer
    ignorer(value);
    // check character rep.
    if (!charRep(value))
      throw DVREncodingException(string("unexpected character repertoire"));
    // decode custom representation
    custom_rep(); // does not work in constructors of descendant classes
  }

  virtual void custom_rep() {} // a virtual function

  template<class TS = ImplicitVRLittleEndian>
  class Coder : public VR::Coder
  {
  public:
    void decode_mandatory(DStream& d, Self& a, const Attribute& attr_info){
      int del = TS::decode_req_data_elt_header(d, attr_info);
      //dgn(string("decode_mand:") + a.get_length.toString());
      if (a.check_length(del)) {
	TS::decode_string(d, a.rep(), del);
	a.update_rep();
      }
      else
	throw DVREncodingException();
    }

    bool decode_required(DStream& d, Self& a, const Attribute& attr_info){
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (a.check_length(del)) {
	TS::decode_string(d, a.rep(), del);
	a.update_rep();
	return true;
      }
      else if (del == 0) {				// no value field
	return false;
      }
      else
	throw DVREncodingException();
      return false;
    }
		
    bool decode_optional(DStream& d, Self& a, const Attribute& attr_info){
      int del = TS::decode_opt_data_elt_header(d, attr_info);
      if (a.check_length(del)) {
	TS::decode_string(d, a.rep(), del);
	a.update_rep();
	return true;
      }
      else if ((del == TransferSyntax::TagNotFound) || (del == 0) ){
	return false;
      }
      else
	throw DVREncodingException();
      return false;
    }

    void encode_empty(DStream& d, Self& a, const Attribute& attr_info){
      TS::encode_data_elt_header(d, attr_info, 0);
    }

    void encode(DStream& d, Self& a, const Attribute& attr_info){
      // perform padding
      string single_str = a.rep(); // copy representation string to ours
      a.padder(single_str);
      int del = single_str.size();
      TS::encode_data_elt_header(d, attr_info, del);
      TS::encode_string(d, single_str, del);
    }

  };

};

// Base class for String VR's with VM > 1

template <class InnerVR, class SizeFun, class CheckLenFun>
class StringVRm : public vector< InnerVR >, public AtomicVR {
public:

  typedef StringVRm<InnerVR, SizeFun, CheckLenFun> Self;

  StringVRm() {}
  SizeFun size_fun;
  CheckLenFun check_length_fun;
  bool check_length(int len) {
    check_zero_length(len);
    return check_length_fun(len);
  }
  typename InnerVR::Padder padder;
  string toString() const {
    string str = "<";
    if (!empty()) {
      const_iterator i = begin(), j = end();
      str += i->toString();
      i++;
      for (; i!=j ; i++)
	str += string(",") + i->toString();
    }
    return str + ">";
  }
  const char* selName() { return InnerVR::name; }

  InnerVR & genElement()
  {
    push_back(InnerVR());
    iterator last = end();
    last--;
    return *last; // allocate a new VR at the end of vector
  }

  template<class TS = ImplicitVRLittleEndian>
  class Coder : public VR::Coder {
  public:
    bool do_decode(DStream & d, Self & a, int del) {
      //dgn(string("multiplicity: ") + a.size_fun.toString());
      a.erase(a.begin(), a.end()); // cleanse storage
      int number_of_elts = 0;
      int pos = 0;// newpos = 0;
      while ( pos < del ) {
	InnerVR & elt = a.genElement();
	int len = TS::decode_delimited_string(d, elt.rep(), del-pos); // *** IMPLEMENT THIS!
	if (!elt.check_length(len))
	  throw DVREncodingException();
	elt.update_rep();
	pos += len;
	number_of_elts++;
      }
      return a.check_length(number_of_elts);
    }
		
    void decode_mandatory(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (!do_decode(d, a, del))
	throw DVREncodingException();
    }
		
    bool decode_required(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (del == 0) {				// no value field
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }
		
    bool decode_optional(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_opt_data_elt_header(d, attr_info);
      if ( (del == TransferSyntax::TagNotFound) || (del == 0) ) {
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }

    void encode_empty(DStream& d, Self& a, const Attribute& attr_info){
      TS::encode_data_elt_header(d, attr_info, 0);
    }

    void encode(DStream& d, Self& a, const Attribute& attr_info){
      iterator i = a.begin(), j = a.end();
      if ( i == j ) return;
      string big = (i++)->rep();
      for (; i!=j ; i++) {
	big += string("\\") + i->rep();	
      }
      // perform padding
      a.padder(big);
      int del = big.size();
      TS::encode_data_elt_header(d, attr_info, del);
      TS::encode_string(d, big, del);
    }

  };

};

// Application Entity VR
extern const char *AEminus;
//extern const string AEminus;
class AE : public GenericStringVR< UBSize<16>, UBLenCheck<16>,
	   IgnoreLTSpaces, CharRepDefMinus<&AEminus> >
{
public:
  typedef Self Base;
  AE() {}
  AE(const char *s) : Base(s) { custom_rep(); }
  AE(string s) : Base(s) { custom_rep(); }
  //void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Age String VR
extern const char* ASplus;
//extern const string ASplus;
class AS : public GenericStringVR<FixedSize<4>, FixedLenCheck<4>,
	   IgnoreNone, CharRepDigitPlus<&ASplus> >
{
public:
  typedef Self Base;

  enum AgeType { days, weeks, months, years };

  AS() : Base("000D"), age_type(days), age(0) {}
  AS(const char *s) : Base(s) { custom_rep(); }
  AS(string s) : Base(s) { custom_rep(); }
  AS(int, AgeType);

  int operator *() const;
  string toString() const;
  void custom_rep();

  const char* selName() const { return name; }
  const static char name[3];
private:
  AgeType age_type;
  int age;
};

// Code String VR
// VR for Defined Terms
extern const char* CSplus;
//extern const string CSplus;
class CS : public GenericStringVR< UBSize<16>, UBLenCheck<16>,
	   IgnoreLTSpaces, CharRepAlphaNumPlus<&CSplus> >
{
public:
  typedef Self Base;
  CS() {}
  CS(const char *s) : Base(s) {custom_rep();}
  CS(string s) : Base(s) {custom_rep();}
  //void custom_rep() {}

  const char* selName() const { return name; }
  const static char name[3];
};


// Date VR
extern const char* DAplus;
//extern const string DAplus;
class DA : public GenericStringVR< FixedSize<8>, FixedLenCheck<8>,
	   IgnoreNone, CharRepDigitPlus<&DAplus> >
{
public:
  typedef Self Base;
  DA() : Base("19700101"), year(1970), month(1), day(1) {} // UNIX!
  DA(const char *s) : Base(s) {custom_rep();}
  DA(string s) : Base(s) {custom_rep();}
  DA(int d, int m, int y);
  string toString() const;
  Time operator*() const; 
  void custom_rep();
  int selYear() const { return year; }
  int selMonth() const { return month; }
  int selDay() const { return day; }
  const char* selName() const { return name; }
  const static char name[3];
private:
  int year, month, day;
  static const char* month_array[];
};


// Decimal String VR
extern const char* DSplus;
//extern const string DSplus;
class DS : public GenericStringVR< UBSize<16>, UBLenCheck<16>,
	   IgnoreLTSpaces, CharRepDigitPlus<&DSplus> >
{
public:
  typedef Self Base;
  DS() : Base("0") {}
  DS(const char *s) : Base(s) {custom_rep();}
  DS(string s) : Base(s) {custom_rep();}
  DS(int i) {
    value = int_to_str(i);
  }
  DS(double d) {
    value = double_to_str(d);
  }
  double operator*() const { return str_to_double(value); }
  //void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Date Time VR
// later
extern const char* DTplus;
//extern const string DTplus;
class DT : public GenericStringVR< UBSize<26>, UBLenCheck<26>,
	   IgnoreLTSpaces, CharRepDigitPlus<&DTplus> >
{
public:
  typedef Self Base;
  DT() : Base("19720101"), timestamp(0,0)  {} //CODE: a more general time
  DT(const char *s) : Base(s) {custom_rep();}
  DT(string s) : Base(s) {custom_rep();}

  Time operator*() const { return timestamp; }
  void custom_rep();

  const char* selName() const { return name; }
  const static char name[3];
private:
  Time timestamp;
};

// Integer String VR
// characters: 0-9, +, -
extern const char* ISplus;
//extern const string ISplus;
class IS : public GenericStringVR< UBSize<12>, UBLenCheck<12>,
	   IgnoreLTSpaces, CharRepDigitPlus<&ISplus> >
{
public:
  typedef Self Base;
  IS() : Base("0") {}
  IS(const char *s) : Base(s) {custom_rep();}
  IS(string s) : Base(s) {custom_rep();}
  IS(int n) : Base(int_to_str(n)) {custom_rep();}
  int operator*() const { return str_to_int(value); }
  //void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Long String VR
extern const char* LOminus;
//extern const string LOminus;
class LO : public GenericStringVR< UBSize<64>, UBLenCheck<64>,
	   IgnoreLTSpaces, CharRepDefMinus<&LOminus> > {
public:
	typedef Self Base;
  LO() {}
  LO(const char *s) : Base(s) {custom_rep();}
  LO(string s) : Base(s) {custom_rep();}
	//void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Long Text VR
class LT : public GenericStringVR< UBSize<1024>, UBLenCheck<1024>,
	   IgnoreTSpaces, CharRepDef >
{
public:
  typedef Self Base;
  LT() {}
  LT(const char *s) : Base(s) {custom_rep();}
  LT(string s) : Base(s) {custom_rep();}
  //void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Person Name VR
extern const char* PNminus;
//extern const string PNminus;
class PN : public GenericStringVR< UBSize<64*5>, UBLenCheck<64*5>,
	   IgnoreTSpaces, CharRepDefMinus<&PNminus> >
{
public:
  typedef Self Base;
  PN() : surname_len(0), name_len(0) {}
  PN(const char *s) : Base(s) {custom_rep();}
  PN(const string& s) : Base(s) {custom_rep();}
  PN(const string& surname, const string& name) : Base( surname + "^" + name ) { custom_rep();} 
  void custom_rep();
  string selFamilyName() const;
  string selGivenName() const;
  string toString() const;
  const char* selName() const { return name; }
  const static char name[3];
private:
  int surname_len;
  int name_len;
};

// Short String VR
extern const char* SHminus;
//extern const string SHminus;
class SH : public GenericStringVR< UBSize<16>, UBLenCheck<16>,
	   IgnoreLTSpaces, CharRepDefMinus<&SHminus> >
{
public:
  typedef Self Base;
  SH() {}
  SH(const char *s) : Base(s) {custom_rep();}
  SH(string s) : Base(s) {custom_rep();}
  //void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Short Text VR
class ST : public GenericStringVR< UBSize<1024>, UBLenCheck<1024>,
	   IgnoreTSpaces >
{
public:
  typedef Self Base;
  ST() {}
  ST(const char *s) : Base(s) {custom_rep();}
  ST(string s) : Base(s) {custom_rep();}
  //void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Time VR
extern const char* TMplus;
//extern const string TMplus;
class TM : public GenericStringVR< UBSize<16>, UBLenCheck<16>,
	   IgnoreTSpaces, CharRepDigitPlus<&TMplus> >
{
public:
  typedef Self Base;
  TM() : Base("000000"), hour(0), minute(0), second(0) {}
  TM(const char *s) : Base(s) {custom_rep();}
  TM(string s) : Base(s) {custom_rep();}
  TM(int h, int m, int s);

  string toString() const;
  void custom_rep();
  int selHour() const { return hour; }
  int selMinute() const { return minute; }
  int selSecond() const { return second; }
  const char* selName() const { return name; }
  const static char name[3];
private:
  int hour, minute, second;
};


// UID Value Representation
// pad with 0 to achieve even length
extern const char* UIplus;
//extern const string UIplus;
class UI : public GenericStringVR< UBSize<64>, UBLenCheck<64>,
	   IgnoreTNull, CharRepDigitPlus<&UIplus>, CharPadder<'\0'> > {
public:
  typedef Self Base;
  UI() {}
  UI(const char *s) : Base(s) {custom_rep();}
  UI(const string &s) : Base(s) {custom_rep();}
  //int operator*() const { return str_to_int(value); }
  //void custom_rep() {}
  const char* selName() const { return name; }
  const static char name[3];
};

// Date & Time range VR's, intended for Identifier Coding

// RangeDate, implements a range of dates and single dates as well
extern const char* rangeDAplus;
//extern const string rangeDAplus;
class rangeDA : public GenericStringVR< UBSize<18>, UBLenCheck<18>,
		IgnoreNone, CharRepDigitPlus<&rangeDAplus> > {
public:
  enum DA_Type { single, range, prior, subsequent };
  typedef Self Base;
  // single: single date that is starting
  // range: inclusive between starting and ending
  // prior: all dates prior to and including ending
  // subsequent: all dates subsequent to and including starting
  rangeDA() : Base("19720101") {custom_rep();}
  rangeDA(const char *s) : Base(s) {custom_rep();}
  rangeDA(string s) : Base(s) {custom_rep();}
  rangeDA(DA_Type t, const DA& first, const DA& second = DA());
  string toString() const;
  void custom_rep();
  const DA& selStarting() const { return starting; }
  const DA& selEnding() const { return ending; }
  const DA_Type selType() const { return type; }
  const char* selName() const { return name; }
  const static char name[3];
private:
  DA starting, ending;
  DA_Type type;
};

// RangeTime, implements a range of times and single times as well
extern const char* rangeTMplus;
//extern const string rangeTMplus;
class rangeTM : public GenericStringVR< UBSize<14>, UBLenCheck<14>,
		IgnoreNone, CharRepDigitPlus<&rangeTMplus> > {
public:
  typedef Self Base;
  enum TM_Type { single, range, prior, subsequent };
  // single: single date that is starting
  // range: inclusive between starting and ending
  // prior: all dates prior to and including ending
  // subsequent: all dates subsequent to and including starting
  rangeTM() : Base("000000") {custom_rep();}
  rangeTM(const char *s) : Base(s) {custom_rep();}
  rangeTM(string s) : Base(s) {custom_rep();}
  rangeTM(TM_Type t, const TM& first, const TM& second = TM());
  string toString() const;
  void custom_rep();
  const TM& selStarting() const { return starting; }
  const TM& selEnding() const { return ending; }
  const TM_Type selType() const { return type; }
  const char* selName() const { return name; }
  const static char name[3];
private:
  TM starting, ending;
  TM_Type type;
};

// String VR fixed VM

template <class InnerVR, int arity>
class StringVRf : public StringVRm< InnerVR, FixedSize<arity>, FixedLenCheck<arity> > {};

// Names of fixed VM string VRs

template <int arity>
	class AEf : public StringVRf<AE, arity> {};
template <int arity>
	class ASf : public StringVRf<AS, arity> {};
template <int arity>
	class CSf : public StringVRf<CS, arity> {};
template <int arity>
	class DAf : public StringVRf<DA, arity> {};
template <int arity>
	class DSf : public StringVRf<DS, arity> {};
template <int arity>
	class DTf : public StringVRf<DT, arity> {};
template <int arity>
	class ISf : public StringVRf<IS, arity> {};
template <int arity>
	class LOf : public StringVRf<LO, arity> {};
template <int arity>
	class LTf : public StringVRf<LT, arity> {};
template <int arity>
	class PNf : public StringVRf<PN, arity> {};
template <int arity>
	class SHf : public StringVRf<SH, arity> {};
template <int arity>
	class STf : public StringVRf<ST, arity> {};
template <int arity>
	class TMf : public StringVRf<TM, arity> {};
template <int arity>
	class UIf : public StringVRf<UI, arity> {};


// String VR Range VM

template <int lower, int upper> class RangeSize
{
public:
  int operator()() {
    return (upper);
  }
  string toString() { return string("length:") + lower + "-" +upper; }
};

template <int lower, int upper> class RangeLenCheck
{
public:
  bool operator()(int len) {
    return ((lower <= len) && (len <= upper) );
  }
};

template <class InnerVR, int lower, int upper>
class StringVRr : public StringVRm< InnerVR, RangeSize<lower, upper>, RangeLenCheck<lower, upper> > {};

// Names of range VM string VRs

template <int lower, int upper>
	class AEr : public StringVRr<AE, lower, upper> {};
template <int lower, int upper>
	class ASr : public StringVRr<AS, lower, upper> {};
template <int lower, int upper>
	class CSr : public StringVRr<CS, lower, upper> {};
template <int lower, int upper>
	class DAr : public StringVRr<DA, lower, upper> {};
template <int lower, int upper>
	class DSr : public StringVRr<DS, lower, upper> {};
template <int lower, int upper>
	class DTr : public StringVRr<DT, lower, upper> {};
template <int lower, int upper>
	class ISr : public StringVRr<IS, lower, upper> {};
template <int lower, int upper>
	class LOr : public StringVRr<LO, lower, upper> {};
template <int lower, int upper>
	class LTr : public StringVRr<LT, lower, upper> {};
template <int lower, int upper>
	class PNr : public StringVRr<PN, lower, upper> {};
template <int lower, int upper>
	class SHr : public StringVRr<SH, lower, upper> {};
template <int lower, int upper>
	class STr : public StringVRr<ST, lower, upper> {};
template <int lower, int upper>
	class TMr : public StringVRr<TM, lower, upper> {};
template <int lower, int upper>
	class UIr : public StringVRr<UI, lower, upper> {};

// String VR variable VM

class VarSize
{
public:
  int operator()() {
    return (-1);
  }
  string toString() { return string("length: 1-n"); }
};

class VarLenCheck
{
public:
  bool operator()(int len) {
    return true;
  }
};

template <class InnerVR>
class StringVRv : public StringVRm< InnerVR, VarSize, VarLenCheck > {};

class AEv : public StringVRv<AE> {};
class ASv : public StringVRv<AS> {};
class CSv : public StringVRv<CS> {};
class DAv : public StringVRv<DA> {};
class DSv : public StringVRv<DS> {};
class DTv : public StringVRv<DT> {};
class ISv : public StringVRv<IS> {};
class LOv : public StringVRv<LO> {};
class LTv : public StringVRv<LT> {};
class PNv : public StringVRv<PN> {};
class SHv : public StringVRv<SH> {};
class STv : public StringVRv<ST> {};
class TMv : public StringVRv<TM> {};
class UIv : public StringVRv<UI> {};


// String VR even variable VM

class EvenVarSize
{
public:
  int operator()() {
    return (-2);
  }
  string toString() { return string("length: 1-2n"); }
};

class EvenVarLenCheck
{
public:
  bool operator()(int len) {
    return (len % 2 == 0);
  }
};

template <class InnerVR>
class StringVRe : public StringVRm< InnerVR, VarSize, VarLenCheck > {};

class AEe : public StringVRe<AE> {};
class ASe : public StringVRe<AS> {};
class CSe : public StringVRe<CS> {};
class DAe : public StringVRe<DA> {};
class DSe : public StringVRe<DS> {};
class DTe : public StringVRe<DT> {};
class ISe : public StringVRe<IS> {};
class LOe : public StringVRe<LO> {};
class LTe : public StringVRe<LT> {};
class PNe : public StringVRe<PN> {};
class SHe : public StringVRe<SH> {};
class STe : public StringVRe<ST> {};
class TMe : public StringVRe<TM> {};
class UIe : public StringVRe<UI> {};


// Binary VR's

template <class _Value, class _BaseCoder>
class BinaryVR : public AtomicVR {
public:

  typedef _Value Value;
  typedef _BaseCoder BaseCoder;
  typedef BinaryVR<Value, BaseCoder> Self;

  enum { length=sizeof(Value) };
  typedef FixedLenCheck<length> CheckLenFun;

  BinaryVR() : value(0) {}
  BinaryVR<Value, BaseCoder>(Value f) : value(f) {}
  int get_length() {return length;}
  CheckLenFun check_length_fun;
  bool check_length(int len) {
    check_zero_length(len);
    return check_length_fun(len);
  }
  operator Value () { return value; }
  Value operator*() const {return value;}
  Value& ref() { Value &aref =  value; return aref; }
  string toString() { return conv_to_string(value); }
  const char* selName() const { return name; }
  static const char * selSName() { return name; }
  const static char name[3];

private:
  Value value;
public:

  template<class TS = ImplicitVRLittleEndian>
  class Coder /* VC6 BUG : public BaseCoder::Coder<TS>*/ {
  public:

    // VC6 KLUDGE!!!
    void do_decode(DStream& d, Value& v) {
	typename BaseCoder::Coder<TS> coder;
	coder.do_decode(d, v);
    }
    void do_encode(DStream& d, Value& v) {
      typename BaseCoder::Coder<TS> coder;
      coder.do_encode(d, v);
    }
    // END VC6 KLUDGE

    void decode_mandatory(DStream& d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      //dgn(string("decode_mand:") + Self::length);
      if (a.check_length(del)) {
	do_decode(d, a.ref());
      }
      else
	throw DVREncodingException();
    }
    bool decode_required(DStream& d, Self& a, const Attribute& attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (a.check_length(del)) {
	typename BaseCoder::Coder<TS> coder;
	coder.do_decode(d, a.ref());
	return true;
      }
      else if (del == 0) {				// no value field
	return false;
      }
      else
	throw DVREncodingException();
      return false;
    }
    bool decode_optional(DStream& d, Self& a, const Attribute& attr_info) {
      int del = TS::decode_opt_data_elt_header(d, attr_info);
      if (a.check_length(del)) {
	typename BaseCoder::Coder<TS> coder;
	coder.do_decode(d, a.ref());
	return true;
      }
      else if ( (del == TransferSyntax::TagNotFound) || (del == 0) ) {
	return false;
      }
      else
	throw DVREncodingException();
      return false;
    }
    void encode_empty(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, 0);
    }
    void encode(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, Self::length);
      do_encode(d, a.ref());
    }
  };

#ifndef _MSC_VER
  friend bool operator< <>(const Self, const Self);
  friend bool operator== <>(const Self, const Self);
#else
  friend bool operator< (const Self, const Self);
  friend bool operator== (const Self, const Self);
#endif
};

template <class C, class K>
inline bool operator <(const BinaryVR<C, K> lhs, const BinaryVR<C, K> rhs) {
  return lhs.value < rhs.value;
}
template <class C, class K>
inline bool operator ==(const BinaryVR<C, K> lhs, const BinaryVR<C,K> rhs) {
  return lhs.value == rhs.value;
}

template <class T> class BinaryCoder
{
public:
  template <class TS> class Coder : public VR::Coder {
  public:
    void do_decode(DStream & ds, T& a) {
      TS::decode_binary(ds, a);
    }
    void do_encode(DStream & ds, T& a) {
      TS::encode_binary(ds, a);
    }
  };
};

template <class T> class TagCoder
{
public:
  template <class TS> class Coder : public VR::Coder {
  public:
    void do_decode(DStream & ds, T & a) {
      TS::decode_binary(ds, a.group);
      TS::decode_binary(ds, a.element);
    }
    void do_encode(DStream & ds, T & a) {
      TS::encode_binary(ds, a.group);
      TS::encode_binary(ds, a.element);
    }
  };
};

// Binary VR names
typedef BinaryVR<float, BinaryCoder<float> > FL;
typedef BinaryVR<double, BinaryCoder<double> > FD;
typedef BinaryVR<signed long, BinaryCoder<signed long> > SL;
typedef BinaryVR<signed short, BinaryCoder<signed short> > SS;
typedef BinaryVR<unsigned long, BinaryCoder<unsigned long> > UL;
typedef BinaryVR<unsigned short, BinaryCoder<unsigned short> > US;
typedef BinaryVR<Tag, TagCoder<Tag> > AT;


// Base class for Binary VR's with VM > 1

template <class InnerVR, class SizeFun, class CheckLenFun>
class BinaryVRm : public vector< InnerVR >, public AtomicVR {
public:

  typedef typename InnerVR::Value Value;
  typedef BinaryVRm<InnerVR, SizeFun, CheckLenFun> Self;

//   Self() {}
  BinaryVRm<InnerVR, SizeFun, CheckLenFun>() {}
// KLUDGE: possible g++ bug
  SizeFun get_size;
  int get_length() { return size() * InnerVR::length; }
  CheckLenFun check_length_fun;
  bool check_length(int len) {
    check_zero_length(len);
    return check_length_fun(len);
  }
  string toString() {
    string str = "<";
    if (!empty()) {
      iterator i = begin(), j = end();
      str += i->toString();
      i++;
      for (; i!=j ; i++)
	str += string(",") + i->toString();
    }
    return str + ">";
  }
  string selName() { return InnerVR::selSName(); }

  InnerVR & genElement()
  {
    push_back(InnerVR());
    iterator last = end();
    last--;
    return *last; // allocate a new VR at the end of vector
  }

  template<class TS = ImplicitVRLittleEndian>
    class Coder : VR::Coder /* VC6 Bug == public InnerVR::Coder<TS> */ {
  public:

    bool do_decode(DStream & d, Self & a, int del) {
      //dgn(string("multiplicity: ") + a.get_size.toString());
      int number_of_elts = del/InnerVR::length;
      a.erase(a.begin(), a.end()); // cleanse storage
      for (int i = number_of_elts-1; i>=0; i--) {
	InnerVR & elt = a.genElement();
        typename InnerVR::Coder<TS> base;
        base.do_decode(d, elt.ref());
      }
      return a.check_length(number_of_elts);
    }
		
    void decode_mandatory(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (!do_decode(d, a, del))
	throw DVREncodingException();
    }
		
    bool decode_required(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_req_data_elt_header(d, attr_info);
      if (del == 0) {				// no value field
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }
		
    bool decode_optional(DStream & d, Self & a, const Attribute & attr_info) {
      int del = TS::decode_opt_data_elt_header(d, attr_info);
      if ( (del == TransferSyntax::TagNotFound) || (del==0) ) {
	return false;
      }
      else if (do_decode(d, a, del))
	return true;
      else
	throw DVREncodingException();
      return false;
    }

    void encode_empty(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, 0);
    }
    void encode(DStream& d, Self& a, const Attribute& attr_info) {
      TS::encode_data_elt_header(d, attr_info, a.get_length());
      iterator i = a.begin(), j = a.end();
      for (; i!=j ; i++) {
        typename InnerVR::Coder<TS> base;
        base.do_encode(d, i->ref());
      }
    }

  };

};


// Binary VR fixed VM

template <class Value, int arity>
class BinaryVRf : public BinaryVRm< BinaryVR<Value, BinaryCoder<Value> >, FixedSize<arity>, FixedLenCheck<arity> > {};

// Names of fixed length binary VRs

template <int arity>
	class FLf : public BinaryVRf<float, arity> {};
template <int arity>
	class FDf : public BinaryVRf<double, arity> {};
template <int arity>
	class SLf : public BinaryVRf<signed long, arity> {};
template <int arity>
	class SSf : public BinaryVRf<signed short, arity> {};
template <int arity>
	class ULf : public BinaryVRf<unsigned long, arity> {};
template <int arity>
	class USf : public BinaryVRf<unsigned short, arity> {};
template <int arity>
	class ATf : public BinaryVRm< AT, FixedSize<arity>, FixedLenCheck<arity> > {};


// Binary VR range VM

template <class Value, int lower, int upper>
class BinaryVRr : public BinaryVRm< BinaryVR<Value, BinaryCoder<Value> >, RangeSize<lower, upper>, RangeLenCheck<lower, upper> > {};

// Names

template <int lower, int upper>
	class FLr : public BinaryVRr<float, lower, upper> {};
template <int lower, int upper>
	class FDr : public BinaryVRr<double, lower, upper> {};
template <int lower, int upper>
	class SLr : public BinaryVRr<signed long, lower, upper> {};
template <int lower, int upper>
	class SSr : public BinaryVRr<signed short, lower, upper> {};
template <int lower, int upper>
	class ULr : public BinaryVRr<unsigned long, lower, upper> {};
template <int lower, int upper>
	class USr : public BinaryVRr<unsigned short, lower, upper> {};
template <int lower, int upper>
  class ATr : public BinaryVRm< AT, RangeSize<lower, upper>, RangeLenCheck<lower, upper> > {};


// Binary VR variable VM


template <class Value>
class BinaryVRv : public BinaryVRm< BinaryVR<Value, BinaryCoder<Value> >, VarSize, VarLenCheck > {};

// Names

class FLv : public BinaryVRv<float> {};
class FDv : public BinaryVRv<double> {};
class SLv : public BinaryVRv<signed long> {};
class SSv : public BinaryVRv<signed short> {};
class ULv : public BinaryVRv<unsigned long> {};
class USv : public BinaryVRv<unsigned short> {};
class ATv : public BinaryVRm< AT, VarSize, VarLenCheck > {};
 
// Binary VR even variable VM


template <class Value>
class BinaryVRe : public BinaryVRm< BinaryVR<Value, BinaryCoder<Value> >, VarSize, VarLenCheck > {};

// Names

class FLe : public BinaryVRe<float> {};
class FDe : public BinaryVRe<double> {};
class SLe : public BinaryVRe<signed long> {};
class SSe : public BinaryVRe<signed short> {};
class ULe : public BinaryVRe<unsigned long> {};
class USe : public BinaryVRe<unsigned short> {};
class ATe : public BinaryVRm< AT, VarSize, VarLenCheck > {};

#endif
