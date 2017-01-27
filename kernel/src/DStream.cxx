/*
**
** Implementation file for DStream module
**
** Dicom Stream
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif _MSC_VER

#include "KernelInterface.hxx"

void DStream::dgn(string s)
{ dicom_app.report( "DStream: " + s); }
