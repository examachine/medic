#ifndef Platform_ImageSet_Interface
#define Platform_ImageSet_Interface

#ifdef _MSC_VER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImageSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageSet recordset

class CImageSet : public CRecordset
{
 public:
  CImageSet(CDatabase* pDatabase = NULL);
  DECLARE_DYNAMIC(CImageSet)

  // Field/Param Data
  //{{AFX_FIELD(CImageSet, CRecordset)
  CString	m_ISOPINSTANCEUID;
  CString	m_ISERIESINSTANCEUID;
  int		m_INUMBER;
  CTime	m_IDATE;
  CString	m_ITIME;
  CString	m_IPATIENTORIENTATION;
  double	m_ISIZE;
  CString	m_ISTAFILENAME;
  CString	m_ILTAFILENAME;
  CString	m_IOVERLAY;
  CString	m_IFOSSIL;
  CString	m_IKEY;
  //}}AFX_FIELD


  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CImageSet)
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

typedef CImageSet ImageSet;

#else

class ImageSet
{
};

#endif // _MSC_VER

#endif
