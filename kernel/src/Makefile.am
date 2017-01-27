noinst_LIBRARIES = libkernel.a

libkernel_a_SOURCES =  \
 DTCPContext_1.cxx      KernelInterface.cxx \
 DTCPStream.cxx         Negotiator.cxx \
 DApplication.cxx                    PDU.cxx \
 DBinaryFileStream.cxx  Dicom_Dir.cxx           PrintManagement.cxx \
 DContext.cxx           ExplicitVRBigEndian.cxx         SOP.cxx \
 DException.cxx         ExplicitVRLittleEndian.cxx      SeqVR.cxx \
 DFileContext.cxx       ExplicitVRLittleEndianBase.cxx  StorageManager.cxx \
      General.cxx                     TCP_PDATA.cxx \
 DPtr.cxx                          Tag.cxx \
 DStream.cxx            ImplicitVRLittleEndian.cxx      TransferSyntax.cxx \
 DStreamBuffer.cxx      JPEG_TS.cxx                     Utility.cxx \
 DTCPContext_0.cxx      KernelAutoGenInterface.cxx      VR.cxx

## Omitted files
## DImageStacker.cxx CFindQuery.cxx CGetQuery.cxx DialogQuery.cxx
## HierarchicalQuery.cxx

INCLUDES = -I$(top_srcdir)/classgen/autogen \
-I$(top_srcdir)/platform/src -I$(top_srcdir)/utility \
-I$(top_srcdir)/platform/thread -I$(top_srcdir)/platform/filesystem \
-I$(top_srcdir)/platform

