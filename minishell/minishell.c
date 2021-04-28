#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>


char g_command[1024];

int ExecCommand(char* argv[])
{
    if(argv[0] == NULL)
    {
        printf("ExecCommand failed\n");
        return -1;
    }

    pid_t pid = fork();
    if(pid < 0)
    {
       perror("fork");
        return -1;
    }

    else if(pid == 0)
    {
        execvp(argv[0], argv);
        exit(0);
    }

    else
    {
        waitpid(pid, NULL, 0);
    }
    return 0;
}


int GetCommand()
{
    printf("[minishell@localhost minishell] ");
    fflush(stdout);
    memset(g_command,'\0',sizeof(g_command));
    if(fgets(g_command, sizeof(g_command) - 1, stdin) == NULL)
    {
        perror("fgets error");
        return -1;
    }
    printf("%s\n", g_command);
    return 0;
}


int DealCommand(char* command)
{
    int argc = 0;
    char* argv[1024] = {0};
    while(*command)
    {
        if(!isspace(*command) && *command != '\0')
        {
            argv[argc] = command;
            argc++;
            while(!isspace(*command) && *command != '\0')
            {
                command++;
            }
            *command = '\0';
        }
        command++;
    }
   argv[argc] = NULL;
    int i;
    for( i = 0; i < argc; i++)
    {
        printf("%d:%s\n", i, argv[i]);
    }
    ExecCommand(argv);
    return 0;
}

int main()
{
    while(1)
    {
        if(GetCommand() == -1)
        {
            continue;
        }

        DealCommand(g_command);
    }
    return 0;
}
