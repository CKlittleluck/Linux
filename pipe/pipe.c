#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return -1;
    }
    printf("fd[0]:%d\n",fd[0]);
    printf("fd[1]:%d\n",fd[1]);

    ret = fork();
    if(ret < 0)
    {
        perror("fork");
        return 0;
    }
    else if(ret == 0)
    {
        close(fd[0]);
        write(fd[1], "linux so easy!!!", 16);
        //return 0;
    }

    else
    {
        close(fd[1]);
        sleep(2);
        char buf[1024] = {0};
        read(fd[0], buf, sizeof(buf) - 1);
        printf("father：buf is %s\n", buf);

        //memset(buf, '\0', sizeof(buf));

        read(fd[0], buf, sizeof(buf) - 1);
        printf("father22：buf is %s\n", buf);
        //return 0;
    }

    while(1)
    {
        sleep(1);
    }
    return 0;
}
