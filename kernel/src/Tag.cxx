/*
**
** Implementation file for Tag module
**
** Attribute Tag
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif

//#include "Tag.hxx"
#include "KernelInterface.hxx"

string Tag::toString() const
{
  return '(' + short_to_hexstr(group) + ',' + short_to_hexstr(element) + ')';
}
