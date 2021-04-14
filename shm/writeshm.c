#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>


#define KEY 0x99999999

int main()
{
    int shmid = shmget(KEY, 1024, IPC_CREAT | 0664 );

    if(shmid < 0)
    {
        perror("shmget");
        return -1;
    }

    void* lp = shmat(shmid, NULL, 0);
    //strcpy((char*)lp, "kangkangjiayou");

    while(1)
    {
        int i = 0;
        for(i=0 ; i < 100000; i++)
        {
            char buf[1024] = {0};
            sprintf(buf, "%s-%d","chengkangjiayou", i);
            strcpy((char*)lp, buf);
            sleep(1);
        };
    }

    return 0;
}
