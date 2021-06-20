#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>

#include "httplib.h"

//void http_callback_func(const httplib::Request & requ, httplib:: Response & resp)
//{
//    (void) requ;
//    std::string str = "<html><h1>chenkangjiayou</h1></html>";
//    resp.set_content(str.c_str(), str.size(), "test/html");
//}

int g_count = 0;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("using ./http_svr [port] [num]\n");
        return 0;
    }

    uint16_t port = atoi(argv[1]);
    std::string num = argv[2];

    httplib::Server svr;
    svr.Get("/aaa", [num](const httplib::Request & requ, httplib:: Response & resp){

            (void) requ;

            char buf[1034] = {0};
            snprintf(buf, sizeof(buf) - 1, "<html><h1>i am httpsvr : %s , i am recv request num is : %d </h1></html>", num.c_str(),++g_count);
            resp.set_content(buf, strlen(buf), "test/html");
            });

    svr.listen("0.0.0.0", port);
    return 0;
}

