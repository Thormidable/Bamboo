#ifndef __WTVFILE_H__
#define __WTVFILE_H__

/// This is the virtual file for cFile. It is a virtual representation of the base code for files loaded from a hdd.
class vFile
{

public:
 virtual ~vFile(){};
 /// This will return the filename or file reference of this file.
 virtual char *FileName()=0;

 /// This will load the file from a hdd into memory.
 virtual void Load()=0;

};


#endif
