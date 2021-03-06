//
//
// C++ Implementation for module: File
//
// Description: 
//
//
// Author: exa
//
//

#include "File.hxx"

#ifndef _MSC_VER

File::File(string filename, Open_Mode open_mode)
  : CFile(filename.c_str(), CFile::modeRead)
{

}

unsigned int File::get_size()
{
  CFileStatus stat;
  GetStatus(stat);
  return stat.m_size;
}

#else
File::File(string filename, Open_Mode open_mode)
  : CFile(filename.c_str(), CFile::modeRead)
{

}

unsigned int File::get_size()
{
  CFileStatus stat;
  GetStatus(stat);
  return stat.m_size;
}

#endif // MSC_VER
