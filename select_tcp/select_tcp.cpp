#include "my_select.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main()
{
    int listen_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listen_sockfd < 0)
    {
        perror("socket");
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    int ret = bind(listen_sockfd, (struct sockaddr*) &addr, sizeof(addr));

    if(ret < 0)
    {
        perror("bind");
        return 0;
    }

    ret = listen(listen_sockfd, 5);
    if(ret < 0)
    {
        perror("listen");
        return 0;
    }

    Myselect ms;
    ms.Addfd(listen_sockfd);

    while(1)
    {
        std::vector<int> vec;
        vec.clear();

        ret = ms.Select(&vec, NULL);
        if(ret <= 0)
        {
            continue;
        }

        for(size_t i = 0; i < vec.size(); i++)
        {
            if(vec[i] == listen_sockfd)
            {
                int newfd = accept(listen_sockfd, NULL, NULL);
                if(newfd < 0)
                {
                    perror("accept");
                    continue;
                }
                ms.Addfd(newfd);
            }
            else 
            {
                printf("newfd recv data...%d\n", vec[i]);
                char buf[1024] = {0};
                ssize_t recv_size = recv(vec[i], buf, sizeof(buf), 0);
                if(recv_size < 0)
                {
                    perror("recv");
                    continue;
                }

                else if(recv_size == 0)
                {
                    printf("peer shutdown connet\n");
                    ms.Deletefd(vec[i]);
                    close(vec[i]);
                    continue;
                }
                printf("buf is %s\n", buf);
            }
        }
    }
    return 0;
}
