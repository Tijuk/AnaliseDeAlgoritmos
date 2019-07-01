#ifndef __LOG__H_
#define __LOG__H_

/**
 * Prints "[ Success ]: {message}\n" in green
 */
void log_success(char *format, ...);

/**
 * Prints "[ Error ]: {message}\n" in red
 */
void log_error(char *format, ...);
void log_info(char *format, ...);

void log_split(const char* message, int size);

void setColor(const char* color);
void resetColor();

void red(char *format, ...);
void green(char *format, ...);

#endif