#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void forceSkip();
void success();
void error();
void info();
void red(char *format, ...);
void green(char *format, ...);

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

void forceSkip()
{
	printf("\n");
}

void success()
{
	init();
	setConsole(FOREGROUND_GREEN);
	printf("[ Success ]: ");
	reset();
}

void error()
{
	init();
	setConsole(FOREGROUND_RED);
	printf("[ Error ]: ");
	reset();
}

void red(char *format, ...)
{
	setConsole(FOREGROUND_RED);
	va_list arg;
	va_start(arg, format);
	printf(format, arg);
	reset();
}

void green(char *format, ...)
{
	setConsole(FOREGROUND_GREEN);
	va_list arg;
	va_start(arg, format);
	printf(format, arg);
	reset();
}

void info() {
	init();
	setConsole(FOREGROUND_INTENSITY);
	printf("[ Info ]: ");
	reset();
}

void log_success(char *format, ...)
{
	success();
	va_list arg;
	va_start(arg, format);
	printf(format, arg);
	forceSkip();
}

void log_error(char *format, ...)
{
	error();
	va_list arg;
	va_start(arg, format);
	printf(format, arg);
	forceSkip();
}

void log_info(char *format, ...)
{
	info();
	va_list arg;
	va_start(arg, format);
	printf(format, arg);
	forceSkip();
}

void log_split(const char* message, int size) {
	init();
	setConsole(BACKGROUND_INTENSITY);
	char* line;
	int i;
	if(size < 2) {
		log_error("log_split: size is too small");
		return;
	}
	int totalSize = size * 2 + 1;
	line = (char*)malloc(totalSize * sizeof(char));
	line[0] = ' ';
	line[1] = '-';
	for( i = 2; i < totalSize; i+=2) {
		line[i] = '=';
		line[i+1] = '-';
	}
	line[totalSize - 1] = '\0';
	printf("%s", message);
	printf("%s", line);
	forceSkip();
	reset();
}