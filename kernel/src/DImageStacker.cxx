/*
**
** Implementation file for module
**
**
**
** exa
**
*/

#include "KernelInterface.hxx"
#include "PatientMod.h"
#include "GeneralSeriesMod.h"
#include "GeneralStudyMod.h"
#include "GeneralImageMod.h"

//CODE: message1 I, fin about it...
#define WM_MESSAGE1 WM_USER+0xd01

void DImageStacker::stack(DPtr& ptr)
{
	try {
		SOP& sop = *ptr;
		// let us articulate the data now
		AbstractGeneralSeriesMod & series = dynamic_cast<AbstractGeneralSeriesMod&>(sop);
		AbstractPatientMod & patient =  dynamic_cast<AbstractPatientMod&>(sop);
		AbstractGeneralStudyMod & study =  dynamic_cast<AbstractGeneralStudyMod&>(sop);
		AbstractGeneralImageMod & image =  dynamic_cast<AbstractGeneralImageMod&>(sop);


		// is there such a series?
		const UI & series_uid = series.selSeriesInstanceUID();
			CMessage1* msg = new CMessage1;
			msg->AddPatientInfo( patient.selPatientID()->c_str(),
													 patient.selPatientsName().selFamilyName().c_str(),
													 patient.selPatientsName().selGivenName().c_str(),
													 patient.selPatientsSex()->c_str(),
													 *patient.selPatientsBirthDate()
													 ); 
			const TM & study_time = study.selStudyTime();
			msg->AddStudyInfo( study.selStudyInstanceUID()->c_str(),
												 study.selStudyID()->c_str(),
												 *study.selStudyDate(),
												 study_time.selHour()*10000 +
												 study_time.selMinute()*100 +
												 study_time.selSecond(),
									 			 study.selReferringPhysiciansName()->c_str(),
												 study.selStudyDescription()->c_str(),
												 study.selAccessionNumber()->c_str()
												);
			const TM & series_time = series.selSeriesTime();
			msg->AddSeriesInfo( series.selSeriesInstanceUID()->c_str(),
													series.selModality()->c_str(),
													*series.selSeriesDate(),
													series_time.selHour()*10000 +
													series_time.selMinute()*100 +
													series_time.selSecond(),
													series.selBodyPartExamined()->c_str(),
													series.selPatientPosition()->c_str(),
													series.selLaterality()->c_str(),
													series.selSeriesDescription()->c_str()
													);

		// add the current image
			string filename = dicom_app.sop_filename(ptr.instance_id);
			File file(filename, File::read);
			CString patient_orientation;
			const TM & image_time = image.selImageTime();
			if (image.refPatientOrientation().size() == 0)
				patient_orientation="";
			else
				patient_orientation = image.selPatientOrientation()[0]->c_str();
			msg->AddImageInfo( ptr.instance_id->c_str(),
												 *image.selImageNumber(),
												 file.get_size(),
												 filename.c_str(),													
												 *image.selImageDate(),
												 image_time.selHour()*10000 +
												 image_time.selMinute()*100 +
												 image_time.selSecond(),
												 patient_orientation
												 );
			// dispatch message
			//AfxMessageBox("Sending M1");
			image_manager->PostThreadMessage(WM_MESSAGE1, 0, (long)msg);
	}
	catch (DException e) {
		e.why();
		throw DException("ImageStacker: invalid instance given");
	}

};
