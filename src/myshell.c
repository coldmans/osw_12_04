#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ls_command.h"
#include "cat.h"
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 80
#define MAX_ARGS 10
int main()
{

    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while (1)
    {
        // prompt
        printf("myshell> ");
        // read command

        fgets(input, MAX_LINE, stdin);

        // parse command
        int i = 0;

        token = strtok(input, " \n\t");

        while (token != NULL)
        {
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL;

        if (argv[0] == NULL)
        {
            continue;
        }

        if (strcmp(argv[0], "exit") == 0)
        {
            printf("Goodbye!\n");
            exit(0);
        }
        else if (strcmp(argv[0], "cd") == 0)
        {

            chdir(argv[1]);
        }
        else if (strcmp(argv[0], "pwd") == 0)
        {
            getcwd(input, MAX_LINE);
            printf("%s\n", input);
        }
        else if (strcmp(argv[0], "ls") == 0)
        {
            my_ls();
        }
        else if (strcmp(argv[0], "cat") == 0)
        {
            my_cat(argv[1]);
                }
        else
        {
            if (access(argv[0], X_OK) == 0)
            {
                printf("execute %s\n", argv[0]);
                pid_t pid = fork();
                if (pid < 0)
                {
                    perror("fork");
                }
                else if (pid == 0)
                {
                    if (execvp(argv[0], argv) == -1)
                    {
                        perror("execvp");
                        exit(1);
                    }
                }
                else
                {
                    int status;
                    if (waitpid(pid, &status, 0) == -1)
                    {
                        perror("waitpid");
                    }
                }
            }
            else
            {
                printf("command not found %s\n", argv[0]);
            }
        }
    }
}