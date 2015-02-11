
#include "../WTBamboo.h"

cFileHandler::cFileHandler()
{
	mpFiles=0;
	mpCursor=0;
}



cFileHandler::~cFileHandler()
{
	TRACE("Deleting mpFiles");
	delete mpFiles; mpFiles=0;
	TRACE("mpFiles Deleted");
}

cFileHandler *cFileHandler::mpInstance=0;

cFileHandler *cFileHandler::Instance()
{
	if(!mpInstance) {mpInstance=new cFileHandler; mpInstance->mpFiles=0;}
	return mpInstance;
}

void cFileHandler::Reload(){}

void cFileHandler::Unload(){}

cLinkedNode<vFile> *cFileHandler::Add(vFile *lpNew)
{
	if (!mpFiles) {
		mpFiles=new cLinkedList<vFile>(lpNew);
		return mpFiles->Start();
	}
	return mpFiles->Insert(lpNew);
}

void cFileHandler::Delete(cLinkedNode<vFile> *lpNode)
{
	if(mpFiles) mpFiles->Delete(lpNode);
}


cDirectoryFileList::cDirectoryFileList(string lsDirectoryPath)
{
	mcFileList.Init(5);
	mcDirectoryList.Init(5);
	mcUnknownList.Init(5);

  
  
#ifndef _COMPILED_IN_VS
  struct dirent *entry;
  DIR *dp;

  dp = opendir(lsDirectoryPath.c_str());

  if (dp == NULL) {
    TRACE("Directory does not exist");
    return;
  }

  while((entry = readdir(dp)))
  {
      if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0) continue;
      if(Find(entry->d_name,".")) {mcFileList.Add(new string(entry->d_name)); continue;}
      mcDirectoryList.Add(new string(entry->d_name));
  }

  closedir(dp);
#else
  HANDLE hFind = INVALID_HANDLE_VALUE;
  WIN32_FIND_DATA ffd;

  hFind = FindFirstFileA(lsDirectoryPath.c_str(),&ffd);
  do
  {
	  if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	  {
		  string *lpNew = new string(ffd.cFileName);
		  mcDirectoryList.Add(lpNew);
	  } 
	  else
	  {
		  string *lpNew = new string(ffd.cFileName);
		  mcFileList.Add(lpNew);
	  }

  }while(FindNextFileA(hFind,&ffd) != 0 );

  FindClose(hFind);
#endif


/*

  boost::filesystem::path full_path( boost::filesystem::initial_path<boost::filesystem::path>() );

  full_path = boost::filesystem::system_complete( boost::filesystem::path( lsDirectoryPath ) );

  if ( !boost::filesystem::exists( full_path ) )
  {
      TRACE("Directory Not Found: " << full_path.c_str());
    return ;
  }

  if ( boost::filesystem::is_directory( full_path ) )
  {
    boost::filesystem::directory_iterator end_iter;
    for ( boost::filesystem::directory_iterator dir_itr( full_path ); dir_itr != end_iter; ++dir_itr )
        {
            if ( boost::filesystem::is_directory( dir_itr->status() ) )
            {
                string lsMine=dir_itr->path().m_pathname;
                AddDirectory(lsMine);
            }
            else if ( boost::filesystem::is_regular_file( dir_itr->status() ) )
            {
                AddFile(dir_itr->path().c_str());
            }
            else
            {
                AddUnknown(dir_itr->path().c_str());
            }
        }
  }
  else // must be a file
  {
    TRACE("Path is not a Directory: " << full_path.c_str());
  }*/
};

void cDirectoryFileList::Clear()
{
	mcFileList.Init(5);
	mcDirectoryList.Init(5);
	mcUnknownList.Init(5);
 
};

void cDirectoryFileList::ResizeFiles(uint16 liFiles)
{
	mcFileList.ChangeSize(liFiles);
};

void cDirectoryFileList::ResizeDirectories(uint16 liDirectories)
{
	mcDirectoryList.ChangeSize(liDirectories);
};

void cDirectoryFileList::ResizeUnknowns(uint16 liUnknowns)
{
	mcUnknownList.ChangeSize(liUnknowns);
};


cDirectoryFileList::~cDirectoryFileList()
{
    
}

