
#include <KernelInterface.hxx>
#include "HierarchicalQuery.hxx"

void Hierarchical_Query::fetch(){
//	AfxMessageBox(SQL_str);
	if(hierarchy_level== "IMAGE")
		fetch_image();
	else if (hierarchy_level== "SERIES")
		fetch_series();
	else if (hierarchy_level== "STUDY")
		fetch_study();
	else//patient
		fetch_patient();
};

void Hierarchical_Query::fetch_image(){
	ConnectDB("pc","pc");
	
	CString DataIn;
	CImageSet ImageS(&m_dbRagaris);
	ImageS.m_strFilter = SQL_str;
	if (!ImageS.Open(AFX_DB_USE_DEFAULT_TYPE, NULL, CRecordset::executeDirect | CRecordset::readOnly | CRecordset::noDirtyFieldCheck | CRecordset::skipDeletedRecords))
	{
		AfxMessageBox("Can't open Image Set");
	}
	
	if (ImageS.IsBOF())
	{
		AfxMessageBox("EMPTY SET!");
	}
	else
	{
		ImageS.MoveFirst();
		while (!ImageS.IsEOF())
		{
			try {
				Image_Info & info = *image_info_list.insert(image_info_list.end());
				info.sop_instance_uid = (LPCTSTR)ImageS.m_ISOPINSTANCEUID;
				info.image_number = ImageS.m_INUMBER;
			}
			catch (DException EE){
				EE.why();
				throw EE;
			}
			ImageS.MoveNext();
		}
	}
	
	ImageS.Close();	
};

void Hierarchical_Query::fetch_series(){
	ConnectDB("pc","pc");
	
	CString DataIn;
	CSeriesSet SeriesS(&m_dbRagaris);
	SeriesS.m_strFilter = SQL_str;
	if (!SeriesS.Open(AFX_DB_USE_DEFAULT_TYPE, NULL, CRecordset::executeDirect | CRecordset::readOnly | CRecordset::noDirtyFieldCheck | CRecordset::skipDeletedRecords))
	{
		AfxMessageBox("Can't open Series Set");
	}
	
	if (SeriesS.IsBOF())
	{
		AfxMessageBox("EMPTY SET!");
	}
	else
	{
		SeriesS.MoveFirst();
		while (!SeriesS.IsEOF())
		{
			try{
				Series_Info & info = *series_info_list.insert(series_info_list.end());
				info.series_instance_uid = (LPCTSTR)SeriesS.m_ESERIESINSTANCEUID;
				info.modality = (LPCTSTR)SeriesS.m_EMODALITY;
			}
			catch (DException EE){
				EE.why();
				throw EE;
			}
			SeriesS.MoveNext();
		}
	}
	
	SeriesS.Close();
	
};

void Hierarchical_Query::fetch_study(){
	ConnectDB("pc","pc");
	
	CString DataIn;
	CStudySet StudyS(&m_dbRagaris);
	StudyS.m_strFilter = SQL_str;
	if (!StudyS.Open(AFX_DB_USE_DEFAULT_TYPE, NULL, CRecordset::executeDirect | CRecordset::readOnly | CRecordset::noDirtyFieldCheck | CRecordset::skipDeletedRecords))
	{
		AfxMessageBox("Can't open Study Set");
	}
	
	if (StudyS.IsBOF())
	{
		AfxMessageBox("EMPTY SET!");
	}
	else
	{
		StudyS.MoveFirst();
		while (!StudyS.IsEOF())
		{
			try {
				Study_Info & info = *study_info_list.insert(study_info_list.end());
				info.study_instance_uid = (LPCTSTR)StudyS.m_TSTUDYINSTANCEUID;
				info.study_date = StudyS.m_TDATE;
				info.study_time = (LPCTSTR)StudyS.m_TTIME;
				info.accession_number = (LPCTSTR)StudyS.m_TACCESSIONNUMBER;
				info.study_id = (LPCTSTR)StudyS.m_TSTUDYID;
			}
			catch (DException EE){
				EE.why();
				throw EE;
			}
			StudyS.MoveNext();
		}
	}
	
	StudyS.Close();
	
};

