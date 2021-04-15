#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main()
{
    printf("process start\n");
    raise(2);
    printf("hahahahh\n");
    kill(getpid(), 2);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
