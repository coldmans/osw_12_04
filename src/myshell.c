#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ls_command.h"
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
        }
        else
        {
            if (access(argv[0], X_OK) == 0)
            {
                printf("execute %s\n", argv[0]);
            }
            else
            {
                printf("command not found %s\n", argv[0]);
            }
            return 0;
        }
    }
}