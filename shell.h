#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024

void display_prompt(void);
int execute_command(const char *command);
void handle_exit(const char *command);
int get_input(char **buffer);
int execute_command_in_path(char *args[]);
void execute_directly(char *args[], char *error_message);

#endif

