/*
**
** Implementation file for SOP module
**
**
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif

#include "KernelInterface.hxx"
#include "SOPClasses.hxx"

void Null_IOD::set(Null_IOD& a)
{}
template<class TS> void Null_IOD::Coder<TS>::decode(DStream& ds, Null_IOD& obj)
{}
template<class TS> void Null_IOD::Coder<TS>::encode(DStream& ds, Null_IOD& obj)
{}
template class Null_IOD::Coder<ImplicitVRLittleEndian>;
template class Null_IOD::Coder<ExplicitVRLittleEndian>;
template class Null_IOD::Coder<ExplicitVRBigEndian>;
template class Null_IOD::Coder<JPEGBaseLineP1>;
template class Null_IOD::Coder<JPEGExtendedP4>;
template class Null_IOD::Coder<JPEGLosslessNHFOP14>;

// CODE: A better SOP class

// Verification
const UI VerificationSOPClass::Base::UID("1.2.840.10008.1.1");
VerificationSOPClass VerificationSOPClass::Representative(true);

// CRImageStorage
const UI CRImageStorage::Base::UID("1.2.840.10008.5.1.4.1.1.1");
CRImageStorage CRImageStorage::Representative(true);

// CTImageStorage
const UI CTImageStorage::Base::UID("1.2.840.10008.5.1.4.1.1.2");
CTImageStorage CTImageStorage::Representative(true);

// SCImageStorage
const UI SecondaryCaptureImageStorage::Base::UID("1.2.840.10008.5.1.4.1.1.7");
SecondaryCaptureImageStorage SecondaryCaptureImageStorage::Representative(true);

// MRImageStorage
const UI MRImageStorage::Base::UID("1.2.840.10008.5.1.4.1.1.8");
MRImageStorage MRImageStorage::Representative(true);

// XRayAngiographic ImageStorage
const UI XRayAngiographicImageStorage::Base::UID("1.2.840.10008.5.1.4.1.1.12.1");
XRayAngiographicImageStorage XRayAngiographicImageStorage::Representative(true);

// MediaStorageDirectoryStorage
const UI MediaStorageDirectoryStorage::Base::UID("1.2.840.10008.1.3.10");
MediaStorageDirectoryStorage MediaStorageDirectoryStorage::Representative(true);

const UI BasicFilmSessionSOPClass::Base::UID("1.2.840.10008.5.1.1.1");
BasicFilmSessionSOPClass BasicFilmSessionSOPClass::Representative(true);

const UI BasicFilmBoxSOPClass::Base::UID("1.2.840.10008.5.1.1.2");
BasicFilmBoxSOPClass BasicFilmBoxSOPClass::Representative(true);

const UI BasicGrayscaleImageBoxSOPClass::Base::UID("1.2.840.10008.5.1.1.4");
BasicGrayscaleImageBoxSOPClass BasicGrayscaleImageBoxSOPClass::Representative(true);

const UI BasicColorImageBoxSOPClass::Base::UID("1.2.840.10008.5.1.1.4.1");
BasicColorImageBoxSOPClass BasicColorImageBoxSOPClass::Representative(true);

const UI PatientRootQRInfoModelFIND::UID("1.2.840.10008.5.1.4.1.2.1.1");
PatientRootQRInfoModelFIND PatientRootQRInfoModelFIND::Representative(true);

const UI PatientRootQRInfoModelGET::UID("1.2.840.10008.5.1.4.1.2.1.1");
PatientRootQRInfoModelGET PatientRootQRInfoModelGET::Representative(true);

const UI PatientRootQRInfoModelMOVE::UID("1.2.840.10008.5.1.4.1.2.1.1");
PatientRootQRInfoModelMOVE PatientRootQRInfoModelMOVE::Representative(true);

/*
UI StudyRootQRInfoModel::UID("1.2.840.10008.5.1.4.1.2.1.1");
StudyRootQRInfoModel StudyRootQRInfoModel::Representative(true);

UI PatientStudyOnlyQRInfoModel::UID("1.2.840.10008.5.1.4.1.2.1.1");
PatientStudyOnlyQRInfoModel PatientStudyOnlyQRInfoModel::Representative(true);
*/

