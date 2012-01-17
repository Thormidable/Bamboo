#ifndef __WTCFILEHANDLER_H__
#define __WTCFILEHANDLER_H__

/**
* \brief This is the handler for the file system.
* This handles all files loaded from a hdd. It will give allow processes
* to use files loaded else where, using either the filenames or if loaded from an IMF
* a file reference. The files are stored in the list mpFiles.
*/
class cFileHandler
{
/// This is the list storing all loaded files.
cLinkedList<vFile> *mpFiles;
/// This is a pointer to the current cursor position in the list of files mpFiles.
cLinkedNode<vFile> *mpCursor;
/// This is a pointer to the cFileHandler instance. By using Instance() there can only be one...cFileHandler.
static cFileHandler *mpInstance;

cFileHandler();

public:
/// This will return a pointer to the current cFileHandler. If there is no current instance it will create one and return the pointer.
static cFileHandler *Instance();
~cFileHandler();
/// This will reload all the files from a hdd into memory. (Note this is not currently complete).
void Reload();
/// This will remove all the files from memory. (Note this is not currently complete).
void Unload();

/// This will return a pointer to a file with the filename or file refernce lpFilename.
template<class cX> cX *File(const char *lpFilename);

/// This will add the file pointed to by lpNew to the current file list mpFile.
cLinkedNode<vFile> *Add(vFile *lpNew);
/// This will delete the file owned by lpNode from the file list mpFile.
void Delete(cLinkedNode<vFile> *lpNode);

};

template<class cX> cX *cFileHandler::File(const char *lpFilename)
{
	if(mpFiles)
	{
	mpCursor=mpFiles->Start();
	while(mpCursor)
	{
		if (dynamic_cast<cX*>(mpCursor->Data()) && !strcmp(mpCursor->Data()->FileName(),lpFilename)) return dynamic_cast<cX*>(mpCursor->Data());
		mpCursor=mpCursor->Next();
	}
	trace("IMF object " << lpFilename << " not found in memory.");
	}
	return 0;
}

#endif
