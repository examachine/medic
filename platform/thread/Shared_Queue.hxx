//
//
// C++ Interface for module: Shared_Queue
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Shared_Queue_Interface
#define Shared_Queue_Interface

#include "General.hxx"

#include "Semaphore.hxx"
#include "Monitor.hxx"
#include "Condition.hxx"

#ifndef _MSC_VER

template <class T> class Shared_Queue : public Monitor_Base
{
public:
  typedef Shared_Queue<T> Self;

  Shared_Queue(unsigned int _max_length = 524288)
    : Monitor_Base("Shared_Queue")
  {
    Critical_Region queue_init("shared queue init", true);
    max_length = _max_length;
    full.init(this);
    empty.init(this);
    sem_barrier.init(0);
    start_flag = true;
    finish_flag = true;
    exit_flag = false;
    nlog << "Shared Queue up " << endl;
  }

//   void start_barrier(int num_working_threads) {
//     // here we must synchonize with all working threads
//     start_flag = true;
//     for (int i = num_working_threads; i>=1; i--) {
//       nlog << "Waiting for " << i << " threads to come in" << endl;
//       sem_barrier.wait();
//     }
//     start_flag = false;
//     nlog << "All threads synchronized at the start of run" << endl;
//   }

//   void finish_barrier(int num_working_threads) {
//     // here we must synchonize with all working threads
//     finish_flag = true;
//     for (int i = num_working_threads; i>=1; i--) {
//       nlog << "Waiting for " << i << " threads to come in" << endl;
//       sem_barrier.wait();
//     }
//     finish_flag = false;
//     nlog << "All threads synchronized at the end of run" << endl;
//   }

//   void barrier_post() {
//     sem_barrier.post();
//   }
  
  void wake_all() {
    soft_enter();
    empty.broadcast();
    leave();
  }

//   void finish_all() {
//     soft_enter();
//     finish_flag = true;
//     empty.broadcast();
//     leave();
//   }

  void terminate_all() {
    soft_enter();
    exit_flag = true;
    empty.broadcast();
    leave();
  }

  T front() {
    soft_enter();
    T val = queue.front();
    leave();
    return val;
  }

  void push(const T & x) {
    soft_enter();
    if (queue.size()==max_length) cerr << "push waiting for item removal"
				       << endl;
    while (queue.size()==max_length)
      full.wait();
//     nlog << "[" << pthread_self() << "] entered push" << endl;
    queue.push(x);
//     cerr << "size: " << queue.size() << " " << pthread_self() << endl;
    //cerr << "Pushed " << x << " into shared queue" << endl;
    if (queue.size()==1)
      nlog << "empty signaled " << pthread_self() << endl;
    if (queue.size()==1) empty.signal();    
    nlog << "Pushed " << pthread_self() << " size " << queue.size()  << endl;
    leave();
  }
  
  T pop() {
    soft_enter();
//     nlog << "[" << pthread_self() << "] entered pop" << endl;
    if (queue.size()==0)
      nlog << "[" << pthread_self()
	   << "] pop waiting for new item (empty signal)" << endl;
    while (queue.size()==0) {
      if (!start_flag) {
	nlog << " Behind start barrier " << pthread_self() << endl;
	leave();
	return T(); // return a default value
      }
      if (!finish_flag) {
	nlog << " Behind finish barrier " << pthread_self() << endl;
	leave();
	return T(); // return a default value
      }
      if (exit_flag) {
	nlog << " Received exit signal " << pthread_self() << endl;
	leave();
	return T(); // return a default value
      }
      empty.wait();
    }
    T val = queue.front();
//     cerr << "Popped" << queue.front() << " from shared queue" << endl
//      << flush;
    assert(queue.size()>0);
    queue.pop();
//     cerr << "size: " << queue.size() << " " << pthread_self() << endl;
    if (queue.size()==max_length-1)
      nlog << "full signaled" << endl;
    if (queue.size()==max_length-1)
      full.signal();
    nlog << "Popped " << pthread_self()
	 << " size " << queue.size() << endl;
    leave();
    return val;
  }

  unsigned int size() {
    soft_enter();
    unsigned int s = queue.size();
    leave();
    return s;
  }

  bool start_flag;
  bool finish_flag;
  bool exit_flag;

private:
  unsigned int max_length;
  Condition full, empty;
  Semaphore sem_barrier;
  queue<T> queue;
};

#else

#endif // _MSC_VER

#endif
