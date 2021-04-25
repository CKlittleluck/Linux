#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 4

struct ThreadData 
{
    int num_;
    ThreadData()
    {
        num_ = -1;
    }
};

class Data
{
    public:
        void SetData(int data)
        {
            data_ = data;
        }

        int Getdata()
        {
            return data_;
        }
    private:
      int data_;
};

void* thread_create(void* arg)
{
    //ThreadData* td = (ThreadData*) arg;
    Data* d = (Data*)arg;

    while(1)
    {
    printf("kang :%d\n", d->Getdata ());
    sleep(1);
    }
    delete d;
}

int main()
{
    pthread_t tid;

    int i = 0;
    for(i = 0; i < THREAD_COUNT; i++)
    {
        //struct ThreadData* td = new ThreadData;
        //td->num_ = i;
        Data* d = new Data;
        d->SetData(i);
        int ret = pthread_create(&tid, NULL, thread_create, (void*)d);
    if(ret < 0)
    {
        perror("pthread_create");
        return -1;
    }
    }

    while(1)
    {
        printf("i am main thraed\n");
        sleep(1);
    }
    return 0;
}
