#include <stdio.h>
#include <stdarg.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <windows.h>


HANDLE hConsole;
WORD original;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

void init()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	original = consoleInfo.wAttributes;
}

void reset()
{
	SetConsoleTextAttribute(hConsole, original);
}

void setConsole(int color)
{
	SetConsoleTextAttribute(hConsole, color);
}

#else

#define FOREGROUND_GREEN 1
#define FOREGROUND_RED 1


void init()
{
	
}

void reset()
{
	
}

void setConsole(int color)
{
	
}

#endif

void forceSkip() {
	printf("\n");
}

void success() {
	init();
	setConsole(FOREGROUND_GREEN);
	printf("[ Success ]: ");
	reset();
}



void error() {
	init();
	setConsole(FOREGROUND_RED);
	printf("[ Error ]: ");
	reset();
}


void red(char *format, ...) {
	setConsole(FOREGROUND_RED);
	va_list arg;
	va_start (arg, format);
	printf(format, arg);
	reset();
}

void green(char *format, ...) {
	setConsole(FOREGROUND_GREEN);
	va_list arg;
	va_start (arg, format);
	printf(format, arg);
	reset();
}

void log_success(char *format, ...) {
	success();
	va_list arg;
	va_start (arg, format);
	printf(format, arg);
	forceSkip();
}


void log_error(char *format, ...) {
	error();
	va_list arg;
	va_start (arg, format);
	printf(format, arg);
	forceSkip();
}