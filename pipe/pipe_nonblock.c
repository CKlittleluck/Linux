#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    int flag =fcntl(fd[1],F_GETFL);
    fcntl(fd[1], F_SETFL, flag | O_NONBLOCK);
    if(ret < 0)
    {
        perror("pipe");
        return -1;
    }

    ret = fork();
    if(ret < 0)
    {
        perror("fork");
        return -1;
    }
    else if(ret == 0)
    {
        close(fd[0]);
        int count = 0;
        while(1)
        {
            ssize_t w_size = write(fd[1], "h", 1);
            if(w_size < 0)
                 {
                    perror("write");
                    return -1;
                }
            count++;
            printf("count :%d\n", count);
        }
        //return 0;
    }

    else
    {
        close(fd[0]);
        while(1)
        {
            sleep(1);
        }
        //return 0;
    }

    return 0;
}
