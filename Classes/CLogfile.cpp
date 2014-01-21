#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "CommonMain.h"
#include "Logfile.h"

CLogfile::CLogfile() 
{
	
}

// Destruktor
//
// schreibt eine abschlussmeldung ins logfile und schliesst es
CLogfile::~CLogfile() 
{
	Write("<p>end of logfile</p></body></html>");
	fclose(m_Logfile);
}

// CreateLogfile (dateiname)
//
// erstellt ein neues Logfile und oeffnet es zum schreiben.
// stelle sicher dass das verzeichnis LOG_LOCATION existiert und die CSS datei vorhanden ist
void CLogfile::CreateLogfile(const char* filename, ERROR_LEVEL errorLevel)
{
	m_errorLevel = errorLevel;
	char* res = new char;
	fprintf(stdout, "%s\n", LOG_LOCATION);
	strcpy(res, LOG_LOCATION);
	strcat(res, filename);
	strcat(res, ".html");
	m_Logfile = fopen(res, "w");
	Write("<html><head><title>Logfile</title><link href='style.css' rel='stylesheet'></head><body>");
	WriteHeading("Logfile", 24);
	if (g_pCommonMain->getAppDebug())
		Write("build: DEBUG<br />");
	else
		Write("build: RELEASE<br />");

	Write("error level: ");
	switch (m_errorLevel)
	{
		case E_ALL:
			Write("E_ALL");
			break;
		case E_WARNING:
			Write("E_WARNING");
			break;
		case E_ERROR:
			Write("E_ERROR");
			break;
		case E_NONE:
			Write("E_NONE");
			break;
	}
//#ifdef _DEBUG
		
//#else
		
//#endif
	fclose(m_Logfile);
	m_Logfile = fopen(res, "a");
}

// WriteHeading (text, groesse)
//
// Schreibt eine Ueberschrift ins Logfile
// size ist die Stufe der Ueberschrift (h1, 2 und 3)
void CLogfile::WriteHeading(const char* text, int size)
{
	char* headerTag = "h1";
	switch (size)
	{
	case 2:
		headerTag = "h2";
		break;
	case 3:
		headerTag = "h3";
		break;
	default:
		break;
	}
	fWrite("<%s>%s</%s>", headerTag, text, headerTag);
	fflush(m_Logfile);
}

void CLogfile::Log(LOG_LEVEL level, const char* text)
{
	switch (level)
	{
		case L_DEBUG:
			if (m_errorLevel == E_ALL)
				fWrite("[DEBUG] %s", text);
			break;
		case L_WARNING:
			if (m_errorLevel == E_ALL || m_errorLevel == E_WARNING)
				fWrite("<div class='warning'>[WARNING] %s</div>", text);
			break;
		case L_ERROR:
			if (m_errorLevel == E_ALL || m_errorLevel == E_ERROR)
				fWrite("<div class='error'>[ERROR] %s</div>", text);
			break;
	}
}

// Write (text)
//
// schreibt einen text ins logfile und flusht es
void CLogfile::Write(const char* text)
{
	fprintf(m_Logfile, text);
	fflush(m_Logfile);
}

// Write (farbe, text)
//
// schreibt einen farbigen text ins logfile
void CLogfile::Write(FORECOLOR color, const char* text)
{
	Write(color, false, text);
}

// Write (farbe, liste, text)
//
// schreibt einen farbigen, ww. als listenelement formatierten text ins logfile
void CLogfile::Write(FORECOLOR color, bool list, const char* text)
{
	if (list)
		Write("<li>");

	switch (color)
	{
	case BLACK:
		Write("<span style='color: black;'>");
		break;
	case RED:
		Write("<span style='color: red;'>");
		break;
	case BLUE:
		Write("<span style='color: blue;'>");
		break;
	case GREEN:
		Write("<span style='color: green;'>");
		break;
	case PURPLE:
		Write("<span style='color: purple;'>");
		break;
	default:
		break;
	}

	Write(text);
	Write("</span>");

	if (list)
		Write("</li>");
	else
		Write("<br />");

}
// fWrite(text, params[])
//
// schreibt einen formatierten text ins logfile
void CLogfile::fWrite(const char* text, ...)
{
	char buff[MAX_BUFFER_SIZE];
	va_list argList;

	va_start(argList, text);
	vsprintf(buff, text, argList);
	va_end(argList);

	Write(buff);
}

// fWrite(farbe, text, params[])
//
// schreibt einen formatierten, farbigen text ins logfile
void CLogfile::fWrite(FORECOLOR color, const char* text, ...)
{
	char buff[MAX_BUFFER_SIZE];
	va_list argList;

	va_start(argList, text);
	vsprintf(buff, text, argList);
	va_end(argList);

	Write(color, buff);
}

// fWrite(farbe, liste, text, params[])
//
// schreibt einen formatierten, farbigen text als listenelement ins logfile
void CLogfile::fWrite(FORECOLOR color, bool list, const char* text, ...)
{
	char buff[MAX_BUFFER_SIZE];
	va_list argList;

	va_start(argList, text);
	vsprintf(buff, text, argList);
	va_end(argList);

	Write(color, list, buff);
}

void CLogfile::fLog(LOG_LEVEL level, const char* text, ...)
{
	char buff[MAX_BUFFER_SIZE];
	va_list argList;

	va_start(argList, text);
	vsprintf(buff, text, argList);
	va_end(argList);

	Log(level, buff);
}

// printFuncRes ( name, ergebnis )
//
// schreibt das ergebnis einer funktion als tabelle ins logfile
void CLogfile::printFuncRes(const char* name, bool result)
{
	if (L_OK == result)
	{
		Write("<table width='100%%' cellSpacing='1' cellPadding='5'");
		Write("border='0' bgcolor='#C0C0C0'><tr><td bgcolor='#FFFFFF' width='35%%'>");
		fWrite("%s</td>", name);
		Write("<td bgcolor='#FFFFFF' width='30%%'><span style='color: green;'>OK</span></td>");
		Write("<td bgcolor='#FFFFFF' width='35%%'>-/-</td></tr></table>");
	}
	else
	{
		Write("<table width='100%%' cellSpacing='1' cellPadding='5'");
		Write("border='0' bgcolor='#C0C0C0'><tr><td bgcolor='#FFFFFF' width='35%%'>");
		fWrite("%s</td>", name);
		Write("<td bgcolor='#FFFFFF' width='30%%'><span style='color: red;'>FAIL</span></td>");
		Write("<td bgcolor='#FFFFFF' width='35%%'>-/-</td></tr></table>");
	}
}