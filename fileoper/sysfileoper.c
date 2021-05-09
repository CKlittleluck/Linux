#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    close(0);
    int ret = open("chenkang", O_RDWR | O_CREAT, 0664);
    if(ret < 0)
    {
        perror("open");
        printf("open failed\n");
        return -1;
    }
    printf("open success ret = %d\n",ret);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
