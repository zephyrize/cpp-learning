#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>

using namespace std;

class ThreadPool {

private:
    vector<thread> threads;
    mutex mtx;
    condition_variable condition;
    queue<function<void()>> task_queue;
    bool stop; // 一开始没加stop，导致while true 一直在循环

public:
    ThreadPool(int num_threads);
    ~ThreadPool();

    template <typename T>
    void addTask(T &&task); 

    // 在实践5中，碰到了一个问题，如果将该函数的实现放在.cpp源文件中
    // 那么会出现无法调用的问题，
    // 但是如果实现都放在类内，则可以调用。
    // template <typename T>
    // void addTask(T &&task) {
    //     {
    //         lock_guard<mutex> lock(this->mtx);
    //         task_queue.emplace(std::forward<T>(task));
    //     }
    //     // 唤醒一个线程执行任务
    //     condition.notify_one();
    // }

    /*
    为什么会出现上面这种情况？（目前还没找到一个合适的解决方案）
    原因在于,将 addTask 的函数实现放在 threadpool.cpp 中,会导致链接时找不到 addTask 的定义。
    因为:
    1. threadpool.h 中只包含了 addTask 的函数声明,没有函数定义。
    2. server.cpp 中调用了 addTask。
    3. 编译 server.cpp 生成目标文件时,会记录调用 addTask 的信息。
    4. 但链接时,需要找到 addTask 的定义,也就是函数实现的代码。
    5. 如果 addTask 的函数实现在 threadpool.cpp中,那么该文件必须参与链接,才能提供 addTask 的定义。
    6. 但是如果没有将 threadpool.cpp 编译后生成的目标文件链接进来,链接器就找不到 addTask 的定义,导致链接错误。
    
    */


};