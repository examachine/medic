//
//
// C++ Interface for module: Critical_Region
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Critical_Region_Interface
#define Critical_Region_Interface

#include "General.hxx"

#include "Mutex.hxx"

#ifndef _MSC_VER

class Critical_Region : protected Mutex
{
public:
//   Critical_Region(bool _enter = false)
//     : enter_now(_enter) {
//     nlog << "no critical region id! " << pthread_self()  << endl;
//     assert(false);
//     start();
//   }

  Critical_Region(const string & _id, bool _enter = false)
    : Mutex(_id), enter_now(_enter) {
    start();
  }

  void start()
  {
    if (enter_now) {
      soft_enter();
    }
  }

  void print_id() {
    nlog << "Critical_Region: " << id << endl;
  }

  // no need ~Mutex does the clean up
//   ~Critical_Region() {
//     if (enter_now)
//       leave();
//   }

  void enter() {
//     nlog << "critical_region: enter " << id << endl;
    lock();
  }

  // do a spin lock
  void soft_enter() {
//     nlog << "critical_region: soft_enter " << id << endl;
    while (!try_lock()) {
    }
  }

  void leave() {
//     nlog << "critical_region: leave " << id << endl;
    unlock();
  }
private:
  bool enter_now;
};

#else

#endif // _MSC_VER

#endif
