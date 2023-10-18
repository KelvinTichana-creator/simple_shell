#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * main - Print the parent process ID
 *
 * Return: Always 0
 */
int main(void)
{
	pid_t parent_pid = getppid();
	char pid_str[16];
	int len = snprintf(pid_str, sizeof(pid_str), "%d", parent_pid);

	if (len > 0)
	{
		write(STDOUT_FILENO, pid_str, len);
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	else
	{
		write(STDERR_FILENO, "Error in converting PID to string\n", 34);
		return (EXIT_FAILURE);
	}
}

