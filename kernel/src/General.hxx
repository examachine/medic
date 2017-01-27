/*
** General include file
**
** eXa
**
*/

#ifndef Kernel_General_Interface
#define Kernel_General_Interface 1

#include "ANSILibrary.hxx"

#include "Utility.hxx"
// using namespace Utility;

#ifdef _MSC_VER
#pragma warning(disable:4804)
#pragma warning(disable:4786)
#endif // _MSC_VER

string short_to_hexstr(short n);

string int_to_hexstr(int n);

int hexstr_to_int(string s);

// convert integer to decimal string
inline string int_to_str(const int n)
{
  char *buf = new char[32];
  sprintf(buf, "%d", n);
  string decimal_str = string(buf);
  delete buf;
  return decimal_str;
}

// convert with padding
inline string int_to_str(int n, int l)
{
  string str = int_to_str(n);
  int diff = l - str.length();
  if (diff>0)
    return string(diff, '0') + str;
  return str;
}

// convert decimal string to integer
inline int str_to_int(string s)
{
  return atoi(s.c_str());
}

// convert float to decimal string
inline string float_to_str(float n)
{
  char *buf = new char[96];
  sprintf(buf, "%f", n);
  string float_str = string(buf);
  delete buf;
  return float_str;
}

// convert decimal string to float
inline float str_to_float(string s)
{
  return (float)atof(s.c_str());
}

// convert double to decimal string
inline string double_to_str(double n)
{
  char *buf = new char[96];
  sprintf(buf, "%G", n);
  string double_str = string(buf);
  delete buf;
  return double_str;
}

// convert decimal string to double
inline double str_to_double(string s)
{
  return atof(s.c_str());
}

inline bool odd(int n) {
  return (n & 1);
}

template<class T> inline string conv_to_string(const T n) {
//#pragma error("no conversion possible!") 
  cerr << "no conversion possible!" << endl; 
#ifdef MSC_VER
  AfxMessageBox("no conversion possible!"); 
#endif
  exit(-1);
}

// BUG: are these explicit instantiations necessary?
template<> inline string conv_to_string<int>(const int n) {
  return int_to_str(n);
}
template<> inline string conv_to_string<char>(const char n) {
  return int_to_str(n);
}
template<> inline string conv_to_string<unsigned char>(const unsigned char n) {
  return int_to_str(n);
}
template<> inline string conv_to_string<short>(const short n) {
  return int_to_str(n);
}
template<> inline string conv_to_string<long>(const long n) {
  return int_to_str(n);
}
template<> inline string conv_to_string<unsigned short>(const unsigned short n) {
  return int_to_str(n);
}
template<> inline string conv_to_string<unsigned long>(const unsigned long n) {
  return int_to_str(n);
}
template<> inline string conv_to_string<float>(const float n) {
  return float_to_str(n);
}
template<> inline string conv_to_string<double>(const double n) {
  return double_to_str(n);
}

inline string operator +(string& lhs, unsigned int rhs) {
  return lhs +  int_to_str(rhs);
};

inline string operator +(const string& lhs, const int rhs) {
  return lhs + conv_to_string(rhs);
};

inline string operator +(string& lhs, float rhs) {
  return lhs + conv_to_string(rhs);
};

inline string operator +(string& lhs, double rhs) {
  return lhs + conv_to_string(rhs);
};

#endif
