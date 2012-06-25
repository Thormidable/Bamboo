#ifndef __WTCFILE_H__
#define __WTCFILE_H__

/**
* \brief This is the base code for files to be loaded from a hdd.
* Any file object loaded from a hddvshould inherit this class.
* It is best used for media files. This code will automatically add
* newly loaded files to cFileHandler. The files can be loaded using the filename
* or if loaded from an IMF file using the reference for each file.
*/
class cFile : public vFile
{
protected:
	~cFile();
public:
       friend class cFileHandler;
	/// This is a pointer to the cLinkedNode which owns this file.
       cLinkedNode<vFile> *mpNode;

	/// This constructor will automatically load the file from memory and add it to the list in cFilehandler.
       cFile();


	/// This will store the files filename.
       char mpFileName[64];

	/// This will return the files filename
       char *FileName();
	/// This is the function that will actually load the file from a hdd.
       void Load();

       void FileName(string lsFileName);

	   void Stop();


protected:
	/// This is a pointer to the cFileHandler which owns this file.
          cFileHandler *mpFileHandler;
};

#endif