void Hierarchical_Query::fetch_patient(){
	ConnectDB("pc","pc");
	
	CString DataIn;
	CPatientSet PatientS(&m_dbRagaris);
	PatientS.m_strFilter = SQL_str;
//	AfxMessageBox(SQL_str);
	if (!PatientS.Open(AFX_DB_USE_DEFAULT_TYPE, NULL, CRecordset::executeDirect | CRecordset::readOnly | CRecordset::noDirtyFieldCheck | CRecordset::skipDeletedRecords))
	{
		AfxMessageBox("Can't open Patient Set");
	}
	
	if (PatientS.IsBOF())
	{
		AfxMessageBox("EMPTY SET!");
	}
	else
	{
		PatientS.MoveFirst();
		while (!PatientS.IsEOF())
		{
			try{
				Patient_Info & info = *patient_info_list.insert(patient_info_list.end());
				info.patient_id = (LPCTSTR)PatientS.m_PPATIENTID;
				info.patient_name= (LPCTSTR)PatientS.m_PNAME;
				info.patient_surname= (LPCTSTR)PatientS.m_PSURNAME;
			}
			catch (DException EE){
				EE.why();
				throw EE;
			}
			PatientS.MoveNext();
		}
	}
	
	PatientS.Close();
	
};


void Hierarchical_Query::SetSQL(CString InStr){
	SQL_str=InStr;
};



void Hierarchical_Query::SetInfoModel(SOP* identifier){
/*

	SQL_str=PatientRootQuery(dynamic_cast<PatientRootQRInfoModelFIND&>(*identifier));
	else if(identifier.sel_class_id ="1.2.840.10008.5.1.4.1.2.2.1")
		SQL_str=StudyRootQuery(*(identifier.ptr());
		else if(identifier.sel_class_id ="1.2.840.10008.5.1.4.1.2.3.1")
		SQL_str=PatientStudyQuery(*(identifier.ptr());
	*/
};

CString Hierarchical_Query::ListUIDtoStr(CString InString){
	CString OutString;
	int pos,count=0;
	
	OutString.Empty();
	if(InString.IsEmpty())
		return OutString;
	
	while((pos=InString.Find(','))!=-1){
		if (count)
			OutString+=",";
		OutString+="'"+InString.Left(pos)+"'";
		count++;
		InString= InString.Mid(pos+1);
	}	
	
	if (count)
		OutString+=",'"+InString+"'";
	else
		OutString+="'"+InString+"'";
	
	
	return OutString;
};




CString Hierarchical_Query::ListUIDStr(CString Str, CString Field)
{
	
	CString StrSQL;
	StrSQL.Empty();
	if(!Str.IsEmpty()){
//		Str=ListUIDtoStr(Str);
		StrSQL=Field+" IN ("+ Str+ ") ";
	}
	return StrSQL;
	
	
	
};


CString Hierarchical_Query::ListUID(UIv InVector, CString Field)
{
	UIList InList;
	CString StrSQL;
	CString Str;
	//StringVRm returns comma delimited elements for toString().data()
	
	InList= UIList(static_cast<UIList&>(InVector));
	Str.Empty();
	StrSQL.Empty();
	Str= Str + "(" + InList.toString().data()+ ")" ;
	if(Str.GetLength()!=2)
		StrSQL=Field+" in "+ Str+ " ";
	return StrSQL;
};


CString Hierarchical_Query::DateSQL(rangeDA InDate, CString Field){
	CString SQLStr;
	CString Date1, Date2;
	if (InDate.selType()!=2)//prior
		Date1= InDate.selStarting().toString().data();
	else 
		Date1.Empty();
	
	if (InDate.selType()!=3)//subsequent
		Date2= InDate.selEnding().toString().data();
	else 
		Date2.Empty();
	
	SQLStr.Empty();
	rangeDA::DA_Type Datetype=InDate.selType();
	switch (Datetype){
	case 0://single
		SQLStr=	Field+"= '"+ Date1+ "'";
		break;
	case 3://subsequent
		SQLStr=	Field+">= '"+ Date1+ "'";
		break;
	case 2://prior
		SQLStr=	Field+"<= '"+ Date2+ "'";
		break;
	case 1://range
		SQLStr=	Field+" BETWEEN '"+ Date1+ "' AND '"+Date2+"'";
		break;
	}
	return SQLStr;
};


