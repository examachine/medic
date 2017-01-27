// Message1.h: interface for the CMessage1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE1_H__881FEA81_FB86_11D1_BDBA_002048088FB4__INCLUDED_)
#define AFX_MESSAGE1_H__881FEA81_FB86_11D1_BDBA_002048088FB4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMessage1 : public CObject
{
public:
	void AddStudyInfo(CString TSIUID, CString TSID, CTime TDate, int TTime, CString TReferringPhysician, CString TDescription, CString TAccessionNumber);
	void AddPatientInfo(CString PID, CString PS, CString PN, CString PSex, CTime m_PDOB);
	void AddSeriesInfo(CString ESIUID, CString EModality, CTime EDate, int ETime, CString EBodyPart, CString EPatientPosition, CString ELaterality, CString EDescription);
	void AddImageInfo(CString ISOPIUID, int INo, double ISize, CString ISTAFileName, CTime IDate, int ITime, CString IPatientOrientation);
	CMessage1() {};
	virtual ~CMessage1() {};
	
	struct SPatient
	{
		CString	m_PPATIENTID;
		CString	m_PSURNAME;
		CString	m_PNAME;
		CString	m_PSEX;
		CTime	m_PDATEOFBIRTH;
	};

	struct SStudy
	{
		CString	m_TSTUDYINSTANCEUID;
		CString	m_TSTUDYID;
		CTime	m_TDATE;
		int		m_TTIME;
		CString	m_TREFERRINGPHYSICIAN;
		CString m_TDESCRIPTION;
		CString m_TACCESSIONNUMBER;
	};

	struct SSeries
	{
		CString	m_ESERIESINSTANCEUID;
		CString	m_EMODALITY;
		CTime	m_EDATE;
		int		m_ETIME;
		CString	m_EBODYPART;
		CString m_EPATIENTPOSITION;
		CString	m_ELATERALITY;
		CString m_EDESCRIPTION;
	};

	struct SImage
	{
		CString	m_ISOPINSTANCEUID;
		CTime	m_IDATE;
		int		m_ITIME;
		int		m_INUMBER;
		double	m_ISIZE;
		CString	m_ISTAFILENAME;
		CString m_IPATIENTORIENTATION;
	};


	SPatient	m_M1Patient;
	SStudy		m_M1Study;
	SSeries		m_M1Series;
	SImage		m_M1Image;
};

#endif // !defined(AFX_MESSAGE1_H__881FEA81_FB86_11D1_BDBA_002048088FB4__INCLUDED_)
