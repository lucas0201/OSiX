#if !defined(__STRING_H)
#define __STRING_H
#include "stddef.h"

int strcmp(char *str1, char *str2);
void *memcpy(void *destination, void *source, size_t num);
char *strcpy(char *destination, char *source);
size_t strlen(char *input);

#endif
