# Microsoft Developer Studio Project File - Name="platform" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=platform - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "platform.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "platform.mak" CFG="platform - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "platform - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "platform - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "platform - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(medic)" /I "$(medic)/vc6/platform" /I "$(medic)/platform/src" /I "$(medic)/utility" /I "$(medic)/platform/thread" /I "$(medic)/platform/filesystem" /I "$(medic)/kernel/src" /I "$(medic)/classgen/autogen" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "$(medic)/platform/src" /i "$(medic)/platform/res" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# SUBTRACT LIB32 /nologo

!ELSEIF  "$(CFG)" == "platform - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(medic)" /I "$(medic)/vc6/platform" /I "$(medic)/platform/src" /I "$(medic)/utility" /I "$(medic)/platform/thread" /I "$(medic)/platform/filesystem" /I "$(medic)/kernel/src" /I "$(medic)/classgen/autogen" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"StdAfx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "$(medic)/platform/src" /i "$(medic)/platform/res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# SUBTRACT LIB32 /nologo

!ENDIF 

# Begin Target

# Name "platform - Win32 Release"
# Name "platform - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Archive Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\platform\src\ImageSet.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\Message1.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\PatientSet.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\SeriesSet.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\StudySet.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "FileSystem Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\platform\filesystem\File.cxx
# End Source File
# End Group
# Begin Group "Thread Impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\platform\thread\Test.cxx
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\platform\src\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\CustomSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\DicomConsoleDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ListenerSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ListenerThread.cpp
# End Source File
# Begin Source File

SOURCE="..\..\platform\res\MEDIC Resources.rc"
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ServerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Archive Intf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\platform\src\ImageSet.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\Message1.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\PatientSet.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\SeriesSet.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\StudySet.h
# End Source File
# End Group
# Begin Group "FileSystem Intf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\platform\filesystem\File.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\File_System
# End Source File
# End Group
# Begin Group "Thread Intf"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\platform\thread\ANSI_Library.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Barrier.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Condition.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Critical_Region.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\General.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Monitor.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Mutex.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Semaphore.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Shared_List.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Shared_Queue.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Shared_Stack.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Test.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Thread
# End Source File
# Begin Source File

SOURCE=..\..\platform\thread\Thread.hxx
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\platform\src\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\CustomSocket.h
# End Source File
# Begin Source File

SOURCE="..\..\platform\src\dcl application.h"
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\DCL.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\DicomConsoleDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ListenerSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ListenerThread.h
# End Source File
# Begin Source File

SOURCE="..\..\platform\res\MEDIC Resources.h"
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\Medic.hxx
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\ServerThread.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\Socket.hxx
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\platform\src\Time.hxx
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