// Patient Management
const UI PatientManagement::Base::UID("1.4.4");
PatientManagement PatientManagement::Representative(true);

//const UI StudyManagement::Base::UID("1.4.5");
//StudyManagement StudyManagement::Representative(true);

//const UI StudyComponentManagement::Base::UID("1.4.6");
//StudyComponentManagement StudyComponentManagement::Representative(true);

//const UI ResultsManagement::Base::UID("1.4.7");
//ResultsManagement ResultsManagement::Representative(true);

// Register SOP Classes
void SOPs::init_class()
{
  SOPs& self = *this;

  self[VerificationSOPClass::UID] = & VerificationSOPClass::Representative;
  VerificationSOPClass::sop_tss.init_class();

  self[CRImageStorage::UID] = & CRImageStorage::Representative;
  CRImageStorage::sop_tss.init_class();

  self[CTImageStorage::UID] = & CTImageStorage::Representative;
  CTImageStorage::sop_tss.init_class();

  self[SecondaryCaptureImageStorage::UID] = & SecondaryCaptureImageStorage::Representative;
  SecondaryCaptureImageStorage::sop_tss.init_class();

  self[MRImageStorage::UID] = & MRImageStorage::Representative;
  MRImageStorage::sop_tss.init_class();

  self[XRayAngiographicImageStorage::UID] = & XRayAngiographicImageStorage::Representative;
  XRayAngiographicImageStorage::sop_tss.init_class();

  self[MediaStorageDirectoryStorage::UID] = & MediaStorageDirectoryStorage::Representative;
  MediaStorageDirectoryStorage::sop_tss.init_class();

  self[BasicFilmSessionSOPClass::UID] = & BasicFilmSessionSOPClass::Representative;
  BasicFilmSessionSOPClass::sop_tss.init_class();

  self[BasicFilmBoxSOPClass::UID] = & BasicFilmBoxSOPClass::Representative;
  BasicFilmBoxSOPClass::sop_tss.init_class();

  self[BasicGrayscaleImageBoxSOPClass::UID] = & BasicGrayscaleImageBoxSOPClass::Representative;
  BasicGrayscaleImageBoxSOPClass::sop_tss.init_class();

  self[BasicColorImageBoxSOPClass::UID] = & BasicColorImageBoxSOPClass::Representative;
  BasicColorImageBoxSOPClass::sop_tss.init_class();

  self[PatientRootQRInfoModelFIND::UID] = & PatientRootQRInfoModelFIND::Representative;
  PatientRootQRInfoModelFIND::sop_tss.init_class();

  self[PatientRootQRInfoModelGET::UID] = & PatientRootQRInfoModelGET::Representative;
  PatientRootQRInfoModelGET::sop_tss.init_class();

  self[PatientRootQRInfoModelMOVE::UID] = & PatientRootQRInfoModelMOVE::Representative;
  PatientRootQRInfoModelMOVE::sop_tss.init_class();

  /*
    self[StudyRootQRInfoModel::UID] = & StudyRootQRInfoModel::Representative;
    StudyRootQRInfoModel::sop_tss.init_class();

    self[PatientStudyOnlyQRInfoModel::UID] = & PatientStudyOnlyQRInfoModel::Representative;
    PatientStudyOnlyQRInfoModel::sop_tss.init_class();
  */
  //self[PatientManagement::UID] = & PatientManagement::Representative;
  //PatientManagement::sop_tss.init_class();

  //self[StudyManagement::UID] = & StudyManagement::Representative;
  //StudyManagement::sop_tss.init_class();

  //self[StudyComponentManagement::UID] = & StudyComponentManagement::Representative;
  //StudyComponentManagement::sop_tss.init_class();

  //self[ResultsManagement::UID] = & ResultsManagement::Representative;
  //ResultsManagement::sop_tss.init_class();

}
