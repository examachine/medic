/*
**
** Implementation file for General module
**
**
**
** exa
**
*/

#include "General.hxx"
//#include "KernelInterface.hxx"

// convert short to hexadecimal string
string short_to_hexstr(const short n)
{
  string s;
  for (int i=12; i>=0; i -= 4 ) {
    char digit =  (n >> i) & 0xf;
    if (digit <=9)
      digit += '0';
    else
      digit += 'A' - 10;
    s += digit;
  }
  return s;
}

// convert int to hexadecimal string
string int_to_hexstr(const int n)
{
  string s;
  for (int i=28; i>=0; i -= 4 ) {
    char digit =  (n >> i) & 0xf;
    if (digit <=9)
      digit += '0';
    else
      digit += 'A' - 10;
    s += digit;
  }
  return s;
}

// convert hexadecimal string to int
int hexstr_to_int(const string s)
{
  int val = 0;
  int k = 1;
  for (int n = s.length()-1; n>=0; n--, k*=16) {
    int digit = s[n] - '0';
    if (digit > 9)
	  digit -= 'A' - 10;
    val += (s[n] - '0') * k ;
  }
  return val;
}

// default template
