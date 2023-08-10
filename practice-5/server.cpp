#include "server.h"

using namespace std;

void setNonBlocking(int);

Server::Server() {
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(SERVER_PORT);
    server_addr_.sin_addr.s_addr = INADDR_ANY;
    memset(server_addr_.sin_zero, '\0', sizeof(server_addr_.sin_zero));

    threadpool_ = std::make_unique<ThreadPool>(8);

    bool is_created = initSocket();
    if (is_created == false) {
        cout << "初始化启动服务失败..." << endl;
    }
}

bool Server::initSocket() {
    // create
    server_socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_fd_ < 0) {
        cout << "创建socket失败." << endl;
        return false;
    }

    // set sock opt
    int re_use = 1;
    int sock_opt = setsockopt(server_socket_fd_, SOL_SOCKET, SO_REUSEADDR, &re_use, sizeof(re_use));
    if (sock_opt < 0) {
        cout << "设置socket选项失败." << endl;
        close(server_socket_fd_);
        return false;
    }

    // bind
    int bind_res = bind(server_socket_fd_, (struct sockaddr *) &server_addr_, sizeof(server_addr_));
    if (bind_res < 0) {
        cerr << "绑定socket失败." << endl;
        close(server_socket_fd_);
        return false;
    }

    // listen
    int listen_res = listen(server_socket_fd_, MAX_CLIENTS);
    if (listen_res < 0) {
        cout << "监听失败." << endl;
        close(server_socket_fd_);
        return false;
    }

    epoll_fd_ = epollCreateInstance();
    if (epoll_fd_ < 0) {
        cout << "创建Epoll实例失败." << endl;
        close(server_socket_fd_);
        return false;
    }

    if (epollAddFd(server_socket_fd_, EPOLLIN | EPOLLET) == false) {
        cout << "添加server socket失败." << endl;
        close(server_socket_fd_);
        close(epoll_fd_);
        return false;
    }
    setNonBlocking(server_socket_fd_);
    cout << "开启服务成功，等待客户端连接..." << endl;
    cout << "server_socket_fd_: " << server_socket_fd_ << endl;
    return true;
}

int Server::epollCreateInstance() {
    return epoll_create1(0);
}

bool Server::epollAddFd(int fd, uint32_t ev) {
    if (fd < 0) return false;

    struct epoll_event event = {0};
    event.data.fd = fd;
    event.events = ev;
    int add_res = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event);
    if (add_res < 0) {
        cout << strerror(errno) << endl;
        return false;
    }
    return true;
}

bool Server::epollModFd(int fd, uint32_t ev) {
    if(fd < 0) return false;
    epoll_event event = {0};
    event.data.fd = fd;
    event.events = ev;
    return epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event) == 0;
}

bool Server::epollDelFd(int fd) {
    if (fd < 0) return false;
    struct epoll_event event = {0};
    return epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &event) == 0;
}

void Server::run() {
    while (true) {
        struct epoll_event events[MAX_EVENTS];
        int ready_events = epoll_wait(epoll_fd_, events, MAX_EVENTS, -1);
        // cout << "ready_events: " << ready_events << endl;
        for (int i = 0; i < ready_events; ++i) {
            // 服务器套接字上发生了EPOLLIN事件，有新的客户端到达
            cout << "---当前fd为: " << events[i].data.fd << "---" << endl;
            if (events[i].data.fd == server_socket_fd_) {
                addClient();
            }
            // 关闭客户端
            // else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)){
            // }
            // 读事件
            else if (events[i].events & EPOLLIN) {
                // cout << "触发读事件 " << endl;
                processReadEvent(events[i].data.fd);
            }
            // 写事件
            else if (events[i].events & EPOLLOUT) {
                // cout << "触发写事件 " << endl;
                processWriteEvent(events[i].data.fd);
            }
            else {
                cout << "监听事件发生了错误." << endl;
            }
        }
    }
    close(server_socket_fd_);
    close(epoll_fd_);

}

// 添加客户端
void Server::addClient() {
    struct sockaddr_in client_addr{};
    socklen_t client_addr_len = sizeof(struct sockaddr_in);
    
    int client_fd = accept(server_socket_fd_, (struct sockaddr *) &client_addr, &client_addr_len);
    if (client_fd < 0) {
        cout << "连接客户端失败" << endl;
        return ;
    }
    //设置非阻塞模式
    setNonBlocking(client_fd);

    if (epollAddFd(client_fd, EPOLLIN | EPOLLET) == false) {
        cerr << "添加客户端socket失败." << endl;
        close(client_fd);
    }
    else {
        cout << "添加客户端(Socket id: " << client_fd << ")成功." <<endl;
        connected_clients_.emplace_back(client_fd);
    }
}

void Server::delClient(int client_fd) {
    auto it = std::remove(connected_clients_.begin(), connected_clients_.end(), client_fd);
    connected_clients_.erase(it, connected_clients_.end());
    client_info_.erase(client_fd);
}

void Server::processReadEvent(int client_fd) {
    // threadpool_->addTask(std::move(std::function<void()>([this, client_fd]() {
    //     readEvent(client_fd);
    // })));
    
    // threadpool_->addTask(std::bind(&Server::readEvent, this, client_fd));
    
    threadpool_->addTask([this, client_fd]() {
        readEvent(client_fd);
    });
}

void Server::readEvent(int client_fd) {
    // cout<< "处理读事件" << endl;
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int reading_bytes = recv(client_fd, buffer, sizeof(buffer), 0);
    if (reading_bytes > 0) {
        client_info_[client_fd].append(buffer, reading_bytes);
    }
    else if (reading_bytes == 0) {
        cout << "客户端已断开连接. Socket id: " << client_fd << endl; 
    }
    else {
        cout << "recv 错误!" << strerror(errno) << endl;
    }

    cout << "客户端, Socket id: " << client_fd << "的传输内容为: " \
         << client_info_[client_fd] << endl;

    // epollModFd(client_fd, EPOLLOUT | EPOLLET);
    writeEvent(client_fd);
}

void Server::writeEvent(int client_fd) {
    // cout<< "处理写事件" << endl;
    string response = "Hello client! I am Sever!";
    ssize_t sent_bytes = send(client_fd, response.c_str(), response.size(), 0);
    if (sent_bytes == -1) {
        cout << "发送数据到客户端(Socket id:" << client_fd << ")失败！" << endl;
    }
    else if (sent_bytes != static_cast<ssize_t>(response.size())) {
        cout << "所有数据未全部发送成功(Socket id:" << client_fd << ")" << endl;
    }
    else {
        cout << "返回数据给客户端(Socket id:" << client_fd << ")成功！" << endl;
    }
    closeSocket(client_fd);
}

void Server::processWriteEvent(int client_fd) {
    threadpool_->addTask([this, client_fd]() {
        writeEvent(client_fd);
    });
}

void Server::closeSocket(int client_fd) {
    cout << "关闭客户端(fd: " << client_fd << ")" << endl;
    epollDelFd(client_fd);
    // cout << "红黑树上删除client fd: " << client_fd << endl;
    delClient(client_fd);
    // cout << "删除client相关信息client fd: " << client_fd << endl;
    close(client_fd);
    cout << "调用close函数关闭client fd: " << client_fd << endl;

}

void setNonBlocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}


int main () {
    Server server;
    server.run();
}