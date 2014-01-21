#include "main.h"

#define PLATTFORM "WIN32"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	char** pars = nullptr;
	char* cmdLine = nullptr;

	CWinStringHelp::convertLPTSTRToCharArray(lpCmdLine, cmdLine);
	
	int parCount = 0;
	parCount = CWinStringHelp::splitCharArrayByDelimiter(cmdLine, " ", pars);

	return g_pCommonMain->main(pars, parCount);
}