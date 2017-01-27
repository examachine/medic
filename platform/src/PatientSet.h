#ifndef Platform_PatientSet_Interface
#define Platform_PatientSet_Interface


#ifdef _MSC_VER

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PatientSet.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CPatientSet recordset

class CPatientSet : public CRecordset
{
 public:
  CPatientSet(CDatabase* pDatabase = NULL);
  DECLARE_DYNAMIC(CPatientSet)

    // Field/Param Data
    //{{AFX_FIELD(CPatientSet, CRecordset)
    CString	m_PPATIENTID;
  CString	m_PSURNAME;
  CString	m_PNAME;
  CString	m_PSEX;
  CTime	m_PDATEOFBIRTH;
  CString	m_PSTATUS;
  CString	m_PNOSTUDY;
  //}}AFX_FIELD


  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPatientSet)
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

typedef CPatientSet PatientSet;

#else

class PatientSet
{
};

#endif // _MSC_VER


#endif
