/*
** Interface file for a TS module
**
**
**
** exa
**
*/

#ifndef ExplicitVRLittleEndian_Interface
#define ExplicitVRLittleEndian_Interface 1

#include "General.hxx"
#include "TransferSyntax.hxx"
#include "ExplicitVRLittleEndianBase.hxx"

// Dicom default Transfer Syntax
// Explicit VR Little Endian Transfer Syntax
class ExplicitVRLittleEndian : public ExplicitVRLittleEndianBase {
public:
  ExplicitVRLittleEndian() {}

  static const UI UID;

};


#endif
