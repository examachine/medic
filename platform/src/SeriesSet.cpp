// SeriesSet.cpp : implementation file
//

#ifdef __MSC_VER
#include "stdafx.h"
#endif // __MSC_VER
#include "SeriesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesSet

IMPLEMENT_DYNAMIC(CSeriesSet, CRecordset)

CSeriesSet::CSeriesSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSeriesSet)
	m_ESERIESINSTANCEUID = _T("");
	m_ESTUDYINSTANCEUID = _T("");
	m_ENUMBER = _T("");
	m_ETIME = _T("");
	m_ESERIESDESCRIPTION = _T("");
	m_EMODALITY = _T("");
	m_EBODYPART = _T("");
	m_EPATIENTPOSITION = _T("");
	m_ELATERALITY = _T("");
	m_ESTATUS = _T("");
	m_ERADIOLOGIST = _T("");
	m_ESIZE = 0.0;
	m_ECDSERIALNUMBER = _T("");
	m_ENOIMAGES = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSeriesSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=RAGARISDB");
}

CString CSeriesSet::GetDefaultSQL()
{
	return _T("[PC].[SERIES]");
}

void CSeriesSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSeriesSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ESERIESINSTANCEUID]"), m_ESERIESINSTANCEUID);
	RFX_Text(pFX, _T("[ESTUDYINSTANCEUID]"), m_ESTUDYINSTANCEUID);
	RFX_Text(pFX, _T("[ENUMBER]"), m_ENUMBER);
	RFX_Date(pFX, _T("[EDATE]"), m_EDATE);
	RFX_Text(pFX, _T("[ETIME]"), m_ETIME);
	RFX_Text(pFX, _T("[ESERIESDESCRIPTION]"), m_ESERIESDESCRIPTION);
	RFX_Text(pFX, _T("[EMODALITY]"), m_EMODALITY);
	RFX_Text(pFX, _T("[EBODYPART]"), m_EBODYPART);
	RFX_Text(pFX, _T("[EPATIENTPOSITION]"), m_EPATIENTPOSITION);
	RFX_Text(pFX, _T("[ELATERALITY]"), m_ELATERALITY);
	RFX_Text(pFX, _T("[ESTATUS]"), m_ESTATUS);
	RFX_Text(pFX, _T("[ERADIOLOGIST]"), m_ERADIOLOGIST);
	RFX_Double(pFX, _T("[ESIZE]"), m_ESIZE);
	RFX_Text(pFX, _T("[ECDSERIALNUMBER]"), m_ECDSERIALNUMBER);
	RFX_Int(pFX, _T("[ENOIMAGES]"), m_ENOIMAGES);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSeriesSet diagnostics

#ifdef _DEBUG
void CSeriesSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSeriesSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
