#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include <unistd.h>

/**
 * execute_command - Execute a command with arguments.
 * @command: The command and its arguments as a single string.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(const char *command)
{
	char *token;
	char *args[64];
	int arg_count = 0;
	char error_message[1024];
	char *command_copy;
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		strcpy(error_message, "fork: ");
		write(STDERR_FILENO, error_message, strlen(error_message));
		perror(NULL);
		return (-1);
	}
	else if (pid == 0)
	{
		command_copy = strdup(command);
		token = strtok(command_copy, " ");
		while (token != NULL)
		{
			args[arg_count] = token;
			arg_count++;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;
		if (execute_command_in_path(args) == -1)
		{
			execute_directly(args, error_message);
		}
		free(command_copy);
		_exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}

/**
 * execute_command_in_path - Execute a command that is in the system's PATH.
 * @args: The command and its arguments.
 * Return: 0 on success, -1 on failure.
 */
int execute_command_in_path(char *args[])
{
	char *path = getenv("PATH");
	char cmd_path[1024];
	int len;
	char *token;

	if (path != NULL)
	{
		token = strtok(path, ":");
		while (token != NULL)
		{
			len = strlen(token);
			strncpy(cmd_path, token, len);
			cmd_path[len] = '/';
			strcpy(cmd_path + len + 1, args[0]);
			if (execve(cmd_path, args, NULL) != -1)
				return (0);
			token = strtok(NULL, ":");
		}
	}
	return (-1);
}

/**
 * execute_directly - Execute a command directly (without searching in PATH).
 * @args: The command and its arguments.
 * @error_message: The error message buffer.
 * Return: nothing
 */
void execute_directly(char *args[], char *error_message)
{
	if (execve(args[0], args, NULL) == -1)
	{
		strcpy(error_message, args[0]);
		strcat(error_message, ": ");
		write(STDERR_FILENO, error_message, strlen(error_message));
		perror(NULL);
	}
}
/**
 * handle_exit - exit
 * @command: cli arg
 * Return: nothing
 */
void handle_exit(const char *command)
{
	char *arg;
	int exit_status;

	if (strncasecmp(command, "exit", 4) == 0)
	{
		exit_status = 0;
		if (strlen(command) > 4)
		{
			arg = strchr(command, ' ');
			if (arg)
			{
				arg++;
				exit_status = atoi(arg);
			}
		}
		exit(exit_status);
	}
}
/**
 * print_environment - prints env
 * Return: nthing
 */
void print_environment(void)
{
    size_t len;
    char **env = environ;
    
    while (*env)
    {
        len = strlen(*env);
        write(STDOUT_FILENO, *env, len);
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}
