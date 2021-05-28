#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if(pid <  0)
    {
        perror("fork");
        return 0;
    }

    else if(pid == 0)
    {
        int count = 20;
        while(1)
        {
          if (count <= 0)
           {
                break;
           }
        printf("child, pid = %d, ppid = %d\n", getpid(), getppid());
        count--;
        sleep(1);
        }
        exit(10);
    }

    else
    {
        printf("begin-----> father, pid = %d, ppid = %d\n",getpid(), getppid());
        int status;
        wait(&status);
        //printf("exit_code: %d\n",(status >> 8) & 0xFF);
        printf("sig_code : %d\n", status & 0x7F);


        while(1)
        {
        printf("father, pid = %d, ppid = %d\n",getpid(), getppid());
        sleep(1);
        }
    }
    return 0;
}
