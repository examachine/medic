//
//
// C++ Interface for module: Monitor
//
// Description: 
//
//
// Author: exa
//
//

#ifndef Monitor_Interface
#define Monitor_Interface

#include "General.hxx"

#include "Critical_Region.hxx"

// A monitored object implementation that uses locks to
// control access to a shared object
// template <class Resource> class Monitored : protected Critical_Region
// {
// public:
//   typedef Monitored<Resource> Self;

//   Monitored()
//     : Critical_Region(false)
//   {
//   }

//   const Resource sel_resource() {
//     enter();
//     Resource res = resource;
//     leave();
//     return res;
//   }

//   void mod_resource(const Resource & res) {
//     enter();
//     resource = res;
//     leave();
//   }

//   void copy_resource(Resource & res) {
//     enter();
//     res = resource;
//     leave();
//   }

  //Reference can't be implemented yet!! We have some design problems
  // in that

//   class Safe_Pointer {
//   public:
//     Safe_Pointer(Self *_owner) : owner(_owner) {
//     }
//     Container & operator *() {
      
//     }
//     Mutex mutex;
//     Self *owner;
//   }

// protected:
//   Resource resource;
// };


#ifndef _MSC_VER

class Condition;

class Monitor_Base : protected Critical_Region
{
public:
  Monitor_Base() : Critical_Region("Monitor") {}
  Monitor_Base(string id) : Critical_Region(id) {}

  friend Condition;
};

#else

#endif // _MSC_VER

#endif
