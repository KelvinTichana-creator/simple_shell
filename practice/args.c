#include <unistd.h>
#include <stdio.h>
#include <string.h>
/**
 * main - Print all command line arguments
 *
 * @ac: The number of arguments
 * @av: An array of command line arguments
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	int i;

	for (i = 0; av[i]; i++)
	{
		write(STDOUT_FILENO, av[i], strlen(av[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

