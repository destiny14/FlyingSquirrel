#ifndef __WINSTRINGHELP_H__
#define __WINSTRINGHELP_H__

#include "CCStdC.h"

class CWinStringHelp {

public:
	static int CWinStringHelp::convertLPTSTRToCharArray(LPTSTR, char*& dst);
	static int CWinStringHelp::splitCharArrayByDelimiter(char* txt, const char* delimiter, char**& dst);
};

#endif