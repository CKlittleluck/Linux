#include "../udp.hpp"

#define CHECK_RET(p) if(p < 0) {return -1;}

int main()
{
    UdpApi ua;
    CHECK_RET(ua.CreatSocket());
    CHECK_RET(ua.Bind("0.0.0.0", 19999));

    while(1)
    {
        std::string data;
        struct sockaddr_in peer_addr;
        socklen_t peer_len = sizeof(peer_addr);
        ua.RecvData(&data, &peer_addr, &peer_len);

        printf("cil say : %s\n", data.c_str());

        data.clear();

        printf("please enter resp:");
        fflush(stdout);
        std::cin >> data;

        ua.SendData(data, &peer_addr, peer_len);
    }
    ua.Close();
    return 0 ;

}












#if 0
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
using namespace std;


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
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("172.17.0.12");

    int ret = bind(sockfd, (struct sockaddr*) & addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }

    while(1)
    {
        char buf[1024] = {0};
        struct sockaddr_in peer_addr;
        socklen_t peer_len = sizeof(peer_addr);
        ssize_t ret = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&peer_addr, &peer_len);
        if(ret < 0)
        {
            perror("recvfrom");
            return -1;
        }

        printf("cil say: %s\n", buf);

        memset(buf, '\0', sizeof(buf));
        printf("please enter resp:");
        fflush(stdout);
        cin >> buf;
        ssize_t send_size = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&peer_addr, peer_len);
        if(send_size < 0)
        {
            perror("sento");
            return -1;
        }

    }
    close(sockfd);
    return 0;
}

#endif
