#ifndef Platform_StudySet_Interface
#define Platform_StudySet_Interface

#ifdef _MSC_VER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StudySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStudySet recordset

class CStudySet : public CRecordset
{
 public:
  CStudySet(CDatabase* pDatabase = NULL);
  DECLARE_DYNAMIC(CStudySet)

    // Field/Param Data
    //{{AFX_FIELD(CStudySet, CRecordset)
    CString	m_TSTUDYINSTANCEUID;
  CString	m_TPATIENTID;
  CString	m_TSTUDYID;
  CString	m_TNUMBER;
  CTime	m_TDATE;
  CString	m_TTIME;
  CString	m_TSTUDYDESCRIPTION;
  CString	m_TACCESSIONNUMBER;
  CString	m_TREFERRINGPHYSICIAN;
  CString	m_TNOSERIES;
  //}}AFX_FIELD


  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CStudySet)
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

typedef CStudySet StudySet;

#else

class StudySet
{
};

#endif // _MSC_VER

#endif
