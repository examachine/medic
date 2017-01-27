/*
** Implementation file for module
**
**
**
** exa
**
*/

#include "Tag.hxx"

int operator<(const Tag& lhs, const Tag& rhs) {
  int lhsnum=(lhs.group.number<<16)+lhs.element.number;
  int rhsnum=(rhs.group.number<<16)+rhs.element.number;
  return (lhsnum < rhsnum);
}