CString Hierarchical_Query::TimeSQLStr(CString Time1,CString Time2, CString Field){
	CString SQLStr;
	int TimeType=0;
	
	SQLStr.Empty();
	
	if(Time1.IsEmpty())
		TimeType=0;
	else 
		TimeType=1;
	if(Time2.IsEmpty())
		TimeType+=0;
	else if (Time2=="-")
		TimeType+=2;
	else
		TimeType+=4;
	
	
	switch (TimeType){
	case 1://single
		SQLStr=	Field+"= '"+ Time1+ "'";
		break;
	case 3://subsequent
		SQLStr=	Field+">= '"+ Time1+ "'";
		break;
	case 4://prior
		SQLStr=	Field+"<= '"+ Time2+ "'";
		break;
	case 5://range
		SQLStr=	Field+" BETWEEN '"+ Time1+ "' AND '"+Time2+"'";
		break;
	}
	return SQLStr;
};

void Hierarchical_Query::DateToStr(rangeDA InDate, CString *Date1, CString *Date2){
	if (InDate.selType()!=2)//prior
		*Date1= InDate.selStarting().toString().data();
	else 
		*Date1="-";
	
	(*Date2).Empty();
	if (InDate.selType()!=3){//subsequent
		if(InDate.selType()!=0)
			(*Date2)= InDate.selEnding().toString().data();
	}
	else 
		*Date2="-";
};

void Hierarchical_Query::TimeToStr(rangeTM InTime, CString *Time1, CString *Time2){
	if (InTime.selType()!=2)//prior
		*Time1= InTime.selStarting().toString().data();
	else 
		*Time1="-";
	
	(*Time2).Empty();
	if (InTime.selType()!=3){//subsequent
		if(InTime.selType()!=0)
			(*Time2)= InTime.selEnding().toString().data();
	}
	else 
		*Time2="-";
};


CString Hierarchical_Query::DateSQLStr(CString Date1,CString Date2, CString Field){
	CString SQLStr;
	int DateType=0;
	
	SQLStr.Empty();
	
	if((Date1.IsEmpty()) ||(Date1=="-"))
		DateType=0;
	else{
		DateType=1;
		Date1="TO_DATE('"+Date1+"', 'DD-MON-YYYY') ";
	}
	if(Date2.IsEmpty())
		DateType+=0;
	else if (Date2=="-")
		DateType+=2;
	else{
		DateType+=4;
		Date2="TO_DATE('"+Date2+"', 'DD-MON-YYYY') ";
	}
	
	
	switch (DateType){
	case 1://single
		SQLStr=	Field+"= "+ Date1+ " ";
		break;
	case 3://subsequent
		SQLStr=	Field+">= "+ Date1+ " ";
		break;
	case 4://prior
		SQLStr=	Field+"<= "+ Date2+ " ";
		break;
	case 5://range
		SQLStr=	Field+" BETWEEN "+ Date1+ " AND "+Date2+" ";
		break;
	}
	return SQLStr;
};


CString Hierarchical_Query::TimeSQL(rangeTM InTime, CString Field)
{
	CString SQLStr;
	CString Time1, Time2;
	
	if (InTime.selType()!=2)//prior
		Time1= InTime.selStarting().toString().data();
	else 
		Time1.Empty();
	
	if (InTime.selType()!=3)//subsequent
		Time2= InTime.selEnding().toString().data();
	else 
		Time2.Empty();
	
	SQLStr.Empty();
	rangeTM::TM_Type Timetype=InTime.selType();
	switch (Timetype){
	case 0:
		SQLStr=	Field+ "= '"+ Time1+ "'";
		break;
	case 3:
		SQLStr= Field+ ">= '"+ Time1+ "'";
		break;
	case 2:
		SQLStr= Field+ "<= '"+ Time2+ "'";
		break;
	case 1:
		SQLStr=	Field+ " BETWEEN '"+ Time1+ "' AND '"+Time2+"'";
		break;
	}
	return SQLStr;	
};


