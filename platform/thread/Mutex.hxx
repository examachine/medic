//
//
// C++ Interface for module: Mutex
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Mutex_Interface
#define Mutex_Interface

#include "General.hxx"

#ifndef _MSC_VER

class Condition;

class Monitor_Base;

class Mutex {
public:

  Mutex() : locked(false), locking_thread(0) {
    // create a mutex with default attributes
     pthread_mutex_init(&pthread_mutex, 0);
    // ********** NON PORTABLE *******************
    //pthread_mutexattr_t attr;
    //pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ERRORCHECK_NP); 
    //pthread_mutex_init(&pthread_mutex, &attr);
    // ********** NON PORTABLE *******************
//     pthread_mutex_init = PTHREAD_ERRORCHECK_INITIALIZER_NP;
  }

  Mutex(const string & _id) : id(_id), locked(false) {
    pthread_mutex_init(&pthread_mutex, 0);
    // ********** NON PORTABLE *******************
//     pthread_mutex_init = PTHREAD_ERRORCHECK_INITIALIZER_NP;
  }

  ~Mutex() {
    //destroy mutex

    // have we forgotten to unlock it?
    if (locked && pthread_self()==locking_thread)
      unlock();

    if (pthread_mutex_destroy(&pthread_mutex)!=0) {
      cerr << "[" << pthread_self()<< "] " << id
	   << " error: Can't destroy locked mutex" << endl;
      cerr << "already locked by [" << locking_thread << "]" << endl; 
      cerr << " locked var: " << locked << endl;
    }
  }

  // Say if it is locked
  bool is_locked() const {
    return locked;
  }

  void lock() {
    if (locked) {
      nlog << "Already locked by thread = " << id << locking_thread
	   << endl;
    }
    if (locked && locking_thread==pthread_self()) {
      nlog << "Already locked by same thread = " << id << pthread_self() << endl;
    }
    // It is an error if it has been locked by the same thread before
    assert(! (locked && locking_thread==pthread_self() ) );
//     pthread_mutex_lock(&pthread_mutex);
    // MAY BE NON PORTABLE
    int code;
    if ( (code = pthread_mutex_lock(&pthread_mutex)) != 0 ) {
      cerr << "error: DEADLOCK" << endl;
      throw string("deadlock sucks");
      return;
    }
    else {
      locking_thread = pthread_self();
      locked = true;
    }
//     nlog << "pthread_mutex_lock(..) returned " << code << endl;
    nlog << "[" << pthread_self() << "] " << id
	 << " locked" << endl;
  }

  // If another thread has the lock it just
  // returns false, otherwise acquires the lock
  bool try_lock() {
    assert(! (locked && locking_thread==pthread_self() ) );
    if (pthread_mutex_trylock(&pthread_mutex)!=EBUSY) {
      locked = true;
      locking_thread = pthread_self();
      nlog << "[" << pthread_self()<< "] " << id
	   << " locked" << endl;
      return true;
    }
    else
      return false;
  }

  // 
  void unlock() {
    if ( (!locked) || (locking_thread!=pthread_self())) {
      nerr << "unlock: unsuccessful [" << pthread_self() << "] " << id
	   << endl;
      if (!locked)
	nerr << "Was not locked" << endl;
      else if (locking_thread!=pthread_self())
	nerr << "locking thread was " << locking_thread
	     << " this thread is " << pthread_self() << endl;
    }

    // Assume that the mutex is locked and owned by current thread
    // assert(locked && locking_thread==pthread_self());
    // following is the code for error checking mutexes
//     if (pthread_mutex_unlock(&pthread_mutex) !=0 ) {
//       cerr << "error: [" << pthread_self() << "] " << id
// 	   << "can't unlock mutex" << endl; 
//       cerr << "already locked by [" << locking_thread << "]" << endl;
//       throw string("can't unlock");
//     }
//     else {
//       locked = false;
//       locking_thread = 0;
//     }
    // this is the code for fast mutexes, this is non - portable
    pthread_mutex_unlock(&pthread_mutex);
    locked = false;
    locking_thread = 0;
    nlog << "[" << pthread_self()<< "] " << id
	 << " unlocked" << endl;
  }

  friend Condition;
  friend Monitor_Base;

protected:
  pthread_mutex_t pthread_mutex;
  string id;
  pthread_t locking_thread;
  bool locked;
};

#else

#endif // _MSC_VER

#endif
