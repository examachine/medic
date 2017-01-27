# Microsoft Developer Studio Project File - Name="classgen" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=classgen - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "classgen.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "classgen.mak" CFG="classgen - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "classgen - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "classgen - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "classgen - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Generating MEDIC base classes
PostBuild_Cmds=echo on	echo hiaaaaaaaa
# End Special Build Tool

!ELSEIF  "$(CFG)" == "classgen - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Generating MEDIC base classes
PostBuild_Cmds=echo on	echo hiaaaaaaaa
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "classgen - Win32 Release"
# Name "classgen - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\classgen\Application.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Attribute.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\DataSet.cxx
# End Source File
# Begin Source File

SOURCE="..\..\classgen\dicom-grammar.cxx"
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dicom.cxx

!IF  "$(CFG)" == "classgen - Win32 Release"

# ADD CPP /I "../../classgen"

!ELSEIF  "$(CFG)" == "classgen - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classgen\IOD.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Message.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Module.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Parser.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Pointer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Tag.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\classgen\ANSI_Library.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Attribute.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\DataSet.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\DataSets.hxx
# End Source File
# Begin Source File

SOURCE="..\..\classgen\dicom-grammar.h"
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dicom.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\General.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Get_Opt.h
# End Source File
# Begin Source File

SOURCE=..\..\classgen\IOD.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Message.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Module.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Parser.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Pointer.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Tag.hxx
# End Source File
# Begin Source File

SOURCE=..\..\classgen\Utility.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "DICOM Dictionaries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\classgen\dictionaries\CIODDict.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\MESSAGEDict.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\MODDict.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\MODDict2.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\NIODDict.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\Retired.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\TAGDict.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\TAGDict2.txt
# End Source File
# Begin Source File

SOURCE=..\..\classgen\dictionaries\UIDDict.txt
# End Source File
# End Group
# Begin Group "Grammar"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\classgen\dicom-grammar.yxx"

!IF  "$(CFG)" == "classgen - Win32 Release"

USERDEP__DICOM="$(InputDir)/dicom-grammar.yxx"	
# Begin Custom Build - Generating Parser $(InputPath)
InputDir=\Stuff\dev\Acqu\medic\classgen
InputPath="..\..\classgen\dicom-grammar.yxx"

BuildCmds= \
	bison --defines $(InputDir)/dicom-grammar.yxx --output-file=$(InputDir)/dicom-grammar.cxx \
	mv  $(InputDir)/dicom-grammar.cxx.h $(InputDir)/dicom-grammar.h \
	

"$(InputDir)/dicom-grammar.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)/dicom-grammar.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "classgen - Win32 Debug"

USERDEP__DICOM="$(InputDir)/dicom-grammar.yxx"	
# Begin Custom Build - Generating Parser $(InputPath)
InputDir=\Stuff\dev\Acqu\medic\classgen
InputPath="..\..\classgen\dicom-grammar.yxx"

BuildCmds= \
	bison --defines $(InputDir)/dicom-grammar.yxx --output-file=$(InputDir)/dicom-grammar.cxx \
	mv  $(InputDir)/dicom-grammar.cxx.h $(InputDir)/dicom-grammar.h \
	

"$(InputDir)/dicom-grammar.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)/dicom-grammar.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classgen\dicom.lxx

!IF  "$(CFG)" == "classgen - Win32 Release"

USERDEP__DICOM_="$(InputDir)/dicom.lxx"	
# Begin Custom Build - Generating Scanner $(InputPath)
InputDir=\Stuff\dev\Acqu\medic\classgen
InputPath=..\..\classgen\dicom.lxx

"$(InputDir)/dicom.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -o$(InputDir)/dicom.cxx  $(InputDir)/dicom.lxx

# End Custom Build

!ELSEIF  "$(CFG)" == "classgen - Win32 Debug"

USERDEP__DICOM_="$(InputDir)/dicom.lxx"	
# Begin Custom Build - Generating Scanner $(InputPath)
InputDir=\Stuff\dev\Acqu\medic\classgen
InputPath=..\..\classgen\dicom.lxx

"$(InputDir)/dicom.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex -o$(InputDir)/dicom.cxx  $(InputDir)/dicom.lxx

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Scripts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\generate-classes.BAT"
# End Source File
# Begin Source File

SOURCE=.\MakeParser.bat
# End Source File
# Begin Source File

SOURCE=.\makeparser.sh
# End Source File
# End Group
# End Target
# End Project
