#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int g_val = 1;

void sigcb(int signo)
{
    g_val = 0;
    printf("signo is %d\n", signo);
}

int main()
{
    signal(2, sigcb);
    while(g_val)
    {

    }
    return 0;
}
