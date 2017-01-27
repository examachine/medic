/*
** Interface file for DCL Kernel
**
** Required for a DICOM Application Entity 
**
** exa
**
*/

#ifndef KernelInterface
#define KernelInterface

#ifdef _MSC_VER
#include "StdAfx.h"
#include "platform/res/MEDIC Resources.h"
#endif // _MSC_VER

#include "General.hxx"

#include "KernelAutoGenInterface.hxx"

#include "TS_Dispatcher.hxx"

#include "DException.hxx"
#include "DBinaryFileStream.hxx"
//#include "StorageManager.hxx"

#include "DImageStacker.hxx"
#include "DApplication.hxx"
#include "DContext.hxx"
#include "DFileContext.hxx"
#include "DStreamBuffer.hxx"
#include "BufferTypes.hxx"
#include "PDU.hxx"
#include "DTCPContext.hxx"
#include "DTCPStream.hxx"
#include "TCP_PDATA.hxx"
#include "Dicom_Dir.hxx"

#include "query/query.hxx"

#include "PrintManagement.hxx"

#endif
