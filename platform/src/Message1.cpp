// Message1.cpp: implementation of the CMessage1 class.
//
//////////////////////////////////////////////////////////////////////

#ifdef __MSC_VER
#include "stdafx.h"
#endif // __MSC_VER

#include "Message1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CMessage1::AddPatientInfo(CString PID, CString PSurname, CString PName, CString PSex, CTime m_PDOB)
{
	m_M1Patient.m_PPATIENTID		= PID;
	m_M1Patient.m_PSURNAME			= PSurname;
	m_M1Patient.m_PNAME				= PName;
	m_M1Patient.m_PSEX				= PSex;
	m_M1Patient.m_PDATEOFBIRTH		= m_PDOB;
}

void CMessage1::AddStudyInfo(CString TSIUID, CString TSID, CTime TDate, int TTime, CString TReferringPhysician, CString TDescription, CString TAccessionNumber)
{
	m_M1Study.m_TSTUDYINSTANCEUID	= TSIUID;
	m_M1Study.m_TSTUDYID			= TSID;
	m_M1Study.m_TDATE				= TDate;
	m_M1Study.m_TTIME				= TTime;
	m_M1Study.m_TREFERRINGPHYSICIAN	= TReferringPhysician;
	m_M1Study.m_TDESCRIPTION		= TDescription;
	m_M1Study.m_TACCESSIONNUMBER	= TAccessionNumber;
}

void CMessage1::AddSeriesInfo(CString ESIUID, CString EModality, CTime EDate, int ETime, CString EBodyPart, CString EPatientPosition, CString ELaterality, CString EDescription)
{
	m_M1Series.m_ESERIESINSTANCEUID	= ESIUID;
	m_M1Series.m_EMODALITY			= EModality;
	m_M1Series.m_EDATE				= EDate;
	m_M1Series.m_ETIME				= ETime;
	m_M1Series.m_EBODYPART			= EBodyPart;
	m_M1Series.m_EPATIENTPOSITION   = EPatientPosition;
	m_M1Series.m_ELATERALITY		= ELaterality;
	m_M1Series.m_EDESCRIPTION		= EDescription;
}

void CMessage1::AddImageInfo(CString ISOPIUID, int INo, double ISize, CString ISTAFileName, CTime IDate, int ITime, CString IPatientOrientation)
{
	m_M1Image.m_ISOPINSTANCEUID		= ISOPIUID;
	m_M1Image.m_INUMBER				= INo;
	m_M1Image.m_ISIZE				= ISize;
	m_M1Image.m_ISTAFILENAME		= ISTAFileName;
	m_M1Image.m_IDATE				= IDate;
	m_M1Image.m_ITIME				= ITime;
	m_M1Image.m_IPATIENTORIENTATION = IPatientOrientation;
}
