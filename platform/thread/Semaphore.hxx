//
//
// C++ Interface for module: Semaphore
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Semaphore_Interface
#define Semaphore_Interface

#include "General.hxx"

#ifndef _MSC_VER

class Semaphore {
public:
  Semaphore() {}

  Semaphore(unsigned int value, bool shared = false) {
    init(value, shared);
  }

  sem_t* c_sem() {
    return const_cast<sem_t *>(&sem);
  }

  void init(unsigned int value, bool shared = false) {
    int pshared;
    if (shared)
      pshared = 1;
    else
      pshared = 0;
    if (sem_init(c_sem(), pshared, value)!=0)
      cerr << "Can't init sem" << endl;
  }

  ~Semaphore() {
    sem_destroy(c_sem());
  }

  void wait() {
    sem_wait(c_sem());
  }

  bool try_wait() {
    if (sem_trywait(c_sem()))
      return true;
    else
      return false;
  }

  void post() {
    sem_post(c_sem());
  }

  int value() {
    int val;
    sem_getvalue(c_sem(), &val);
    return val;
  }
private:
  volatile sem_t sem;
};

#else

#include <afxmt.h>

class Semaphore : public CSemaphore {
  public:
    Semaphore() {}
};
#endif // _MSC_VER

#endif
