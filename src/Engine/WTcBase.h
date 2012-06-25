#ifndef __WTCBASE_H__
#define __WTCBASE_H__

extern string __scopeSource;

#if WT_OS_TYPE==OS_WIN32

/**
 * \brief This Class is responsible for initialising and starting the Program. This is so the program can be created from a single line.
 * \tparam cX This is the class that will first be called (The Core Process - it must inherit cProcess) and will initialise and start the game.
 * \tparam cS This is the class that will be used for doing the Settings for the game and engine (it must inherit cUserSettings).
 * This will create a window. Initialise the Engine and Create the first process - of type cX, before entering the main loop.
 * This version of the class is for Windows.
 * This is best called using the macro _START_PROGRAM(TYPE,SETTINGS).
 */
template<class cX,class cS> class cMainThread
{
	cMainThread(){};
public:
	~cMainThread(){};

 	///Function for Starting the Engine and Game. Will Create a window and initialise all components of the engine. It will create and instance of cX and enter the main loop.
	static uint32 Start(HINSTANCE hInstance)
	{
        LOGGING_INIT()
        LOGGING_ADD_FILE("main","main.log")

        TRACE("Entering")

		gpSettings =new cS;
		cSettings *mpCast;
		mpCast=dynamic_cast<cSettings*>(gpSettings);
		mpCast->cSettings::Settings();
		gpSettings->Settings();
		if(mpCast) cSettings::SetupVariables();
		gpWindow=new cWindow(hInstance);



		cMainThread::GetGLVersion();

		gpTimer=new cSync();

		cEventHandler::Instance();

        glewInit();

		new cX;

		printf("Whatever it was you were talking about...\n");
		cCollisionHandler::Instance();
		TRACE("Start Updating");
		cKernel::Instance()->Update();

		delete gpSettings;
		gpSettings=0;
		delete cKernel::Instance();
		TRACE("Finished Bamboo V 1.2");
		return gpWindow->msg.wParam;
	};
	///This will detect the Version of OpenGL the system is using as well as the GLSL compiler and print the data to the screen.
	static void GetGLVersion()
	{
  //  int major,minor;
	// for all versions
      char* verGL = (char*)glGetString(GL_VERSION); // ver = "3.2.0"

/*      major = verGL[0] - '0';
      if( major >= 3)
      {
       // for GL 3.x
       glGetIntegerv(GL_MAJOR_VERSION, &major); // major = 3
       glGetIntegerv(GL_MINOR_VERSION, &minor); // minor = 2
      }
      else
      {
            minor = verGL[2] - '0';
      }
*/
      // GLSL
      char *verSHDR = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    TRACE("***************************************************************************");
	TRACE("Renderer: " << glGetString(GL_RENDERER));
	TRACE("GL Version : " << verGL);
	TRACE("Shading Language : " << verSHDR);
	TRACE("***************************************************************************");


	};

};

#endif

#if WT_OS_TYPE==OS_LINUX

/**
 * \brief This Class is responsible for initialising and starting the Program. This is so the program can be created from a single line.
 * \tparam cX This is the class that will first be called (The Core Process - it must inherit cProcess) and will initialise and start the game.
 * \tparam cS This is the class that will be used for doing the Settings for the game and engine (it must inherit cUserSettings).
 * This will create a window. Initialise the Engine and Create the first process - of type cX, before entering the main loop.
 * This version of the class is for Linux.
 * This is best called using the macro _START_PROGRAM(TYPE,SETTINGS).
 */
template<class cX,class cS> class cMainThread
{
	cMainThread(){};
public:
	~cMainThread(){};
	///Function for Starting the Engine and Game. Will Create a window and initialise all components of the engine. It will create and instance of cX and enter the main loop.
	static uint32 Start()
	{
			LOGGING_INIT()
			LOGGING_ADD_FILE("main","main.log")
			TRACE("Entering")

		try {
		  	gpSettings =new cS;
		cSettings *mpCast;
		mpCast=dynamic_cast<cSettings*>(gpSettings);
		mpCast->cSettings::Settings();
		gpSettings->Settings();
		if(mpCast) cSettings::SetupVariables();

		TRACE("calling glewInit to initialise OpenGL");


			TRACE("Setting up cWindow...");
			gpWindow=new cWindow();



//			cMainThread::GetGLVersion();

			TRACE("Setting up cSync...");
			gpTimer=new cSync();

			TRACE("Setting up cEventHandler...");
			cEventHandler::Instance();

		glewInit();


			TRACE("Creating the cCore process");
			new cX;

			TRACE("Setting up cCollisionHandler");
			cCollisionHandler::Instance();

			//Start the main loop
			TRACE("Calling cKernel::Update to start the main loop");
			cKernel::Instance()->Update();

			delete gpSettings;

			TRACE("Exiting cKernel");
			delete cKernel::Instance();
		} catch(CException e) {
			cerr << "Unhandled exception:" << e.message << endl;
			TRACEERROR("Unhandled exception:" << e.message);
			return 1;
		}

		TRACE("Exiting program and reporting success")
		return EXIT_SUCCESS;
	};
	///This will detect the Version of OpenGL the system is using as well as the GLSL compiler and print the data to the screen.
	static void GetGLVersion()
		{
int major,minor;
	// for all versions
      char* verGL = (char*)glGetString(GL_VERSION); // ver = "3.2.0"

      major = verGL[0] - '0';
      if( major >= 3)
      {
       // for GL 3.x
       glGetIntegerv(GL_MAJOR_VERSION, &major); // major = 3
       glGetIntegerv(GL_MINOR_VERSION, &minor); // minor = 2
      }
      else
      {
            minor = verGL[2] - '0';
      }

      // GLSL
      char *verSHDR = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    trace("***************************************************************************");
	trace("Renderer: " << glGetString(GL_RENDERER));
	trace("GL Version : " << verGL);
	trace("Shading Language : " << verSHDR);
	trace("***************************************************************************");

	};


};

#endif







#endif
