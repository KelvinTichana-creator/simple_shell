#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
    char *prompt = "#cisfun$ ";
    write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * execute_command - Execute a command with arguments.
 * @command: The command and its arguments as a single string.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(const char *command)
{
    char *token;
    char *args[64];  // Maximum number of arguments (adjust as needed)
    int arg_count = 0;
    char error_message[1024];

    pid_t pid = fork();

    if (pid == -1)
    {
        strcpy(error_message, "fork: ");
        write(STDERR_FILENO, error_message, strlen(error_message));
        perror(NULL);
        return -1;
    }
    else if (pid == 0)
    {
        // Child process
        char *command_copy = strdup(command);  // Make a copy for tokenization
        token = strtok(command_copy, " ");
        while (token != NULL)
        {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        // Check if the command contains a path or not
        if (strchr(args[0], '/') == NULL)
        {
            // The command does not contain a path, search for it in PATH
            char *path = getenv("PATH");
            if (path != NULL)
            {
                token = strtok(path, ":");
                while (token != NULL)
                {
                    char cmd_path[1024];
                    int len = strlen(token);
                    strncpy(cmd_path, token, len);
                    cmd_path[len] = '/';
                    strcpy(cmd_path + len + 1, args[0]);
                    if (execve(cmd_path, args, NULL) != -1)
                    {
                        free(command_copy);
                        _exit(EXIT_SUCCESS); // Found and executed in PATH
                    }
                    token = strtok(NULL, ":");
                }
            }
        }

        // If not found in PATH, attempt to execute directly
        if (execve(args[0], args, NULL) == -1)
        {
            strcpy(error_message, args[0]);
            strcat(error_message, ": ");
            write(STDERR_FILENO, error_message, strlen(error_message));
            perror(NULL);
            free(command_copy);
            _exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}

/**
 * handle_exit - Handle the exit command with or without arguments.
 * @command: The exit command and its arguments.
 */
void handle_exit(const char *command)
{
    // Parse the command and check for arguments
    if (strncasecmp(command, "exit", 4) == 0)
    {
        // Extract the exit status if provided
        int exit_status = 0;
        if (strlen(command) > 4)
        {
            char *arg = strchr(command, ' ');
            if (arg)
            {
                arg++;  // Move past the space character
                exit_status = atoi(arg);
            }
        }

        // Perform the exit with the specified status
        exit(exit_status);
    }
}

/**
 * get_input - Get user input using getline.
 * @buffer: The buffer to store the input.
 * @buffer_size: The size of the buffer.
 * Return: 0 on Ctrl+D (EOF), 1 otherwise.
 */
int get_input(char **buffer)
{
    ssize_t read_bytes;
    size_t n = 0;

    read_bytes = getline(buffer, &n, stdin);

    if (read_bytes == -1)
    {
        perror("getline");
        return 0;
    }

    if (read_bytes == 0)
    {
        return 0; // Ctrl+D (EOF)
    }

    if ((*buffer)[read_bytes - 1] == '\n')
    {
        (*buffer)[read_bytes - 1] = '\0';
    }

    return 1;
}

int main(void)
{
    char *buffer = NULL;
    int is_running = 1;

    while (is_running)
    {
        display_prompt();

        if (!get_input(&buffer))
        {
            break; // Exit on Ctrl+D (EOF)
        }

        // Handle the exit command
        handle_exit(buffer);

        // If it's not an exit command, execute it
        execute_command(buffer);
    }

    free(buffer);

    return (EXIT_SUCCESS);
}

