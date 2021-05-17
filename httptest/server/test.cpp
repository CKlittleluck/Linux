#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("using \"./test_http [ip] [port]\"\n");
        return -1;
    }

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("ip.c_str()");
    
    int ret = bind(sockfd,(struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }

    ret = listen(sockfd, 5);
    if(ret < 0)
    {
        perror("listen");
        return -1;
    }
    
        int  newsockfd = accept(sockfd, NULL, NULL);
        if(newsockfd < 0)
        {
            perror("accept");
            return -1;
        }
        while(1)
        {
        char buf[1024] = {0};
        ret = recv(newsockfd, buf, sizeof(buf) - 1, 0);
        if(ret < 0)
        {
              perror("recv");
              return -1;
        }

        else if(ret == 0)
        {
            printf("peer shutdown\n");
            close(newsockfd);
            close(sockfd);
            return 0;
        }

        printf("chorme say: %s\n", buf);

        std::string body = "<html><h1>hello</h1></html>";

          memset(buf, '\0', sizeof(buf));
          snprintf(buf, sizeof(buf) - 1, "%s %s %s\r\ncontent-type: text/html\r\ncontent-length:%lu\r\n\r\n","HTTP1.1","200", "ok", body.size());

       // sleep(2);


        ret = send(newsockfd, buf, strlen(buf), 0);
        if(ret < 0)
        {
            perror("send");
            return 0;
        }


        ret = send(newsockfd, body.c_str(), body.size(), 0);
        if(ret < 0)
        {
            perror("send");
            return 0;
        }


       // ret = send(newsockfd, buf, strlen(buf), 0);
       //    if(ret < 0)
       //     {
       //         perror("send");
       //         return -1;
       //     }
    }
   close(newsockfd);
   close(sockfd);
    return 0 ;
}

