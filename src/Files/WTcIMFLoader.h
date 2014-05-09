#ifndef __WTCIMFLOADER_H__
#define __WTCIMFLOADER_H__

class cIMFLoader
{
public:
  void LoadIMF(ifstream &FileStream);
};

/// This basically holds functions for loading IMF files.
namespace cIMF
{
 /// This is the function which will load an IMF file from memory.
 void LoadIMF(const char *lpPath);

};

#endif
