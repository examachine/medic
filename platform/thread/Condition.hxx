//
//
// C++ Interface for module: Condition
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Condition_Interface
#define Condition_Interface

#include "General.hxx"

#include "Monitor.hxx"

// Condition Variable used to signal
// tasks on occurance of some condition

#ifndef _MSC_VER

class Condition
{
public:
  Condition(Monitor_Base * mon) {
    if (!mon)
      throw string("condition: no monitor given");
    init(mon);
  }

  Condition() {}

  void init(Monitor_Base * mon) {
    monitor = mon;
    // initialize a condition variable with default attributes
    pthread_cond_init(ptr_cond_var(), 0);
  }

  ~Condition() {
    int code;
    if ((code=pthread_cond_destroy(ptr_cond_var()))==EBUSY)
      nlog << "Can't destroy condition var" << endl;
    assert (code!=EBUSY);
  }

  pthread_cond_t *ptr_cond_var() { return &cond; }

  void signal() {
    //assert(monitor->is_locked());
    pthread_cond_signal(ptr_cond_var());
  }

  void broadcast() {
    //assert(monitor->is_locked());
    pthread_cond_broadcast(ptr_cond_var());
  }

  void wait() {
//     assert(monitor->locked);

    // all right this makes things kludgey, but needed
    pthread_t old_locking_thread = monitor->locking_thread;
    // mutes the mutex

    pthread_cond_wait(ptr_cond_var(), &monitor->pthread_mutex);
    if (monitor->locked) {
      nlog << "[" << pthread_self() << "] " 
	   << monitor->id << " already locked by thread = "
	   << monitor->locking_thread << endl;
    }

    // restore the thing
    monitor->locked = true;
    monitor->locking_thread = old_locking_thread;
  }

  void timed_wait(const struct timespec _time) {
//     assert(monitor->is_locked());
    struct timespec time = _time;
    pthread_cond_timedwait(ptr_cond_var(), &monitor->pthread_mutex, &time);
  }
private:
  Monitor_Base * monitor;
  pthread_cond_t cond;
}; 

#else

#endif // _MSC_VER

#endif
