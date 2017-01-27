#include "CGetQuery.hxx"

void CGet_Query::fetch(){
	fetch_image();
}

CString CGet_Query::PatientRootQuery(PatientRootQRInfoModelGET & identifier){

	CString query[16];
	
	if((identifier.avlPatientsName())){
		query[0]=identifier.selPatientsName().selFamilyName().data();
		query[1]=identifier.selPatientsName().selGivenName().data();
	}
	if((identifier.avlPatientID()))
		query[2]=identifier.selPatientID().toString().data();
	if((identifier.avlStudyDate()))
		DateToStr(identifier.selStudyDate (),&(query[3]),&(query[4]));
	if((identifier.avlStudyTime()))
		TimeToStr(identifier.selStudyTime (),&(query[5]),&(query[6]));
	if((identifier.avlAccessionNumber()))
		query[7]=identifier.strAccessionNumber().data();
	if((identifier.avlStudyID()))
		query[8]=identifier.strStudyID().data();
	if((identifier.avlStudyInstanceUID())){
		UIv tempUIv=identifier.selStudyInstanceUID();
		UIList templist= UIList(static_cast<UIList&>(tempUIv));
		query[9]= templist.toString().data();
	}
	if((identifier.avlModality()))
		query[10]=identifier.selModality ().toString().data();
	if((identifier.avlSeriesNumber ()))
		query[11]=identifier.selSeriesNumber ().toString().data();
	if((identifier.avlSeriesInstanceUID ())){
		UIv tempUIv=identifier.selSeriesInstanceUID();
		UIList templist=UIList(static_cast<UIList&>(tempUIv));
		query[12]=templist.toString().data();
	}
	if((identifier.avlImageNumber()))
		query[13]=identifier.strImageNumber().data();
	if((identifier.avlSOPInstanceUID())){
		UIv tempUIv=identifier.selSOPInstanceUID();
		UIList templist=UIList(static_cast<UIList&>(tempUIv));
		query[14]=templist.toString().data();
	}
	if((identifier.avlQueryRetrieveLevel()))
		query[15]=identifier.strQueryRetrieveLevel().data();
	
	return(PatientRootQueryStr(query));
};

void CGet_Query::SetInfoModel(PatientRootQRInfoModelGET & identifier){
	SetSQL(PatientRootQuery(identifier));
};