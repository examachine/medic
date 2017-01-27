#ifndef _CFIND_QUERY
#define _CFIND_QUERY
#include "KernelInterface.hxx"
#include "SOPClasses.hxx"

#ifdef _MSC_VER
#include <afxdb.h>
#endif // _MSC_VER

#include "HierarchicalQuery.hxx"

class CFind_Query:public Hierarchical_Query{
public:
	CString PatientRootQuery(PatientRootQRInfoModelFIND&);
	void SetInfoModel(PatientRootQRInfoModelFIND&);

};

#endif
