#ifndef _CGET_QUERY
#define _CGET_QUERY
#include "KernelInterface.hxx"
#include "SOPClasses.hxx"

#ifdef _MSC_VER
#include <afxdb.h>
#endif /* _MSC_VER */

#include "PatientSet.h"
#include "StudySet.h"
#include "SeriesSet.h"
#include "ImageSet.h"

#include "HierarchicalQuery.hxx"

class CGet_Query:public Hierarchical_Query{
public:
	void fetch();
	CString PatientRootQuery(PatientRootQRInfoModelGET & identifier);
	void SetInfoModel(PatientRootQRInfoModelGET &);

};

#endif
