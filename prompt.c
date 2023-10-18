#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"
/**
 * display_prompt - displays prompt
 * Return: nothing
 */
void display_prompt(void)
{
	char *prompt = "#cisfun$ ";

	write(STDOUT_FILENO, prompt, strlen(prompt));
}

