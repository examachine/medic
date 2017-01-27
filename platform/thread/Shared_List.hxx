//
//
// C++ Interface for module: Shared_List
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Shared_List_Interface
#define Shared_List_Interface

#include "General.hxx"

#ifndef _MSC_VER

template <class T> class Shared_List : public Monitor_Base
{
public:
  typedef Shared_List<T> Self;
  typedef list<T>::iterator Pos;

  Shared_List() {}

  Pos add(const T & x) {
    soft_enter();
    list.push_back(x);
    Pos pos = list.end()-1;
    leave();
    return pos;
  }
  
  void remove(Pos & pos) {
    soft_enter();
    list.remove(pos);
    leave();
  }

  const T sel(Pos & pos) {
    soft_enter();
    T val = *pos;
    leave();
    return val;
  }

  void mod(Pos & pos, const T & x) {
    soft_enter();
    *pos = x;
    leave();
  }

  unsigned int size() {
    soft_enter();
    unsigned int s = list.size();
    leave();
    return s;
  }

private:
  list<T> list;
};

#else

#endif // _MSC_VER

#endif
