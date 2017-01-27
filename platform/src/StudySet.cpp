// StudySet.cpp : implementation file
//

#ifdef __MSC_VER
#include "stdafx.h"
#endif // __MSC_VER

#include "StudySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudySet

IMPLEMENT_DYNAMIC(CStudySet, CRecordset)

CStudySet::CStudySet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CStudySet)
	m_TSTUDYINSTANCEUID = _T("");
	m_TPATIENTID = _T("");
	m_TSTUDYID = _T("");
	m_TNUMBER = _T("");
	m_TTIME = _T("");
	m_TSTUDYDESCRIPTION = _T("");
	m_TACCESSIONNUMBER = _T("");
	m_TREFERRINGPHYSICIAN = _T("");
	m_TNOSERIES = _T("");
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CStudySet::GetDefaultConnect()
{
	return _T("ODBC;DSN=RAGARISDB");
}

CString CStudySet::GetDefaultSQL()
{
	return _T("[PC].[STUDY]");
}

void CStudySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStudySet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[TSTUDYINSTANCEUID]"), m_TSTUDYINSTANCEUID);
	RFX_Text(pFX, _T("[TPATIENTID]"), m_TPATIENTID);
	RFX_Text(pFX, _T("[TSTUDYID]"), m_TSTUDYID);
	RFX_Text(pFX, _T("[TNUMBER]"), m_TNUMBER);
	RFX_Date(pFX, _T("[TDATE]"), m_TDATE);
	RFX_Text(pFX, _T("[TTIME]"), m_TTIME);
	RFX_Text(pFX, _T("[TSTUDYDESCRIPTION]"), m_TSTUDYDESCRIPTION);
	RFX_Text(pFX, _T("[TACCESSIONNUMBER]"), m_TACCESSIONNUMBER);
	RFX_Text(pFX, _T("[TREFERRINGPHYSICIAN]"), m_TREFERRINGPHYSICIAN);
	RFX_Text(pFX, _T("[TNOSERIES]"), m_TNOSERIES);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStudySet diagnostics

#ifdef _DEBUG
void CStudySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStudySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
