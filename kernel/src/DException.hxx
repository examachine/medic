/*
** Interface file for DException module
**
** Dicom Exceptions
**
** exa
**
*/

#ifndef DException_Interface
#define DException_Interface 1

#include "General.hxx"
#include "Tag.hxx"

class DException {
public:
  DException() {}
  DException(char *s) : reason(s) {}
  DException(string s) : reason(s) {}
  void why();
public:
  string reason; // brief explanation for exception
};


class DTagMismatch : public DException {
public:
  DTagMismatch(Tag t) : DException(string("Tag ") + t.toString() + " not expected") {}
};

class DStreamReadException : public DException {
public:
  DStreamReadException() : DException("DStream Read Error") {}
  DStreamReadException(string s) : DException("DStream Read Error:" + s) {}
};

class DStreamWriteException : public DException {
public:
  DStreamWriteException() : DException("DStream Write Error") {}
  DStreamWriteException(string s) : DException("DStream Write Error:" + s) {}
};

class DItemEncodingException : public DException {
public:
  DItemEncodingException() : DException("Item Encoding Protocol not met: ") {}
  DItemEncodingException(string s) : DException(string("Item Encoding Protocol not met: ") + s) {}
};

class DDETypeException : public DException {
public:
  DDETypeException() : DException("Data Element Type Protocol not met") {}
};

class DVREncodingException : public DException {
public:
  DVREncodingException() : DException("VR Encoding Protocol not met") {}
  DVREncodingException(string s) : DException(string("VR Encoding Protocol not met:") + s) {}
};

class DPtrException : public DException {
public:
  DPtrException() : DException("Invalid Pointer Dereference") {}
  DPtrException(string s) : DException("Pointer Dereference:" + s) {}
};

#endif