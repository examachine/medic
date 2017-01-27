// Type_Query.hxx: interface for the Type_Query class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPE_QUERY_HXX__488EC3C1_2878_11D5_B823_0080AD0022C2__INCLUDED_)
#define AFX_TYPE_QUERY_HXX__488EC3C1_2878_11D5_B823_0080AD0022C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "General.hxx"

class Type_Query
{
public:
	Type_Query();
	~Type_Query();

         list<DPtr>* query(const UI& class_id);
};

#endif // !defined(AFX_TYPE_QUERY_HXX__488EC3C1_2878_11D5_B823_0080AD0022C2__INCLUDED_)
