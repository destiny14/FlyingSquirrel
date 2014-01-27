#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <ctime>
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
	write("<p>end of logfile</p></body></html>");
	fclose(m_Logfile);
}

// createLogfile (dateiname)
//
// erstellt ein neues Logfile und oeffnet es zum schreiben.
// stelle sicher dass das verzeichnis LOG_LOCATION existiert und die CSS datei vorhanden ist
void CLogfile::createLogfile(const char* filename, ERROR_LEVEL errorLevel)
{
	m_errorLevel = errorLevel;
	char* res = new char;
	fprintf(stdout, "%s\n", LOG_LOCATION);
	strcpy(res, LOG_LOCATION);
	strcat(res, filename);
	strcat(res, ".html");
	m_Logfile = fopen(res, "w");
	write("<html><head><title>Logfile</title><link href='style.css' rel='stylesheet'></head><body>");
	writeHeading("Logfile", 24);
	if (g_pCommonMain->getAppDebug())
		write("build: DEBUG<br />");
	else
		write("build: RELEASE<br />");
	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);
	fWrite("created: %s<br />", dt);
	write("error level: ");
	switch (m_errorLevel)
	{
		case E_ALL:
			write("E_ALL");
			break;
		case E_WARNING:
			write("E_WARNING");
			break;
		case E_ERROR:
			write("E_ERROR");
			break;
		case E_NONE:
			write("E_NONE");
			break;
	}
	fclose(m_Logfile);
	m_Logfile = fopen(res, "a");
}

// writeHeading (text, groesse)
//
// Schreibt eine Ueberschrift ins Logfile
// size ist die Stufe der Ueberschrift (h1, 2 und 3)
void CLogfile::writeHeading(const char* text, int size)
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

// Log (LogLevel, text)
//
// Schreibt einen Logeintrag
void CLogfile::log(LOG_LEVEL level, const char* text)
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

// write (text)
//
// schreibt einen text ins logfile und flusht es
void CLogfile::write(const char* text)
{
	fprintf(m_Logfile, text);
	fflush(m_Logfile);
}

// write (farbe, text)
//
// schreibt einen farbigen text ins logfile
void CLogfile::write(FORECOLOR color, const char* text)
{
	write(color, false, text);
}

// write (farbe, liste, text)
//
// schreibt einen farbigen, ww. als listenelement formatierten text ins logfile
void CLogfile::write(FORECOLOR color, bool list, const char* text)
{
	if (list)
		write("<li>");

	switch (color)
	{
	case BLACK:
		write("<span style='color: black;'>");
		break;
	case RED:
		write("<span style='color: red;'>");
		break;
	case BLUE:
		write("<span style='color: blue;'>");
		break;
	case GREEN:
		write("<span style='color: green;'>");
		break;
	case PURPLE:
		write("<span style='color: purple;'>");
		break;
	default:
		break;
	}

	write(text);
	write("</span>");

	if (list)
		write("</li>");
	else
		write("<br />");

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

	write(buff);
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

	write(color, buff);
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

	write(color, list, buff);
}

// flog(LogLevel, text, arguments)
//
// Schreibt einen formatierten Logeintrag
void CLogfile::fLog(LOG_LEVEL level, const char* text, ...)
{
	char buff[MAX_BUFFER_SIZE];
	va_list argList;

	va_start(argList, text);
	vsprintf(buff, text, argList);
	va_end(argList);

	log(level, buff);
}

// printFuncRes ( name, ergebnis )
//
// schreibt das ergebnis einer funktion als tabelle ins logfile
void CLogfile::printFuncRes(const char* name, bool result)
{
	if (L_OK == result)
	{
		write("<table width='100%%' cellSpacing='1' cellPadding='5'");
		write("border='0' bgcolor='#C0C0C0'><tr><td bgcolor='#FFFFFF' width='35%%'>");
		fWrite("%s</td>", name);
		write("<td bgcolor='#FFFFFF' width='30%%'><span style='color: green;'>OK</span></td>");
		write("<td bgcolor='#FFFFFF' width='35%%'>-/-</td></tr></table>");
	}
	else
	{
		write("<table width='100%%' cellSpacing='1' cellPadding='5'");
		write("border='0' bgcolor='#C0C0C0'><tr><td bgcolor='#FFFFFF' width='35%%'>");
		fWrite("%s</td>", name);
		write("<td bgcolor='#FFFFFF' width='30%%'><span style='color: red;'>FAIL</span></td>");
		write("<td bgcolor='#FFFFFF' width='35%%'>-/-</td></tr></table>");
	}
}