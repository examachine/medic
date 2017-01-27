// PatientSet.cpp : implementation file
//

#ifdef __MSC_VER
#include "stdafx.h"
#endif // __MSC_VER

#include "PatientSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatientSet

IMPLEMENT_DYNAMIC(CPatientSet, CRecordset)

CPatientSet::CPatientSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPatientSet)
	m_PPATIENTID = _T("");
	m_PSURNAME = _T("");
	m_PNAME = _T("");
	m_PSEX = _T("");
	m_PSTATUS = _T("");
	m_PNOSTUDY = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CPatientSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=RAGARISDB");
}

CString CPatientSet::GetDefaultSQL()
{
	return _T("[PC].[PATIENT]");
}

void CPatientSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPatientSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[PPATIENTID]"), m_PPATIENTID);
	RFX_Text(pFX, _T("[PSURNAME]"), m_PSURNAME);
	RFX_Text(pFX, _T("[PNAME]"), m_PNAME);
	RFX_Text(pFX, _T("[PSEX]"), m_PSEX);
	RFX_Date(pFX, _T("[PDATEOFBIRTH]"), m_PDATEOFBIRTH);
	RFX_Text(pFX, _T("[PSTATUS]"), m_PSTATUS);
	RFX_Text(pFX, _T("[PNOSTUDY]"), m_PNOSTUDY);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPatientSet diagnostics

#ifdef _DEBUG
void CPatientSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPatientSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
