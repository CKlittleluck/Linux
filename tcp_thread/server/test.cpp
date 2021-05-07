#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

struct NewConnectSockFd
{
    int newsockfd;
};

void* TestTcpStart(void* arg)
{
    pthread_detach(pthread_self());
    NewConnectSockFd* nf = (NewConnectSockFd*)arg;

     while(1)
      {
          char buf[1024] = {0};
          int ret = recv(nf->newsockfd, buf, sizeof(buf) - 1, 0);
          if(ret < 0)
          {
              perror("recv");
              close(nf->newsockfd);
              delete nf;
              return NULL;
          }

          else if(ret == 0)
          {
              printf("peer shutdown\n");
              close(nf->newsockfd);
              delete nf;
              return NULL;
          }

          printf("cli say: %s\n", buf);

          memset(buf, '\0', sizeof(buf));
          const char* str = "i am server";
          strncpy(buf, str, strlen(str));

          ret = send(nf->newsockfd, buf, strlen(buf), 0);
          if(ret < 0)
          {
              perror("send");
              close(nf->newsockfd);
              delete nf;
              return NULL;
          }
      }
     delete nf;
     return NULL;
}



int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    
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
    while(1)
    {
        int  newsockfd = accept(sockfd, NULL, NULL);
        if(newsockfd < 0)
        {
            perror("accept");
            return -1;
        }


        struct NewConnectSockFd* nscf = new NewConnectSockFd();
        nscf->newsockfd = newsockfd;

        pthread_t tid;
        ret = pthread_create(&tid, NULL, TestTcpStart, (void*)nscf);
        if(ret < 0)
        {
            delete nscf;
            perror("pthread_create");
            return -1;
        }
    }
    close(sockfd);
    return 0;
}






