#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
// #include "../practice-4/threadpool.h"
#include "../practice-4/threadpool-improved.cpp"

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <unordered_map>


class Server {

private:
    const int PORT = 12345;
    const int MAX_CLIENTS = 6;
    const int MAX_EVENTS = 6;

    // struct epoll_event event{};
    struct sockaddr_in server_addr{}, client_addr{};
    socklen_t client_addr_size = sizeof(client_addr);

    int server_socket_fd_;
    int epoll_fd_;
    std::string buffer_;

    std::vector<int> connected_clients_;
    std::unordered_map<int, std::string> client_info_;
    std::unique_ptr<ThreadPool> threadpool_;

    // using Task = std::function<void()>;
public:

    Server();

    /*
    server 相关
    */
    // 初始化server
    bool initSocket();
    // 关闭server
    void closeSocket();
    //运行server
    void run();

    /*
    epoll 相关
    */
    // 创建epoll实例
    bool epollCreateInstance();
    // epoll添加fd
    bool epollAddFd(int fd, uint32_t event);

    /*
    client相关
    */
    // 添加客户端
    void addClient();
    void delClient(int);

    void processReadEvent(int);
    void processWriteEvent(int);
    void writeEvent(int);
    void readEvent(int);
    
    
};