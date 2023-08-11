#include <iostream>
#include <cstring>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

using namespace std;
const int SERVER_PORT = 12345;

void readCallback(struct bufferevent* bev, void* ctx) {
    char buffer[1024];
    int reading_bytes = bufferevent_read(bev, buffer, sizeof(buffer) - 1);
    if (reading_bytes > 0) {
        buffer[reading_bytes] = '\0';
        cout << "接收到请求: " << buffer << endl;
        string response = "回应客户端：";
        bufferevent_write(bev, response.c_str(), response.length());
    }
}

void acceptCallback(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* addr, int socklen, void* ctx) {
    struct event_base* base = evconnlistener_get_base(listener);
    struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, readCallback, nullptr, nullptr, nullptr);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    cout << "新的客户端已连接. Socket fd: " << fd << endl;
}

void errorCallback(struct evconnlistener* listener, void* ctx) {
    struct event_base* base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    cerr << "监听错误: " << evutil_socket_error_to_string(err) << endl;
    event_base_loopexit(base, nullptr);
}

int main() {
    struct event_base* base = event_base_new();
    if (!base) {
        cerr << "创建event base失败." << endl;
        return 1;
    }

    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    struct evconnlistener* listener = evconnlistener_new_bind(base, acceptCallback, nullptr,
                                                              LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1,
                                                              (struct sockaddr*) &server_address,
                                                              sizeof(server_address));
    if (!listener) {
        cerr << "创建listener失败." << endl;
        event_base_free(base);
        return 1;
    }
    evconnlistener_set_error_cb(listener, errorCallback);

    cout << "服务器启动，等待连接..." << endl;
    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}