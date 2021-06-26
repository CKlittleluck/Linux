#include <stdio.h>
#include <poll.h>
#include <unistd.h>

int main()
{
    struct pollfd arr[10];

    arr[0].fd = 0;
    arr[0].events = POLLIN;

    int ret = poll(arr, 1, -1);
    if(ret < 0)
    {
        perror("poll");
        return 0;
    }

    for(int i = 0; i < 10; i++)
    {
        if(arr[i].revents == POLLIN)
        {
            printf("fd is %d\n", arr[i].fd);
            char buf[1024] = {0};

            read(arr[i].fd, buf, sizeof(buf) - 1);
            printf("buf : %s\n", buf);
        }
    }
    return 0;
}