CString Hierarchical_Query::SingleSQL(CString InStr, CString Field){
	CString SQLStr;
	SQLStr.Empty();
	if (!InStr.IsEmpty()){
		if(InStr.Find(',')!=-1)
			SQLStr=ListUIDStr(InStr, Field);
		else
			SQLStr+= Field+"='"+InStr+"'";
	}
	return SQLStr;
};

CString Hierarchical_Query::WildSQL(CString InStr, CString Field){
	CString SQLStr;
	SQLStr.Empty();
	if (InStr.IsEmpty())
		return SQLStr;
	int pos;
	BOOLEAN wildcard=FALSE;
	
	pos=InStr.Find('*');
	if(pos!=-1){
		InStr.SetAt(pos,'%');
		wildcard=TRUE;
	}
	
	pos=InStr.Find('?');
	if(pos!=-1){
		InStr.SetAt(pos,'_');
		wildcard=TRUE;
	}
	
	if (wildcard==TRUE)
		SQLStr= Field+" LIKE '"+InStr+"'"+ " ESCAPE ' '";
	else
		SQLStr= Field+"='"+InStr+"'";
	
	return SQLStr;
};



CString Hierarchical_Query::PatientRootQueryStr(CString identifier[]){
	CString PatientSQL;
	CString StudySQL;
	CString SeriesSQL;
	CString ImageSQL;
	
	CString SQLString;
	
	//patient level
	{
		CString PnameSQL;
		CString PfnameSQL;
		CString PIDSQL;
		CString FieldName;
		
		PnameSQL.Empty();
		PfnameSQL.Empty();
		PIDSQL.Empty();
		{	//Patient Name field
			FieldName="PSURNAME";
			PnameSQL=WildSQL(identifier[0], FieldName);
			//	AfxMessageBox(PnameSQL);
			FieldName="PNAME";
			PfnameSQL=WildSQL(identifier[1], FieldName);
			//	AfxMessageBox(PfnameSQL);
		}	//Patient Name field
		
		{//Patient ID field
			FieldName="PPATIENTID";
			PIDSQL=SingleSQL(identifier[2], FieldName);
			//	AfxMessageBox(PIDSQL);
		}
		
		//WHERE clause
		{
			BOOLEAN composite=FALSE;
			PatientSQL.Empty();
			if (!PnameSQL.IsEmpty())
				composite= TRUE;
			PatientSQL+=PnameSQL;
			if(!PfnameSQL.IsEmpty()){
				if (composite==TRUE)
					PatientSQL+= " AND ";
				PatientSQL+=PfnameSQL;
				composite=TRUE;
			}
			if(!PIDSQL.IsEmpty()){
				if (composite==TRUE)
					PatientSQL+= " AND ";
				PatientSQL+=PIDSQL;
			}
		}	
	}//Patient level
	
	//Study level
	{
		CString SDateSQL;
		CString STimeSQL;
		CString ANumberSQL;
		CString SIDSQL;
		CString SUIDSQL;
		
		{//study date field
			SDateSQL=DateSQLStr(identifier[3],identifier[4], "TDATE");
		}//study date field
		
		{//study time field
			STimeSQL= TimeSQLStr(identifier[5], identifier[6], "TTIME");
		}//study time field
		
		{//accession number field
			ANumberSQL=WildSQL(identifier[7],"TACCESSIONNUMBER");
		}//accession number field
		
		{//study ID field
			SIDSQL=WildSQL(identifier[8], "TSTUDYID");
		}//study ID field
		
		{//study instance UID field 
			
			SUIDSQL=ListUIDStr(identifier[9], "TSTUDYINSTANCEUID");
			//StringVRm return comma delimited elements for toString().data()
		}//study instance UID field 
		
		BOOLEAN composite= FALSE;
		if(!SDateSQL.IsEmpty()){
			StudySQL= SDateSQL;
			composite=TRUE;}
		if(!STimeSQL.IsEmpty()){
			if(composite)
				StudySQL+= " AND "+ STimeSQL;
			else
				StudySQL= STimeSQL;
			composite=TRUE;}
		if(!ANumberSQL.IsEmpty()){
			if(composite)
				StudySQL+= " AND "+ ANumberSQL;
			else
				StudySQL= ANumberSQL;
			composite=TRUE;}
		if(!SIDSQL.IsEmpty()){
			if(composite)
				StudySQL+= " AND "+ SIDSQL;
			else
				StudySQL= SIDSQL;
			composite=TRUE;}
		if(!SUIDSQL.IsEmpty()){
			if(composite)
				StudySQL+= " AND "+ SUIDSQL;
			else
				StudySQL= SUIDSQL;
		}
	}//Study level
	
	{//Series Level
		CString ModalitySQL;
		CString SNumberSQL;
		CString SIUIDSQL;
		
		{//Modality field
			ModalitySQL=WildSQL(identifier[10], "EMODALITY");
		}//Modality field
		
		{//Series Number Field
			SNumberSQL=WildSQL(identifier[11], "ENUMBER");
		}//Series Number Field
		
		{//Series Instance UID Field
			SIUIDSQL=ListUIDStr(identifier[12],"ESERIESINSTANCEUID");
		}//Series Instance UID Field
		
		{//Where clause
			BOOLEAN composite= FALSE;
			if(!ModalitySQL.IsEmpty()){
				SeriesSQL= ModalitySQL;
				composite=TRUE;}
			if(!SNumberSQL.IsEmpty()){
				if(composite)
					SeriesSQL+= " AND "+ SNumberSQL;
				else
					SeriesSQL= SNumberSQL;
				composite=TRUE;}
			if(!SIUIDSQL.IsEmpty()){
				if(composite)
					SeriesSQL+= " AND "+ SIUIDSQL;
				else
					SeriesSQL= SIUIDSQL;
			}
		}//where clause
	}//Series level
	
	{//Image Level
		CString INumberSQL;
		CString SOPUIDSQL;
		
		{//image number field
			INumberSQL=WildSQL(identifier[13], "INUMBER");
		}//image number field
		
		{//SOP Instance UID field
			SOPUIDSQL=ListUIDStr(identifier[14], "ISOPINSTANCEUID");
		}//SOP Instance UID field
		
		{//Where clause
			BOOLEAN composite= FALSE;
			if(!INumberSQL.IsEmpty()){
				ImageSQL= INumberSQL;
				composite=TRUE;}
			if(!SOPUIDSQL.IsEmpty()){
				if(composite)
					ImageSQL+= " AND "+ SOPUIDSQL;
				else
					ImageSQL= SOPUIDSQL;
			}
			
		}//where clause
		
	}//Image Level
	
	
	
	
	CString SQLLevel3,SQLLevel2,SQLLevel1;
	
	SQLLevel3.Empty();
	SQLLevel2.Empty();
	SQLLevel1.Empty();
	if (!PatientSQL.IsEmpty())
		SQLLevel1= "TPATIENTID IN(SELECT PPATIENTID FROM PATIENT WHERE "+ PatientSQL+")";
	
	if (!StudySQL.IsEmpty()){
		SQLLevel2= "ESTUDYINSTANCEUID IN(SELECT TSTUDYINSTANCEUID FROM STUDY WHERE "+StudySQL;
		if(!SQLLevel1.IsEmpty())
			SQLLevel2+=" AND "+SQLLevel1+")";
		else
			SQLLevel2+=")";
	}
	else 
		if(!SQLLevel1.IsEmpty())
			SQLLevel2="ESTUDYINSTANCEUID IN(SELECT TSTUDYINSTANCEUID FROM STUDY WHERE "+SQLLevel1+")";
		else
			SQLLevel2.Empty();
		
		if (!SeriesSQL.IsEmpty()){
			SQLLevel3= "ISERIESINSTANCEUID IN(SELECT ESERIESINSTANCEUID FROM SERIES WHERE "+SeriesSQL;
			if(!SQLLevel2.IsEmpty())
				SQLLevel3+=" AND "+SQLLevel2+")";
			else
				SQLLevel3+=")";
		}
		else 
			if(!SQLLevel2.IsEmpty())
				SQLLevel3="ISERIESINSTANCEUID IN(SELECT ESERIESINSTANCEUID FROM SERIES WHERE "+SQLLevel2+")";
			else
				SQLLevel3.Empty();
			
			CString level=identifier[15];
			hierarchy_level=level;
			
			if(level=="PATIENT")
			{
				SQLString=PatientSQL;
			};
			if(level=="STUDY")
			{
				if (!StudySQL.IsEmpty()){
					SQLString=StudySQL;
					if (!SQLLevel1.IsEmpty())
						SQLString+="AND "+SQLLevel1;
				}
				else {
					SQLString.Empty();
					if (!SQLLevel1.IsEmpty())
						SQLString=SQLLevel1;
				}
			};//study
			if(level=="SERIES")
			{
				if(!SeriesSQL.IsEmpty()){
					SQLString=SeriesSQL;
					if (!SQLLevel2.IsEmpty())
						SQLString+="AND "+SQLLevel2;
				}
				else{
					SQLString.Empty();
					if (!SQLLevel2.IsEmpty())
						SQLString=SQLLevel2;
				}
			};//series
			if(level=="IMAGE")
			{
				if(!ImageSQL.IsEmpty()){
					SQLString=ImageSQL;
					if (!SQLLevel3.IsEmpty())
						SQLString+="AND "+SQLLevel3;
				}
				else{
					SQLString.Empty();
					if (!SQLLevel3.IsEmpty())
						SQLString=SQLLevel3;
				}
			};//image
			
			return SQLString;
};


