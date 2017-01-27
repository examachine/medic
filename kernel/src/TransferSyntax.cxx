/*
**
** Implementation file for TransferSyntax module
**
**
**
** exa
**
*/

#ifdef _MSC_VER
#include "stdafx.h"
#endif // _MSC_VER

#include "KernelInterface.hxx"

//const UI ImplicitVRLittleEndian::UID = "1.2.840.10008.1.2";

string Attribute::toString() const {
	return "[" + tag.toString() + ", " + name + ", " + vr + ", " + vm.toString()
							  + ", " + (int)sequence + "]";
}

void TransferSyntax::dgn(string &s)
{
	dicom_app.report( "TransferSyntax:" + s );
}
