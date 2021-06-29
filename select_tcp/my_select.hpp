#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <vector>

class Myselect
{
    public:

        Myselect()
        {
            FD_ZERO(&readfds_);
            nfds_ = -1;
        }

        ~Myselect()
        {
           // FD_CLR(&readfds_);
        }

        void Addfd(int fd)
        {
            FD_SET(fd, &readfds_);

            if(fd > nfds_)
            
            {
                nfds_ = fd;
            }

        }

        void Deletefd(int fd)
        {
            FD_CLR(fd, &readfds_);
            for(int i = nfds_; i >= 0; i--)
            {
                if(Isinset(i))
                {
                    nfds_ = i;
                    break;
                }
            }
        }

        bool Isinset(int fd)
        {
            if(FD_ISSET(fd, &readfds_))
            {
                return true;
            }
            return false;
        }

        int Select(std::vector<int>* vec, struct timeval* timeout = NULL)
        {
            printf("begin select ...\n");
            fd_set tmp = readfds_;
            int ret = select(nfds_ + 1, &tmp, NULL, NULL, 0);
            if(ret < 0)
            {
                perror("select");
                return ret;
            }
            else if(ret == 0)
            {
                printf("select timeout... \n");
            }

            for(int fd = 0; fd <= nfds_; fd--)
            {
                printf("fd is %d, nfds = %d/s", fd, nfds_);
                if(FD_ISSET(fd, &tmp))
                {
                    printf("insert fd is %d\n", fd);
                    vec->push_back(fd);
                }
            }
            return ret;
        }


    private:
        fd_set readfds_;

        int nfds_;

};
