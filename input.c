#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * get_input - get user  commands
 * @buffer: cli buffer
 * Return: int
 */
int get_input(char **buffer)
{
	ssize_t read_bytes;
	size_t n = 0;

	read_bytes = getline(buffer, &n, stdin);
	if (read_bytes == -1)
	{
		perror("getline");
		return (0);
	}
	if (read_bytes == 0)
	{
		return (0);
	}
	if ((*buffer)[read_bytes - 1] == '\n')
	{
		(*buffer)[read_bytes - 1] = '\0';
	}
	return (1);
}

