/*
** Interface file for Tag module
**
**
**
** exa
**
*/

#ifndef Kernel_Tag_h
#define Kernel_Tag_h 1

#include "General.hxx"

class Tag {
public:
  Tag() {}
	Tag(const unsigned short c) : group(c), element(c) {}
  Tag(const unsigned short g, const unsigned short e) : group(g), element(e) {}
  Tag(const int g, const int e)
      : group(static_cast<unsigned short>(g)),
	element(static_cast<unsigned short>(e)) {}
  unsigned short group, element;

  unsigned int number() {
    return (static_cast<unsigned int>(group) << 16) + element; }

  string toString() const;

};

inline bool operator==(Tag lhs, Tag rhs) {
  return (lhs.group==rhs.group) && (lhs.element==rhs.element);
};

inline bool operator <(Tag lhs, Tag rhs) { 
  return lhs.number() < rhs.number();
};
inline bool operator <=(Tag lhs, Tag rhs) { 
  return lhs.number() <= rhs.number();
};
inline bool operator >=(Tag lhs, Tag rhs) { 
  return lhs.number() >= rhs.number();
};
inline bool operator >(Tag lhs, Tag rhs) { 
  return lhs.number() > rhs.number();
};

template<> inline string conv_to_string<Tag>(const Tag t) {
  return "(" + short_to_hexstr(t.group), "," + short_to_hexstr(t.element) + ")";
}


#endif
