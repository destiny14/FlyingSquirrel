#include "CommonMain.h"
#include "CommandLineParameter.h"


int CCommonMain::main(char** par, int parLength)
{

	CCommandLineParameter* pCommand = new CCommandLineParameter(par, parLength);
	m_appDebug = pCommand->isParameterActive("-debug");
	m_windowWidth = pCommand->getParameterInt("-w", pCommand->getParameterInt("-width", 800));
	m_windowHeight = pCommand->getParameterInt("-h", pCommand->getParameterInt("-height", 600));
	int dFPS = pCommand->getParameterInt("-fps", 60);

	char* tmp = pCommand->getParameterCharArr("-l", "h");
	
	switch (tmp[0])
	{
		case 'e':
			//log("Created LogFile %s\n", "e");
			g_pLogfile->CreateLogfile("log", E_ERROR);
			break;
		case 'w':
			//log("Created LogFile %s\n", "w");
			g_pLogfile->CreateLogfile("log", E_WARNING);
			break;
		case 'n':
			//log("Created LogFile %s\n", "n");
			g_pLogfile->CreateLogfile("log", E_NONE);
			break;
		case 'a':
			//log("Created LogFile %s\n", "a");
		default:
			//log("Created LogFile %s\n", "d/a");
			g_pLogfile->CreateLogfile("log", E_ALL);
			break;
	}


	fprintf(stdout, "========================\nDebug: %i\n", m_appDebug);
	fprintf(stdout, "========================\nFenster:\n\tBreite: %i\n\tHoehe: %i\n========================\n", m_windowWidth, m_windowHeight);
	
	m_eglView.init("FlyingSquirrel", m_windowWidth, m_windowHeight);
	m_app.setDesiredFPS(dFPS);
	return Application::getInstance()->run();
}

void CCommonMain::printHelp()
{
#ifdef __linux__
	fprintf(stdout, "========================\n%s\n%s\n%s\n%s\n%s\n%s\n========================\n", "Verfuegbare Parameter:", "-debug\t\tDebug-Schalter", "-w\t\tBreite des Spielfensters", "-h\t\tHoehe des Spielfensters", "-l\t\tLog-Level\n\t\t(a - all [standard], e - error, w - warning, n - none)" ,"help, -h\tDiese Seite");
#else
	log("%s\n%s\n%s\n%s\n%s\n", "Verfuegbare Parameter:", "-debug\t\tDebug-Schalter", "-w\t\tBreite des Spielfensters", "-h\t\tHoehe des Spielfensters", "help, -h\tDiese Seite");
#endif
}

int CCommonMain::getWindowHeight()
{
	return m_windowHeight;
}

int CCommonMain::getWindowWidth()
{
	return m_windowWidth;
}

bool CCommonMain::getAppDebug()
{
	return m_appDebug;
}