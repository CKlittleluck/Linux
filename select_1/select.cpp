#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>



int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("sockfd");
        return 0;
    }

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(18889);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    listen(sockfd, 5);
        

    fd_set readfds;
    FD_ZERO(&readfds);

    FD_SET(0, &readfds);
    FD_SET(sockfd, &readfds);


    while(1)
    {
        struct timeval tv;
        tv.tv_sec = 6;
        tv.tv_usec = 0;

        fd_set tmp = readfds;
        int ret = select(sockfd + 1, &tmp, NULL, NULL, &tv);

        if(ret < 0)
        {
            perror("select");
            return 0;
        }

        else if(ret == 0)
        {
            //timeout
            ret = FD_ISSET(0, &tmp);
            printf("0 ret = %d\n", ret);

            ret = FD_ISSET(sockfd, &tmp);
            printf("sockfd ret =%d\n", ret);

            printf("%d - %d\n", tv.tv_sec , tv.tv_usec);
            continue;
        }

        if(!FD_ISSET(sockfd, &tmp))
        {
            printf("sockfd is not in readfds\n");
        }
        else
        {
            printf("sockfd is in tmp\n");
        }
    }
    return 0;
}
