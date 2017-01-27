// ImageSet.cpp : implementation file
//

#ifdef __MSC_VER
#include "stdafx.h"
#endif // __MSC_VER

#include "ImageSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageSet

IMPLEMENT_DYNAMIC(CImageSet, CRecordset)

CImageSet::CImageSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CImageSet)
	m_ISOPINSTANCEUID = _T("");
	m_ISERIESINSTANCEUID = _T("");
	m_INUMBER = 0;
	m_ITIME = _T("");
	m_IPATIENTORIENTATION = _T("");
	m_ISIZE = 0.0;
	m_ISTAFILENAME = _T("");
	m_ILTAFILENAME = _T("");
	m_IOVERLAY = _T("");
	m_IFOSSIL = _T("");
	m_IKEY = _T("");
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CImageSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=RAGARISDB");
}

CString CImageSet::GetDefaultSQL()
{
	return _T("[PC].[IMAGE]");
}

void CImageSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CImageSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ISOPINSTANCEUID]"), m_ISOPINSTANCEUID);
	RFX_Text(pFX, _T("[ISERIESINSTANCEUID]"), m_ISERIESINSTANCEUID);
	RFX_Int(pFX, _T("[INUMBER]"), m_INUMBER);
	RFX_Date(pFX, _T("[IDATE]"), m_IDATE);
	RFX_Text(pFX, _T("[ITIME]"), m_ITIME);
	RFX_Text(pFX, _T("[IPATIENTORIENTATION]"), m_IPATIENTORIENTATION);
	RFX_Double(pFX, _T("[ISIZE]"), m_ISIZE);
	RFX_Text(pFX, _T("[ISTAFILENAME]"), m_ISTAFILENAME);
	RFX_Text(pFX, _T("[ILTAFILENAME]"), m_ILTAFILENAME);
	RFX_Text(pFX, _T("[IOVERLAY]"), m_IOVERLAY);
	RFX_Text(pFX, _T("[IFOSSIL]"), m_IFOSSIL);
	RFX_Text(pFX, _T("[IKEY]"), m_IKEY);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CImageSet diagnostics

#ifdef _DEBUG
void CImageSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CImageSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