CString Hierarchical_Query::PatientRootQuery(void){
/*
CString query[16];

	if(!(identifier.selPatientsName()).zero_length){
		query[0]=identifier.selPatientsName().selFamilyName().data();
		query[1]=identifier.selPatientsName().selGivenName().data();
	}
	if(!(identifier.selPatientID()).zero_length)
		query[2]=identifier.selPatientID().toString().data();
	if(!(identifier.selStudyDate()).zero_length)
		DateToStr(identifier.selStudyDate (),&(query[3]),&(query[4]));
	if(!(identifier.selStudyTime()).zero_length)
		TimeToStr(identifier.selStudyTime (),&(query[5]),&(query[6]));
	if(!(identifier.selAccessionNumber()).zero_length)
		query[7]=identifier.strAccessionNumber().data();
	if(!(identifier.selStudyID()).zero_length)
		query[8]=identifier.strStudyID().data();
	if(!(identifier.selStudyInstanceUID()).zero_length){
		UIv tempUIv=identifier.selStudyInstanceUID();
		UIList templist= UIList(static_cast<UIList&>(tempUIv));
		query[9]= templist.toString().data();
	}
	if(!(identifier.selModality()).zero_length)
		query[10]=identifier.selModality ().toString().data();
	if(!(identifier.selSeriesNumber ()).zero_length)
		query[11]=identifier.selSeriesNumber ().toString().data();
	if(!(identifier.selSeriesInstanceUID ()).zero_length){
		UIv tempUIv=identifier.selSeriesInstanceUID();
		UIList templist=UIList(static_cast<UIList&>(tempUIv));
		query[12]=templist.toString().data();
	}
	if(!(identifier.selImageNumber()).zero_length)
		query[13]=identifier.strImageNumber().data();
	if(!(identifier.selSOPInstanceUID()).zero_length){
		UIv tempUIv=identifier.selSOPInstanceUID();
		UIList templist=UIList(static_cast<UIList&>(tempUIv));
		query[14]=templist.toString().data();
	}
	if(!(identifier.selQueryRetrieveLevel()).zero_length)
		query[15]=identifier.strQueryRetrieveLevel().data();

	return(PatientRootQueryStr(query));
	*/
	return CString();
};

