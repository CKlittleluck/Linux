#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd = open("./ck", O_RDWR | O_CREAT, 0664);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }
    write(1,"before dup2i\0", 12);
    printf("dup2 \n");

    dup2(fd, 1);
    write(1,"hahaha", 6);
    return 0;


}
