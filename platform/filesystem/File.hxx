//
//
// C++ Interface for module: File
//
// Description: 
//
//
// Author: exa
//
//

#ifndef File_Interface
#define File_Interface

#include "General.hxx"

#ifndef _MSC_VER

class File
{
public:
  enum Open_Mode {
    read, write, append
  };

  File(string filename, Open_Mode open_mode = read) {} 

  unsigned int get_size();
};

#else

#include <afx.h>

class File
  : private CFile
{
public:

  enum Open_Mode {
    read, write, append
  };

  File(string filename, Open_Mode open_mode = read);

  unsigned int get_size();
};

#endif // _MSC_VER


#endif
