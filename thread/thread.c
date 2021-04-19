#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_create(void* arg)
{
    while(1)
    {
    printf("kang\n");
    sleep(1);
    }
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_create, NULL);
    if(ret < 0)
    {
        perror("pthread_create");
        return -1;
    }

    while(1)
    {
        printf("i am main thraed\n");
        sleep(1);
    }
    return 0;
}
