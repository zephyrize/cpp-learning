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

    cout<< "开启服务成功，等待客户端连接..." << endl;
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

        for (int i = 0; i < ready_events; ++i) {
            // 服务器套接字上发生了EPOLLIN事件，有新的客户端到达
            if (events[i].data.fd == server_socket_fd_) {
                addClient();
            }
            // 关闭客户端
            else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)){
                
            }
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
    cout<< "处理读事件" << endl;
    char buffer[1024];
    int reading_bytes = 0;
    // string request_body;
    while (true) {
        reading_bytes = read(client_fd, buffer, sizeof(buffer));
        if (reading_bytes <= 0) {
            if (errno != EAGAIN) {
                closeSocket(client_fd);
            }
            break ;
        }
        client_info_[client_fd].append(buffer, reading_bytes);
    }
    cout << "客户端, Socket id: " << client_fd << "的传输内容为: " \
         << client_info_[client_fd] << endl;

    epollModFd(client_fd, EPOLLOUT | EPOLLET);
    
}

void Server::writeEvent(int client_fd) {
    cout<< "处理写事件" << endl;
    string response = "来自服务端: 收到收到, over!";
    int w_res = write(client_fd, response.c_str(), response.length());
    if (w_res < 0) {
        cout << "返回信息给客户端失败, Socket fd: " << client_fd << endl;
        close(client_fd);
        closeSocket(client_fd);
    }
    cout << "返回数据给客户端(Socket id:)" << client_fd << "成功！" << endl;
    closeSocket(client_fd);
}

void Server::processWriteEvent(int client_fd) {
    threadpool_->addTask([this, client_fd]() {
        writeEvent(client_fd);
    });
}

void Server::closeSocket(int client_fd) {
    epollDelFd(client_fd);
    delClient(client_fd);
}

void setNonBlocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}


int main () {
    Server server;

    server.run();
}