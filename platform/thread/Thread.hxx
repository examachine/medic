//
//
// C++ Interface for module: Thread
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Thread_Interface
#define Thread_Interface

#include "General.hxx"

#include "Semaphore.hxx"


// Thread class, represents a thread of execution
// When created, it automatically spawns off a process
// It is an abstract class which should be derived from

// Since it is called from another thread, its constructor
// destructor are executed in the calling thread, while
// run() method and associated components are contained
// within the newly created thread.
#ifndef _MSC_VER

class Thread {
public:
  const static int magic_num = 0x78652061;

  Thread() : magic(magic_num) {
    // a message in a struct
    thread_init = new Thread_Init(this);
    thread_init->mod_thread(this);
    // We create the thread suspended
    // so that the Thread object is properly initialized
    // before it bursts
    if (pthread_create(&thread_id, 0, &Thread::thread_start,
		       (void*)thread_init)==0) {
      nlog << "[" << sel_thread_id() <<  "] thread spawn" << endl;
    }
    else {
      cerr << "Can't create thread" << endl;
    }
    thread_init->go();
  }  

  ~Thread() {
    magic = 0;
  }

  pthread_t sel_thread_id() const {
    return thread_id;
  }

  // wait for another thread to exit
  static void wait(const Thread & thread) {
    // wait for thread, CODE: handle return value!!
    pthread_join(thread.sel_thread_id(), NULL);
  }

  // send a termination message to another thread
  static void terminate(const Thread & thread) {
    // CODE: handle return value!!
    pthread_cancel(thread.sel_thread_id());
  }

  // send a signal to another thread
  static void kill(const Thread & thread) {
    // CODE: handle return value!!
    pthread_kill(thread.sel_thread_id(), 1);
  }

  // a checkpoint for receiving termination messages
  static void test_terminate() {
    pthread_testcancel();
  }

  static void finish() {
    nlog << "[" << pthread_self()
	 << "] 	Exiting thread" << endl;
    pthread_exit(0);
  }

protected:
  // entry point to the thread
  // exiting this function, or calling exit ends
  // thread execution
  virtual void run() = 0;

  // to be called by thread procedure
  virtual void exit() {
    nlog << "[" << pthread_self()
	 << "] Exiting thread" << endl;
    pthread_exit(0);
  }

private:

  // Code Use the generic Monitored<T> to implement this
  class Thread_Init {
  public:

    Thread_Init(Thread *t)
      : sem(0), thread(t) {
    }

    Thread * sel_thread() {
      sem.wait();
      Thread * t =  thread;
      return t;
    }

     void mod_thread(Thread *t) {
      thread = t;
    }

    void go() {
      sem.post();
    }

  private:
    Semaphore sem;
    Thread *thread;
  };

  Thread_Init *thread_init;
  int magic;
  
  // our custom function which kickstarts the thread
  static void * thread_start(void * arg) {
    nlog << "[" << pthread_self()
 	 << "] thread online" << endl;
    // pass execution to owning thread object
    Thread_Init *t = reinterpret_cast<Thread_Init*>(arg);
    // synchronize
    // spin here, shouldn't take too long
    Thread *thread = t->sel_thread();
    delete t;
    // set our attributes
//     pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,0);
    // run our thread
    assert(thread->magic == magic_num);
    thread->run();
    // thread ends here
    thread->exit();
  }

  // encapsulated thread id
  pthread_t thread_id;
};

#else

#endif // _MSC_VER

#endif
