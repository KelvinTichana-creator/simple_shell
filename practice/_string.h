#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

size_t _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(const char *str, int c);
char *_strstr(const char *haystack, const char *needle);

#endif /* _STRING_H */

