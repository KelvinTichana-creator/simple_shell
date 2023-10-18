#include <stdio.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 128

/**
 * _realloc_buffer - Reallocate the line buffer if needed
 * @line: A pointer to the buffer where the line is stored
 * @size: A pointer to the buffer size
 *
 * Return: 0 on success, -1 on failure
 */
static int _realloc_buffer(char **line, size_t *size)
{
	size_t new_size = *size * 2;
	char *new_line = (char *)realloc(*line, new_size);

	if (new_line == NULL)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	*line = new_line;
	*size = new_size;
	return (0);
}

/**
 * custom_getline - Read a line from a file stream
 * @lineptr: A pointer to the buffer where the line is stored
 * @n: A pointer to the buffer size
 * @stream: The file stream to read from
 *
 * Return: The number of characters read (excluding the newline character),
 * or -1 on error or end of input.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	char *line = *lineptr;
	size_t size = *n, pos = 0;
	int c;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*n = INITIAL_BUFFER_SIZE;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		c = fgetc(stream);
		if (c == EOF)
		{
			if (pos == 0)
			{
				free(line);
				*lineptr = NULL;
			}
			else
				line[pos] = '\0';
			return ((pos == 0) ? -1 : pos);
		}
		if (pos >= (size - 1))
		{
			if (_realloc_buffer(&line, &size) == -1)
				return (-1);
		}
		line[pos++] = (char)c;
		if (c == '\n')
		{
			line[pos] = '\0';
			return (pos);
		}
	}
}

