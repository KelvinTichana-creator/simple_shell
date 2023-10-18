#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Read and print user input
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;

	write(STDOUT_FILENO, "$ ", 2);

	while (getline(&line, &len, stdin) != -1)
	{
		if (line[0] != '\n')
		{
			write(STDOUT_FILENO, line, strlen(line));
		}
		write(STDOUT_FILENO, "$ ", 2);
	}
	free(line);
	return (0);
}

