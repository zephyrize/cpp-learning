#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <vector>
#include <thread>
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

const int MAX_EVENTS = 10;
const int MAX_CLIENTS = 5;
const int SERVER_PORT = 12345;
const int NUM_CLIENTS = 5;

void setNonBlocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}

void clientTask (int client_id) {
    int client_socket, epoll_fd;
    struct sockaddr_in server_addr{};
    char buffer[1024];

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        cout << "创建客户端socket失败. Client" << client_id << endl;
        return ;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // if (inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)) <= 0) {
    //     cerr << "非法地址. Client " << client_id << endl;
    //     close(client_socket);
    //     return;
    // }

    if (connect(client_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        cerr << "连接服务端失败. Client " << client_id << endl;
        cout << strerror(errno) << endl;
        close(client_socket);
        return;
    }

    if ((epoll_fd = epoll_create1(0)) == -1) {
        cerr << "创建epoll实例失败. Client " << client_id << endl;
        close(client_socket);
        return;
    }

    struct epoll_event event{};
    event.data.fd = client_socket;
    event.events = EPOLLIN | EPOLLET;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event) == -1) {
        cerr << "添加客户端到socket模型中失败. Client " << client_id << endl;
        close(client_socket);
        close(epoll_fd);
        return;
    }

    setNonBlocking(client_socket);

    cout << "Client " << client_id << " 已连接到服务器" << endl;

    string message = "Hello server! I am Client with id: " + to_string(client_id) + ".";
    send(client_socket, message.c_str(), message.length(), 0);

    struct epoll_event events[MAX_EVENTS];
    int ready_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    for (int i = 0; i < ready_events; ++i) {
        if (events[i].data.fd == client_socket) {
            int reading_bytes = 0;
            while(true) {
                reading_bytes = read(client_socket, buffer, sizeof(buffer));
                if (reading_bytes == -1) {
                    if (errno != EAGAIN) {
                        cerr << "从服务端读取数据失败, Client " << client_id << endl;
                        close(client_socket);
                        return;
                    }
                    break;
                }
                else if (reading_bytes == 0) {
                    cout << "服务端断开连接, Client " << client_id << endl;
                    close(client_socket);
                    return;
                }
                else {
                    string response(buffer, reading_bytes);
                    cout << "客户端接收到数据, Client " << client_id << ": " << response << endl;
                }
            }
        }
    }
    close(client_socket);
    close(epoll_fd);
}


int main() {
    // clientTask(1);

    std::vector<std::thread> client_threads;
    for (int i = 0; i < NUM_CLIENTS; ++i) {
        client_threads.emplace_back(clientTask, i + 1);
    }

    for (auto &thread : client_threads) {
        thread.join();
    }

    return 0;
}


