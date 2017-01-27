//
//
// C++ Interface for module: Barrier
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Barrier_Interface
#define Barrier_Interface

#include "General.hxx"

#include "Condition.hxx"

#ifndef _MSC_VER

class Barrier : Monitor_Base
{
public:
  Barrier() : Monitor_Base("Barrier") {
    init();
  }
  Barrier(string id) : Monitor_Base(id){
    init();
  }

  void init() {
    soft_enter();
    blocked_threads = 0;
    instance_id = 0;
    // initialize the condition variable
    enter.init(this);
    leave();
    nlog << "Barrier up" << endl;
  }
  

  // all threads call this
  // gives number of distinct threads to hit the barrier
  void sync(int num_threads, bool * passed) {
    assert(*passed == false);

    int cancel;

    // enter here
    soft_enter();
    blocked_threads++;
    int id = instance_id;

    nlog << "[" << pthread_self() << "] entered barrier" << endl;

    // we're waiting for num_threads threads to get in here

    if (blocked_threads!=num_threads) {
      // all threads except last entering wait on enter
//       pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cancel);
      while (id == instance_id) {
	enter.wait();
      }
    }
    else {
      // the last thread simply broadcasts and released the barrier
      // it also increments the barrier instance so we can spin for
      // that
      instance_id++;
      *passed = true;
      blocked_threads=0;
      enter.broadcast();
      nlog << "Barrier " << id << " completed for "
	   << num_threads<< " threadz" << endl;
    }

    leave();
  }

protected:
  // think of this object as a finite state atomicity machine :)
  Condition enter;
  int blocked_threads;
  int instance_id;
};

#else

#endif // _MSC_VER

#endif
