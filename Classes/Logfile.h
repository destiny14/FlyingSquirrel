#ifndef __CLOGFILE_H__
#define __CLOGFILE_H__

#include "Singleton.h"
#include <stdio.h>

#ifdef __linux__
#define LOG_LOCATION "Resources/log/"
#else
#define LOG_LOCATION "log\\"
#endif
#define MAX_BUFFER_SIZE 2048
#define L_FAIL false
#define L_OK true

#define g_pLogfile CLogfile::Get ()

enum FORECOLOR {
	BLACK,
	RED,
	BLUE,
	GREEN,
	PURPLE
};

enum ERROR_LEVEL {
	E_ALL,
	E_WARNING,
	E_ERROR,
	E_NONE,
};

enum LOG_LEVEL {
	L_DEBUG,
	L_WARNING,
	L_ERROR
};

class CLogfile : public TSingleton<CLogfile>
{
public:
	CLogfile();
	~CLogfile();
	void createLogfile(const char* filename, ERROR_LEVEL errorLevel);
	void writeHeading(const char* text, int size);

	void log(LOG_LEVEL level, const char* text);

	void write(const char* text);
	void write(FORECOLOR color, const char* text);
	void write(FORECOLOR color, bool list, const char* text);
	void fWrite(const char* text, ...);
	void fWrite(FORECOLOR color, const char* text, ...);
	void fWrite(FORECOLOR color, bool list, const char* text, ...);

	void fLog(LOG_LEVEL level, const char* text, ...);

	void printFuncRes(const char* name, bool result);

private:
	ERROR_LEVEL m_errorLevel;
	FILE* m_Logfile;
};

#endif //CLOGFILE_H