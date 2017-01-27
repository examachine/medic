# Microsoft Developer Studio Project File - Name="kernel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=kernel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "kernel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "kernel.mak" CFG="kernel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "kernel - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "kernel - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kernel - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /Gi /GR /GX /O2 /I "." /I "$(medic)" /I "$(medic)/kernel/src" /I "$(medic)/platform/src" /I "$(medic)/utility" /I "$(medic)/classgen/autogen" /I "$(medic)/platform/thread" /I "$(medic)/platform" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /Zm700 /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# SUBTRACT LIB32 /nologo

!ELSEIF  "$(CFG)" == "kernel - Win32 Debug"

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
# ADD CPP /MDd /W3 /Gm /Gi /GR /GX /ZI /Od /I "." /I "$(medic)" /I "$(medic)/kernel/src" /I "$(medic)/platform/src" /I "$(medic)/utility" /I "$(medic)/classgen/autogen" /I "$(medic)/platform/thread" /I "$(medic)/platform" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /Zm700 /c
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

# Name "kernel - Win32 Release"
# Name "kernel - Win32 Debug"
# Begin Group "Implementation"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Archive Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\src\CFindQuery.cxx
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\CGetQuery.cxx
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DialogQuery.cxx
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DImageStacker.cxx
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\HierarchicalQuery.cxx
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\kernel\src\DApplication.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DBinaryFileStream.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DContext.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DException.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DFileContext.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Dicom_Dir.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DPtr.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DStream.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DStreamBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DTCPContext_0.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DTCPContext_1.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DTCPStream.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ExplicitVRBigEndian.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ExplicitVRLittleEndian.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ExplicitVRLittleEndianBase.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\General.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ImplicitVRLittleEndian.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\JPEG_TS.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\KernelAutoGenInterface.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\KernelInterface.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Negotiator.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\PDU.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\PrintManagement.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\SeqVR.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\SOP.cxx
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\StorageManager.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Tag.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\TCP_PDATA.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\TransferSyntax.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Type_Query.cxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\VR.cxx
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Archive Intf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\kernel\src\CFindQuery.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\CGetQuery.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DialogQuery.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DImageStacker.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\HierarchicalQuery.hxx
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\kernel\src\ANSILibrary.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\BufferTypes.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DApplication.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DBinaryFileStream.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DContext.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DException.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DFileContext.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Dicom_Dir.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DPtr.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DStream.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DStreamBuffer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DTCPContext.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\DTCPStream.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ExplicitVRBigEndian.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ExplicitVRLittleEndian.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ExplicitVRLittleEndianBase.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\General.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\ImplicitVRLittleEndian.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\JPEG_TS.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\KernelAutoGenInterface.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\KernelImplementation.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\KernelInterface.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Messages.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Negotiator.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\PDU.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\PrintManagement.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\query\query.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\query\Query_Common.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\SeqVR.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\SOP.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\SOPClasses.hxx
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\StorageManager.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\Tag.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\TCP_PDATA.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\TransferSyntax.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\TransferSyntaxes.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\TS_Dispatcher.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\query\Type_Query.hxx
# End Source File
# Begin Source File

SOURCE=..\..\kernel\src\VR.hxx
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# Begin Source File

SOURCE="..\..\kernel\sop-architecture.txt"
# End Source File
# Begin Source File

SOURCE=..\..\kernel\Todo
# End Source File
# End Target
# End Project
