#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * main - entry point
 * Return: nothing
 */
int main(void)
{
	char *buffer = NULL;
	int is_running = 1;

	while (is_running)
	{
		display_prompt();
		if (!get_input(&buffer))
		{
			break;
		}
		handle_exit(buffer);
		execute_command(buffer);
	}
	free(buffer);
	return (EXIT_SUCCESS);
}

