/*
**
** Implementation file for DException module
**
** Dicom Exceptions
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif

#include "KernelInterface.hxx"

void DException::why()
{
  dicom_app.report( "Exception caught: " + reason );
}
