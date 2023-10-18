#include "_string.h"

/**
 * _strlen - Calculate the length of a string
 * @str: The input string
 *
 * Return: The length of the string
 */
size_t _strlen(const char *str)
{
	size_t length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * _strcpy - Copy a string
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the destination string
 */
char *_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_start);
}

/**
 * _strncpy - Copy a portion of a string
 * @dest: The destination string
 * @src: The source string
 * @n: The maximum number of characters to copy
 *
 * Return: A pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *dest_start = dest;

	while (n > 0 && *src != '\0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return (dest_start);
}
