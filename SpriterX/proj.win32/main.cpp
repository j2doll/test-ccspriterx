#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
	int ret = 0;
	{
		AppDelegate app;

		// main resource directory 
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 
		CCFileUtils::sharedFileUtils()->setResourceDirectory( "./Resources" );
#endif 
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		CCFileUtils::sharedFileUtils()->setResourceDirectory( "assets" );  
#endif     
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS          
		// iPhone, iPad 
#endif 

		CCEGLView::sharedOpenGLView()->setFrameSize(960, 640); 
		ret = CCApplication::sharedApplication()->run();
	}

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
