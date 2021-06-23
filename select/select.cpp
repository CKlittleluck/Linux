#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
    fd_set readfds;
    FD_ZERO(&readfds);

    FD_SET(0, &readfds);

    int ret = select(0+1, &readfds, NULL, NULL,  NULL);
        if(ret < 0)
        {
            perror("select");
            return 0;
        }
        else if(ret == 0)
        {
            //timeout
        }

        if(FD_ISSET(0, &readfds))
        {
            char buf[1024] = {0};
            read(0, buf, sizeof(buf) - 1);
            printf("%s\n", buf);
        }
    return 0;
}
