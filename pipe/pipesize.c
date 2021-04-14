#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return -1;
    }

    int count = 0;

    while(1)
    {
        ssize_t w_size = write(fd[1], "h", 1);
        if(w_size != 1)
        {
            break;
        }

        count++;
        printf("count:%d\n", count);
    }
    return 0;
}
