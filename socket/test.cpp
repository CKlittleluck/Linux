#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1; 
    }


    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("172.17.0.12");

    int ret = bind(sockfd, (struct sockaddr*) & addr, sizeof(addr));

    if(ret < 0)
    {
        perror("bind");
        return -1;
    }

    while(1)
    {
        sleep(1);
    }
    return 0;
}
