#ifndef Platform_SeriesSet_Interface
#define Platform_SeriesSet_Interface

#ifdef _MSC_VER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SeriesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeriesSet recordset

class CSeriesSet : public CRecordset
{
public:
	CSeriesSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSeriesSet)

// Field/Param Data
	//{{AFX_FIELD(CSeriesSet, CRecordset)
	CString	m_ESERIESINSTANCEUID;
	CString	m_ESTUDYINSTANCEUID;
	CString	m_ENUMBER;
	CTime	m_EDATE;
	CString	m_ETIME;
	CString	m_ESERIESDESCRIPTION;
	CString	m_EMODALITY;
	CString	m_EBODYPART;
	CString	m_EPATIENTPOSITION;
	CString	m_ELATERALITY;
	CString	m_ESTATUS;
	CString	m_ERADIOLOGIST;
	double	m_ESIZE;
	CString	m_ECDSERIALNUMBER;
	int		m_ENOIMAGES;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

typedef CSeriesSet SeriesSet;

#else

class SeriesSet
{
};

#endif // _MSC_VER

#endif
