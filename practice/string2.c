#include "_string.h"

/**
 * _strcmp - Compare two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: An integer less than, equal to, or greater than zero
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strncmp - Compare a portion of two strings
 * @s1: The first string
 * @s2: The second string
 * @n: The number of characters to compare
 *
 * Return: An integer less than, equal to, or greater than zero
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 == *s2)
	{
		if (*s1 == '\0' || n == 1)
		{
			return (0);
		}
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strchr - Find the first occurrence of a character in a string
 * @str: The string to search
 * @c: The character to find
 *
 * Return: A pointer to the first matching character or NULL
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * _strstr - Find the first occurrence of a substring in a string
 * @haystack: The string to search
 * @needle: The substring to find
 *
 * Return: A pointer to the first matching substring or NULL
 */
char *_strstr(const char *haystack, const char *needle)
{
	size_t needle_len = _strlen(needle);

	while (*haystack != '\0)
	{
		if (_strncmp(haystack, needle, needle_len) == 0)
		{
			return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}

