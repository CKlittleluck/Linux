#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("signo is %d\n", signo);

}

int main()
{
    struct sigaction newcat;
    newcat.sa_handler = sigcb;                                               
    sigemptyset(&newcat.sa_mask);
    newcat.sa_flags = 0;
    sigaction(2, &newcat, NULL);

    while(1)
    {
        sleep(1);
    }
    return 0;
}
