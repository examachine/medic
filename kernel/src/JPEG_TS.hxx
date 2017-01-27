/*
** Interface file for a TS module
**
**
**
** exa
**
*/

#ifndef JPEG_TS_Interface
#define JPEG_TS_Interface 1

#include "General.hxx"
#include "TransferSyntax.hxx"
#include "ExplicitVRLittleEndianBase.hxx"

// Dicom JPEG default Transfer Syntaxes

class JPEGBaseLineP1 : public ExplicitVRLittleEndianBase {
public:
  JPEGBaseLineP1() {}
    
  static const UI UID;
    
};

//const UI JPEGBaseLineP1 = UI("1.2.840.10008.1.2.4.50");

class JPEGExtendedP4 : public ExplicitVRLittleEndianBase {
public:
  JPEGExtendedP4() {}
   
  static const UI UID;
    
};

class JPEGLosslessNHFOP14 : public ExplicitVRLittleEndianBase {
public:
  JPEGLosslessNHFOP14() {}
  
  static const UI UID;

};

/*
JPEGBaseLineP1
JPEGExtendedP4
JPEGLosslessNHFOP14
*/

#endif
