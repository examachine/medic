#ifndef _DIALOG_QUERY
#define _DIALOG_QUERY
#include "KernelInterface.hxx"
#include "SOPClasses.hxx"
#include "CFindQuery.hxx"

#ifdef _MSC_VER
#include <afxdb.h>
#endif // _MSC_VER

#include "HierarchicalQuery.hxx"

class Dialog_Query:public CFind_Query{
};

#endif
