#if !defined(__STDIO_H)
#define __STDIO_H
#include "vga.h"
#include "stdarg.h"
#include "string.h"

void putchar(char c);
void puts(char *input);
int printf(const char *, ...);

#endif // (__STDIO_H)
