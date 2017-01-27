/*
** Interface file for module
**
**
**
** exa
**
*/

#ifndef Tag_h
#define Tag_h 1

#include "General.hxx"

struct TagGroup {
public:
  TagGroup() {}
  TagGroup(int a,int b) : number(a), x(b) {}
  int number;
  int x;
};

class TagElement {
public:
  TagElement() {}
  TagElement(int a, int b) : number(a), number2(b) {}
  int number;
  int number2;
};

class Tag {
public:
  Tag() {}
  Tag(TagGroup a, TagElement b) : group(a), element(b) {}
  TagGroup group;
  TagElement element;
};

int operator<(const Tag& lhs, const Tag& rhs);

inline ostream & operator <<(ostream& out, const Tag & tag)
{
  out << "Tag(0x" << hex << tag.group.number << ",0x"
      << tag.element.number << ")" << dec;
  return out;
}

class VM {
public:
  VM() {}
  VM (int a, int b, int c) : least(a), most(b), variable(c) {}
  int least, most; // valid if fixed or range
  int variable; // enum 0: fixed, 1: range, 2: 1-n, 3: 2-2n
};

class TagDef {
public:
  TagDef() {}
  TagDef(string b, string c, VM d) :
    name(b), vr(c), vm(d) {}
  string name;
  string vr; // may change? vr's are getting complicated
  VM vm;
};

#endif
