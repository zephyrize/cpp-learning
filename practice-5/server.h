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
    const int SERVER_PORT = 12345;
    const int MAX_CLIENTS = 10;
    const int MAX_EVENTS = 100;

    // struct epoll_event event{};
    struct sockaddr_in server_addr_{}, client_addr_{};
    socklen_t client_addr_size = sizeof(client_addr_);

    int server_socket_fd_;
    int epoll_fd_;
    std::string buffer_;

    std::vector<int> connected_clients_;
    std::unordered_map<int, std::string> client_info_;
    int num_users_;
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
    void closeSocket(int);
    //运行server
    void run();

    /*
    epoll 相关
    */
    // 创建epoll实例
    int epollCreateInstance();
    // epoll添加fd
    bool epollAddFd(int fd, uint32_t event);
    bool epollModFd(int fd, uint32_t event);
    bool epollDelFd(int fd);

    /*
    client相关
    */
    // 添加客户端
    void addClient();
    // 删除客户端
    void delClient(int);

    /*
    读写事件相关
    */
    void processReadEvent(int);
    void processWriteEvent(int);
    void writeEvent(int);
    void readEvent(int);
    
};