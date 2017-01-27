//
//
// Implementation file for VR module
//
// Value Representation
//
// exa - aka Eray Ozkural
//
//

#ifdef _MSC_VER
#include "stdafx.h"
#endif // _MSC_VER

#include "KernelInterface.hxx"

void VR::dgn(string s)
{
  dicom_app.report( "VR:" + s );
}

void VR::Coder::dgn(string s)
{
  dicom_app.report( "VR Coder:" + s );
}

/*template <class Value, int arity> string BinaryVRf<Value, arity>::toString()
{
	string str = "<";
	if (!empty()) {
		iterator a = begin(), b = end();
		str += a->toString();
		for (; a!=b; ++a)
			str += string(", ") + a->toString();
	}
	return str + ">";
}*/

//const char VR::name[3] = "VR";

//const char AtomicVR::name[3] = "VR";

// VR specific
const char AE::name[3] = "AE";
const char* AEminus = "\n\f\r\x016";
//const string AEminus("\n\f\r\x016");

const char AS::name[3] = "AS";
const char* ASplus = "DWMY";
//const string ASplus("DWMY");

const char AT::name[3] = "AT";

const char CS::name[3] = "CS";
const char* CSplus = " _";
//const string CSplus(" _");

const char DA::name[3] = "DA";
const char* DAplus = "";
//const string DAplus("");
const char* DA::month_array[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

const char DS::name[3] = "DS";
const char* DSplus = "+-Ee.";
//const string DSplus("+-Ee.");

const char DT::name[3] = "DT";
const char* DTplus = "+-.";
//const string DTplus("+-.");

const char FL::name[3] = "FL";

const char FD::name[3] = "FD";

const char IS::name[3] = "IS";
const char* ISplus = "+-";
//const string ISplus("+-");

const char LO::name[3] = "LO";
const char* LOminus = "\\\n\f\r";
//const string LOminus("\\\n\f\r");

const char LT::name[3] = "LT";

const char OB::name[3] = "OB";

const char OW::name[3] = "OW";

const char PN::name[3] = "PN";
const char* PNminus = "\n\f\r";
//const string PNminus("\n\f\r");

const char SH::name[3] = "SH";
const char* SHminus = "\\\n\f\r";
//const string SHminus("\\\n\f\r");

const char SL::name[3] = "SL";

//const char SQ::name[3] = "SQ";

const char SS::name[3] = "SS";

const char ST::name[3] = "ST";

const char TM::name[3] = "TM";
const char* TMplus = ".";
//const string TMplus(".");

const char UI::name[3] = "UI";
const char* UIplus = ".";
//const string UIplus(".");

const char UL::name[3] = "UL";

const char US::name[3] = "US";


AS::AS(int a, AgeType t) : age(a), age_type(t)
{
  // fill in value here **** value;
}

int AS::operator * () const
{
  switch (age_type) {
  case days: return age; break;
  case weeks: return age*7; break;
  case months: return age*30; break;
  case years: return age*365; break;
  }
  return 0; // never executed
}

string AS::toString() const
{
  string pretty = int_to_str(age);
  switch (age_type) {
  case days: pretty += " days"; break;
  case weeks: pretty += " weeks"; break;
  case months: pretty += " months"; break;
  case years: pretty += " years"; break;
  }
  return pretty;
}

void AS::custom_rep()
{
  switch (value[3]) {
  case 'D': age_type = days; break;
  case 'W': age_type = weeks; break;
  case 'M': age_type = months; break;
  case 'Y': age_type = years; break;
  }
  value[3] = ' ';
  age = str_to_int(value);
}

DA::DA(int d, int m, int y) : day(d), month(m), year(y)
{
  // update string
  value = int_to_str(year, 4) +
    int_to_str(month, 2) +
    int_to_str(day, 2);
}

string DA::toString() const {
  return int_to_str(day) + '/' +
    month_array[month-1] + '/' +
    int_to_str(year);
}

Time DA::operator* () const
{
  return Time(year, month, day, 0, 0, 0);
}

void DA::custom_rep() {
  char *buf = new char[5];
  value.copy(buf, 4, 0);
  buf[4] = 0;
  year = str_to_int(buf);
  value.copy(buf, 2, 4);
  buf[2] = 0;
  month = str_to_int(buf);
  value.copy(buf, 2, 6);
  day = str_to_int(buf);
}

void DT::custom_rep() {
  string century; int century_v = 0;
  string year; int year_v = 0;
  string month; int month_v = 0;
  string day; int day_v = 0;
  string hour; int hour_v = 0;
  string minute; int minute_v = 0; 
  string second; int second_v = 0;

  int size = value.size();
  if (size > 0 ) {
    century.assign(value, 0, 2);
    int century_v = str_to_int(century);
    if (size > 4) {
      year.assign(value, 2, 2);
      int year_v = str_to_int(year);
      if (size > 6) {
	month.assign(value, 4, 2);
	int month_v = str_to_int(month);
	if (size > 8) {
	  day.assign(value, 6, 2);
	  int day_v = str_to_int(day);
	  if (size > 10) {
	    hour.assign(value, 8, 2);
	    int hour_v = str_to_int(hour);
	    if (size > 12) {
	      minute.assign(value, 10, 2);
	      int minute_v = str_to_int(minute);
	      if (size > 14) {
		second.assign(value, 12, 2);
		int second_v = str_to_int(second);
	      }
	    }
	  }
	}
      }
    }
  }
  //string frac_second; frac_second.assign(value, 6, 2);
  //string offset; offset.assign(value, 6, 2);

  timestamp = Time( century_v*100 + year_v, month_v, day_v, hour_v, minute_v, second_v);
}

void PN::custom_rep()
{
  int first_delim, second_delim;
  first_delim = value.find('^');
  if (first_delim == string::npos) {
    surname_len = value.size();
    name_len = 0;
  }
  else {
    surname_len = first_delim;
    second_delim = value.find('^', first_delim+1);
    if (second_delim == string::npos) {
      name_len = value.size() - first_delim - 1;
    }
    else {
      name_len = second_delim - first_delim - 1;
    }
  }
}

string PN::selFamilyName() const
{
  string r;
  if (surname_len == 0)
    return "";
  else {
    r.assign(value, 0, surname_len);
    return r;
  }
}

string PN::selGivenName() const
{
  string r;
  if (name_len == 0)
    return "";
  else {
    r.assign(value, surname_len+1, name_len);
    return r;
  }
}

string PN::toString() const
{
  return selFamilyName() + ", " + selGivenName();
}

TM::TM(int h, int m, int s) : hour(h), minute(m), second(s)
{
  // update string
  value = int_to_str(hour, 2) +
    int_to_str(minute, 2) +
    int_to_str(second, 2);
}

void TM::custom_rep()
{
  string hour_s; hour = 0;
  string minute_s; minute = 0; 
  string second_s; second = 0;

  int size = value.size();
  if (size > 0) {
    hour_s.assign(value, 0, 2);
    int hour = str_to_int(hour_s);
    if (size > 2) {
      minute_s.assign(value, 2, 2);
      int minute = str_to_int(minute_s);
      if (size > 4) {
	second_s.assign(value, 4, 2);
	int second = str_to_int(second_s);
      }
    }
  }
}

string TM::toString() const {
  return int_to_str(hour) + ":" + int_to_str(minute) + ":" + int_to_str(second);
}

const char rangeDA::name[3] = "DA";
const char *rangeDAplus = "-";
//const string rangeDAplus("-");

rangeDA::rangeDA(DA_Type t, const DA& first, const DA& second) : type(t)
{
  // update string, and custom rep
  switch (type) {
  case single:
    starting = first;
    value = starting.value;
    break;
  case range:
    starting = first;
    ending = second;
    value = starting.value + '-' + ending.value;
    break;
  case prior:
    ending = first;
    value = '-' + ending.value;
    break;
  case subsequent:
    starting = first;
    value = starting.value + '-';
    break;
  }
}

string rangeDA::toString() const {
  switch (type) {
  case single:
    return starting.toString();
  case range:
    return starting.toString() + '-' + ending.toString();
  case prior:
    return '-' + ending.toString();
  case subsequent:
    return starting.toString() + '-';
  default:
    return "invalid date range";
  }
}

/*
Date_Range rangeDA::operator* () const
{
	return CTime(year, month, day, 0, 0, 0);
}
*/

void rangeDA::custom_rep() {
  // find the dash
  int size = value.size();
  int pos = value.find('-');
  if (pos==string::npos) {
    type = single;
    starting = DA(value);
  }
  else if (pos==0) {
    type = prior;
    ending = DA(value.substr(1, size-1));
  }
  else if (pos==size-1) {
    type = subsequent;
    starting = DA(value.substr(0, size-1));
  }
  else {
    type = range;
    starting = DA(value.substr(0, pos));
    ending = DA(value.substr(pos, size-pos));
  }
}

const char rangeTM::name[3] = "TM";
const char *rangeTMplus = "-";

rangeTM::rangeTM(TM_Type t, const TM& first, const TM& second) : type(t)
{
  // upTMte string, and custom rep
  switch (type) {
  case single:
    starting = first;
    value = starting.value;
    break;
  case range:
    starting = first;
    ending = second;
    value = starting.value + '-' + ending.value;
    break;
  case prior:
    ending = first;
    value = '-' + ending.value;
    break;
  case subsequent:
    starting = first;
    value = starting.value + '-';
    break;
  }
}

string rangeTM::toString() const {
  switch (type) {
  case single:
    return starting.toString();
  case range:
    return starting.toString() + '-' + ending.toString();
  case prior:
    return '-' + ending.toString();
  case subsequent:
    return starting.toString() + '-';
  default:
    return "invalid date range";
  }
}

void rangeTM::custom_rep() {
  // find the TMsh
  int size = value.size();
  int pos = value.find('-');
  if (pos==string::npos) {
    type = single;
    starting = TM(value);
  }
  else if (pos==0) {
    type = prior;
    ending = TM(value.substr(1, size-1));
  }
  else if (pos==size-1) {
    type = subsequent;
    starting = TM(value.substr(0, size-1));
  }
  else {
    type = range;
    starting = TM(value.substr(0, pos));
    ending = TM(value.substr(pos, size-pos));
  }
}
