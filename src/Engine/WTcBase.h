#ifndef __WTCBASE_H__
#define __WTCBASE_H__

#if WT_OS_TYPE==OS_WIN32
/*This Class is responsible for initialising and starting the Program. This is so the program can be created from a single line.
 *
 */
template<class cX,class cS> class cMainThread
{
	cMainThread(){};
public:
	~cMainThread(){};
	static uint32 Start(HINSTANCE hInstance)
	{
		cS *mpSettings =new cS;
		cSettings *mpCast;
		mpCast=dynamic_cast<cSettings*>(mpSettings);
		mpCast->cSettings::Settings();
		mpSettings->Settings();
		if(mpCast) cSettings::SetupVariables();
		gpWindow=new cWindow(hInstance);
		
		gpTimer=new cSync();
		
		cEventHandler::Instance();
		
		new cX;
		
		printf("Whatever it was you were talking about...\n");
		cCollisionHandler::Instance();
		trace("Start Updating");
		cKernel::Instance()->Update();
		
		delete mpSettings;
		delete cKernel::Instance();
		return gpWindow->msg.wParam;
	};
	
	
};

#endif

#if WT_OS_TYPE==OS_LINUX
/*This Class is responsible for initialising and starting the Program. This is so the program can be created from a single line.
 * 
 */
template<class cX,class cS> class cMainThread
{
	cMainThread(){};
public:
	~cMainThread(){};
	static uint32 Start()
	{
		LOGGING_INIT()
		LOGGING_ADD_FILE("main","main.log")
		LOGGING_SET_SCOPE_SOURCE("main")
		TRACE("Entering")
		
		try {
		  	cS *mpSettings =new cS;
		cSettings *mpCast;
		mpCast=dynamic_cast<cSettings*>(mpSettings);
		mpCast->cSettings::Settings();
		mpSettings->Settings();
		if(mpCast) cSettings::SetupVariables();
			
			TRACE("Setting up cWindow...");
			gpWindow=new cWindow();
			
			TRACE("Setting up cSync...");
			gpTimer=new cSync();
			
			TRACE("Setting up cEventHandler...");
			cEventHandler::Instance();

			TRACE("calling glewInit to initialise OpenGL");
			glewInit();
			
			TRACE("Creating the cCore process");
			new cX;
			
			TRACE("Setting up cCollisionHandler");
			cCollisionHandler::Instance();
			
			//Start the main loop
			TRACE("Calling cKernel::Update to start the main loop");
			cKernel::Instance()->Update();
			
			delete mpSettings;
			
			TRACE("Exiting cKernel");
			delete cKernel::Instance();
		} catch(CException e) {
			cerr << "Unhandled exception:" << e.message << endl;
			ERROR("Unhandled exception:" << e.message);
			return 1;
		}
		
		TRACE("Exiting program and reporting success")
		return EXIT_SUCCESS;
	};
	
	
};

#endif


#endif
