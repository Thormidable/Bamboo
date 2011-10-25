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

		cMainThread::GetGLVersion();

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

	static void GetGLVersion()
	{
    int major,minor;
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

    trace("***************************************************************************");
	trace("Renderer: " << glGetString(GL_RENDERER));
	trace("GL Version : " << verGL);
	trace("Shading Language : " << verSHDR);
	trace("***************************************************************************");


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
