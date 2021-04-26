#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <vector>

typedef void (*Handler)(int);

class Data
{
    public:
        Data(int data, Handler handler)
        {
            data_ = data;
            handler_ = handler;
        }

        void run()
        {
            handler_(data_);
        }
    private:
        int data_;
        Handler handler_;
};

class ThreadPool
{
    public:
        ThreadPool(int thread_count, int capa)
        {
            pthread_mutex_init(&mutex_, NULL);                               
            pthread_cond_init(&cond_,NULL);

            capacity_ = capa;
            thread_count_ = thread_count;
            vec_.clear();
            vec_.resize(thread_count);
        }

        ~ThreadPool()
        {
            pthread_mutex_destroy(&mutex_);
            pthread_cond_destroy(&cond_);
        }

        int Oninit()
        {
           int ret =  ThreadCreat();
           if(ret < 0)
           {
               return -1;
           }
           return 0;
        }

        void Push(Data* d)
        {
            pthread_mutex_lock(&mutex_);
            while(que_.size() >= capacity_)
            {
                pthread_mutex_unlock(&mutex_);
                return;
            }
            que_.push(d);
            pthread_mutex_unlock(&mutex_);
            pthread_cond_signal(&cond_);

        }

        void Pop(Data** d)
        {
            *d = que_.front();
            que_.pop();
            
        }

        void PthreadJoin()
        {
            size_t i;
            for(i = 0; i < vec_.size(); i++)
            {
                printf("--------ck---------\n");
                pthread_join(vec_[i], NULL);
            }
        }



        void Thread_Exit()
        {
            pthread_mutex_lock(&mutex_);
            flag = true;
            pthread_mutex_unlock(&mutex_);
            pthread_cond_broadcast(&cond_);
        }

    private:
        int ThreadCreat()
        {
            int i;
            for(i = 0; i < thread_count_; i++)
            {
               int ret =  pthread_create(&vec_[i], NULL, ThreadStart, (void*)this);
                   if(ret < 0)
                   {
                       return -1;
                   }
            }
            return 0;
        }

        static void* ThreadStart(void* arg)
        {
            ThreadPool* tp = (ThreadPool*)arg;
            while(1)
            {
                pthread_mutex_lock(&tp->mutex_);
                while(tp->que_.empty())
                {
                    if(tp->flag)
                    {
                        tp->thread_count_--;
                        pthread_mutex_unlock(&tp->mutex_);
                        pthread_exit(NULL);
                    }
                    pthread_cond_wait(&tp->cond_, &tp->mutex_);
                }
                Data* d;
                tp->Pop(&d);
                pthread_mutex_unlock(&tp->mutex_);
                d->run();

                delete d;

            }
            return NULL;
        }

    private:
        std::queue<Data*> que_;
        pthread_mutex_t mutex_;
        pthread_cond_t cond_;

        int capacity_;
        int thread_count_;
        std::vector<pthread_t> vec_;

        int flag;
};


void func(int data)
{
    printf("d = %d\n", data);
}


int main()
{
    ThreadPool* tp = new ThreadPool(4, 1);
    if(!tp)
    {
        printf("init ThreadPool failed\n");
        return -1;

    }

    if(tp->Oninit() < 0)
    {
        printf("threadpool create faile\n");
        return -1;
    }


    for (int i = 0; i < 500; i++)
    {
        Data* d = new Data(i, func);
        if(!d)
        {
            continue;
        }
        tp->Push(d);
        usleep(1000);
    }

    sleep(5);
    tp->Thread_Exit();
    tp->PthreadJoin();
    delete tp;
    return 0;
}
