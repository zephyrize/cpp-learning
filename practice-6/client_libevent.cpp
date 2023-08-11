#include <iostream>
#include <vector>
#include <cstring>
#include <thread>
#include <arpa/inet.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

using namespace std;

constexpr int SERVER_PORT = 12345;
constexpr int NUM_CLIENTS = 5;

void readCallback(struct bufferevent* bev, void* ctx) {
    struct evbuffer* input_buffer = bufferevent_get_input(bev);
    size_t len = evbuffer_get_length(input_buffer);
    if (len > 0) {
        char* buffer = new char[len + 1];
        evbuffer_remove(input_buffer, buffer, len);
        buffer[len] = '\0';
        cout << "收到回应: " << buffer << endl;
        delete[] buffer;
    }
}

void writeCallback(struct bufferevent* bev, void* ctx) {
    string request = "Request from client";
    bufferevent_write(bev, request.c_str(), request.length());
}

void eventCallback(struct bufferevent* bev, short events, void* ctx) {
    if (events & BEV_EVENT_CONNECTED) {
        cout << "已连接到服务端." << endl;
        bufferevent_trigger(bev, EV_WRITE, 0);
    } else if (events & (BEV_EVENT_ERROR | BEV_EVENT_EOF)) {
        if (events & BEV_EVENT_ERROR) {
            int err = EVUTIL_SOCKET_ERROR();
            cerr << "错误: " << evutil_socket_error_to_string(err) << endl;
        }
        bufferevent_free(bev);
    }
}

void connectToServer() {
    struct event_base* base = event_base_new();
    if (!base) {
        cerr << "创建event base失败." << endl;
        return;
    }

    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &(server_address.sin_addr)) <= 0) {
        cerr << "非法地址." << endl;
        return;
    }

    struct bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, readCallback, nullptr, eventCallback, nullptr);
    if (bufferevent_socket_connect(bev, (struct sockaddr*) &server_address, sizeof(server_address)) == 0) {
        event_base_dispatch(base);
    }

    bufferevent_free(bev);
    event_base_free(base);
}

int main() {
    vector<thread> client_threads;

    // 创建多个客户端线程
    for (int i = 0; i < NUM_CLIENTS; ++i) {
        client_threads.emplace_back(connectToServer);
    }

    // 等待客户端线程完成
    for (auto& thread : client_threads) {
        thread.join();
    }

    return 0;
}
