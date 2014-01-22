#include "CommandLineParameter.h"
#include <cstring>
#include <stdlib.h>

CCommandLineParameter::CCommandLineParameter(char** p, int l)
{
	m_pars = p;
	m_len = l;
}

CCommandLineParameter::~CCommandLineParameter() { }

bool CCommandLineParameter::isParameterActive(const char* par)
{
	if(par == nullptr || m_pars == nullptr) return false;

	for(int i = 0; i < m_len; i++)
	{
		if(strcmp(m_pars[i], par) == 0)
			return true;
	}

	return false;
}

int CCommandLineParameter::getParameterInt(const char* par, int alt)
{
	if(par == nullptr || m_pars == nullptr) return alt;

	for(int i = 0; i < m_len; i++)
	{
		if(strcmp(m_pars[i], par) == 0 && (i + 1) < m_len)
			return atoi(m_pars[i + 1]);;
	}

	return alt;
}

char* CCommandLineParameter::getParameterCharArr(const char* par, char* alt)
{
	if(par == nullptr || m_pars == nullptr) return alt;

	for(int i = 0; i < m_len; i++)
	{
		if(strcmp(m_pars[i], par) == 0 && (i + 1) < m_len)
			return m_pars[i + 1];
	}

	return alt;
}