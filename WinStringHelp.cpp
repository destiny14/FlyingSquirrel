#include "WinStringHelp.h"
#include <vector>

int CWinStringHelp::convertLPTSTRToCharArray(LPTSTR string, char*& dst)
{
	assert(string);
	#ifdef _UNICODE
		const size_t size = 100;
		dst = new char[size];
		int l = wcstombs(dst, string, size);
		return l;
	#else
		return dynamic_cast<char*>(lpCmdLine);
	#endif
}

int CWinStringHelp::splitCharArrayByDelimiter(char* txt, const char* delimiter, char**& dst)
{
	std::vector<char*> v;
	char* chars_array = strtok(txt, delimiter);
	while(chars_array)
	{
		v.push_back(chars_array);
		chars_array = strtok(nullptr, delimiter);
	}
	v.shrink_to_fit();
	
	dst = new char*[v.size()];
	for(int i = 0; i < v.size(); i++)
		dst[i] = v[i];

	return v.size();
}