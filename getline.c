#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

#define BUFFER_SIZE 1024

static char input_buffer[BUFFER_SIZE];
static size_t buffer_pos;
static size_t buffer_size;

/**
 * custom_getline - read a line of input.
 * @buffer: The buffer to store the input.
 * Return: The number of characters read or -1 on error.
 */
ssize_t custom_getline(char **buffer)
{
	ssize_t bytes_read;
	size_t line_length = 0;
	char c;

	if (buffer_pos >= buffer_size)
	{
		bytes_read = read(STDIN_FILENO, input_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (bytes_read);
		buffer_size = (size_t)bytes_read;
		buffer_pos = 0;
	}
	while (buffer_pos < buffer_size)
	{
		c = input_buffer[buffer_pos++];
		line_length++;
		if (c == '\n')
		{
			break;
		}
		*buffer = (char *)realloc(*buffer, line_length);
		if (*buffer == NULL)
		{
			return (-1);
		}
		(*buffer)[line_length - 1] = c;
	}
	*buffer = (char *)realloc(*buffer, line_length + 1);
	if (*buffer == NULL)
	{
		return (-1);
		(*buffer)[line_length] = '\0';
		return (line_length);
}

