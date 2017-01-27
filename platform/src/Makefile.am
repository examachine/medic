noinst_LIBRARIES = libkernel.a

libkernel_a_SOURCES =  \
 ClientSocket.cpp     ListenerSocket.cpp  SeriesSet.cpp     StudySet.cpp\
 CustomSocket.cpp     ListenerThread.cpp  ServerSocket.cpp\
 DicomConsoleDlg.cpp  Message1.cpp        ServerThread.cpp\
 ImageSet.cpp         PatientSet.cpp      StdAfx.cpp

INCLUDES = -I$(top_srcdir)/classgen/autogen \
-I$(top_srcdir)/kernel/src -I$(top_srcdir)/utility \
-I$(top_srcdir)/platform/thread -I$(top_srcdir)/platform/filesystem
