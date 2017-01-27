//
//
// C++ Interface for module: Shared_Stack
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Shared_Stack_Interface
#define Shared_Stack_Interface

#include "General.hxx"

#ifndef _MSC_VER

template <class T> class Shared_Stack : public Monitor_Base
{
public:
  typedef Shared_Stack<T> Self;

  Shared_Stack(unsigned int _max_length = 524288)
  : max_length(_max_length) {}

  T top() {
    soft_enter();
    T val = stack.top();
    leave();
  }

  void push(const T & x) {
    soft_enter();
    if (stack.size()==max_length) cerr << "Stack full, push waiting"
				       << endl;
    leave();
    if (stack.size()==max_length) full.wait();
    soft_enter();
    stack.push(x);
    //cerr << "Pushed " << x << " into shared queue" << endl;
    leave();
    if (stack.size()==1) empty.signal();    
  }
  
  void pop() {
    soft_enter();
    if (stack.size()==0) cerr << "Stack empty, pop waiting"
			      << endl;
    leave();
    if (stack.size()==0) empty.wait();
    soft_enter();
    //cerr << "Popped" << queue.front() << " from shared queue" << endl;
    stack.pop();
    leave();
    if (stack.size()==max_length-1) full.signal();    
  }

  unsigned int size() {
    soft_enter();
    unsigned int s = stack.size();
    leave();
    return s;
  }

private:
  unsigned int max_length;
  Condition full, empty;
  stack<T> stack;
};

#else

#endif // _MSC_VER

#endif
