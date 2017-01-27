# Microsoft Developer Studio Project File - Name="base" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=base - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "base.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "base.mak" CFG="base - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "base - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "base - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "base - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(projdir)\..\kernel\src $(projdir)\..\utility" /I "$(medic)" /I "$(medic)\kernel\src" /I "$(medic)\platform\src" /I "$(medic)\utility" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# SUBTRACT LIB32 /nologo

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(medic)" /I "$(medic)\kernel\src" /I "$(medic)\platform\src" /I "$(medic)\utility" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# SUBTRACT LIB32 /nologo

!ENDIF 

# Begin Target

# Name "base - Win32 Release"
# Name "base - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "IOD Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicAnnotationBoxIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicDirectoryIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmBoxIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmSessionIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicImageBoxIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicStudyDescriptorIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CRImageIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CTImageIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\MRImageIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\PatientIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ResultsIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\SCImageIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\StudyComponentIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\StudyIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\VisitIOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\XRayAngiographicImageIOD.cxx
# End Source File
# End Group
# Begin Group "Module Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicAnnotationPresentationMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmBoxPresentationMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmBoxRelationshipMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmSessionPresentationMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmSessionRelationshipMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CineMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ContrastBolusMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CRImageMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CRSeriesMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CTImageMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CurveMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\DeviceMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\DICOMFileMetaInformationMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\DirectoryInformationMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\DisplayShutterMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\FileSetIdentificationMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\FrameOfReferenceMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\FramePointersMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\GeneralEquipmentMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\GeneralImageMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\GeneralSeriesMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\GeneralStudyMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ImageBoxPixelPresentationMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ImageBoxRelationshipMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ImagePixelMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ImagePlaneMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\MaskMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ModalityLUTMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\MRImageMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\MultiFrameMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\MultiFrameOverlayMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\OverlayPlaneMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\PatientMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\PatientRootQRMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\PatientStudyMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\PatientStudyOnlyQRMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\SCImageEquipmentMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\SCImageMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\SOPCommonMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\StudyRootQRMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\TherapyMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\VOILUTMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\XAPositionerMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\XRayAcquisitionMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\XRayCollimatorMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\XRayImageMod.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\XRayTableMod.cxx
# End Source File
# End Group
# Begin Group "Message Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\classgen\autogen\CCancelFindRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CCancelGetRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CEchoRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CEchoRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CFindRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CFindRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CGetRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CGetRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CMoveRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CMoveRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CStoreRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CStoreRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NActionRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NActionRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NCreateRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NCreateRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NDeleteRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NDeleteRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NGetRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NGetRSPMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NSetRQMsg.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\NSetRSPMsg.cxx
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "IOD Intf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicAnnotationBoxIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicDirectoryIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmBoxIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicFilmSessionIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicImageBoxIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\BasicStudyDescriptorIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CRImageIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\CTImageIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\MRImageIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\PatientIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\ResultsIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\SCImageIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\StudyComponentIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\StudyIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\VisitIOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\XRayAngiographicImageIOD.hxx
# End Source File
# End Group
# Begin Group "Module Intf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\classgen\autogen\AudioMod.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\GeneralImageMod.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\autogen\GeneralStudyMod.hxx
# End Source File
# End Group
# Begin Group "Message Intf"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Scripts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\autogen.BAT

!IF  "$(CFG)" == "base - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\autogen.BAT

"..\..\classgen\autogen\BasicAnnotationBoxIOD.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	autogen Release

# End Custom Build

!ELSEIF  "$(CFG)" == "base - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\autogen.BAT

"..\..\classgen\autogen\BasicAnnotationBoxIOD.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	autogen Debug

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
