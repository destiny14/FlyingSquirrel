#ifndef __COMMANDLINEPARAMETER_H__
#define __COMMANDLINEPARAMETER_H__

class CCommandLineParameter {
public:
	CCommandLineParameter(char**, int);
	~CCommandLineParameter(void);

	bool isParameterActive(const char*);
	int getParameterInt(const char*, int);
	char* getParameterCharArr(const char*, char*);

private:
	char** m_pars;
	int m_len;

};

#endif