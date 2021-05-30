#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("_____begin_____\n");
    pid_t ret = fork();
    if(ret < 0)
    {
        perror("fork");
        return 0;
    }
    else if(ret > 0)
    {
        while(1)
        {
        printf("i am father, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(5);
       }
    }
    else 
    {
      while(1)
        {
        printf("i am child, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(5);
       }
    }
   //printf("laoxuha 666\n");
    return 0;
}
