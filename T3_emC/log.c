/* Change console text color, then restore it back to normal. */
#include <stdio.h>
#include <windows.h>
#include <stdarg.h>

HANDLE hConsole;
WORD original;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

// void my_print(const char* format, ...);
// char *convert(unsigned int num, int base);

void forceSkip() {
	printf("\n");
}

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