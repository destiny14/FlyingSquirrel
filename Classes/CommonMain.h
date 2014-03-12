#ifndef __COMMONMAIN_H__
#define __COMMONMAIN_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "Singleton.h"
#include "Logfile.h"
#include <iostream>

#define g_pCommonMain CCommonMain::Get()

USING_NS_CC;
class CCommonMain : public TSingleton<CCommonMain>
{
public:
	int main(char**, int);
	char* getAppVersion() { return "0.0.1"; }
	int getWindowWidth();
	int getWindowHeight();
	bool getAppDebug();
	char* getEditFilename();
	bool getSkipMenu();

private:
	void printHelp();
	int m_windowHeight;
	int m_windowWidth;
	bool m_appDebug;
	bool m_appFullscreen;
	char* m_editFilename;
	bool m_skipMenu;

	AppDelegate m_app;
	EGLView m_eglView;
};

#endif