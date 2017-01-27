//
//
// C++ Interface for module: Time
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Time_Interface
#define Time_Interface

#include "General.hxx"

#ifndef _MSC_VER

class Time {
public:
  Time() : time_rep() {
    if (gettimeofday(&time_rep, NULL)==-1) // current time
      cerr << "error: can't get timeofday" << endl;
  }
  Time( int year, int month, int day,
	int hour, int minute, int second ) {
    // CODE: calendar calculation
    time_rep.tv_sec = hour*3600 + minute*60 + second ;
    time_rep.tv_usec = 0;
  }
  Time(long int sec, long int usec) {
    time_rep.tv_sec = sec;
    time_rep.tv_usec = usec;
  }
  operator const timeval() { return time_rep; }
  ostream& print(ostream& out) {
    out << time_rep.tv_sec << "." << time_rep.tv_usec << " seconds";
  }
  Time operator -(const Time rhs) {
    return Time( (time_rep.tv_sec - rhs.time_rep.tv_sec),
		 (time_rep.tv_usec - rhs.time_rep.tv_usec));
  }
  //Time(time_t t) : time_rep(t) {}
  //operator const time_t() { return time_rep; }
private:
  struct timeval time_rep;
  //time_t time_rep;
};

#else

#include "afx.h"

class Time : private CTime {
public:
  Time() : CTime(CTime::GetCurrentTime()) {
  }
  Time( int year, int month, int day,
	int hour, int minute, int second )
	: CTime (year, month, day, hour, minute, second) {
  }
  Time(long int sec, long int usec) {
    // CODE: corresponding CTime constructor
  }
  operator const CTime() { return time_rep; }
  ostream& print(ostream& out) {
    out << time_rep.Format("%A, %B %d, %Y");
  }
  CTimeSpan operator -(const Time rhs) {
    return time_rep - rhs.time_rep;
  }
private:
  CTime time_rep;
  };

#endif // _MSC_VER

#endif
