#include <mutex>
#include <thread>
#include <vector>
#include <queue>

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

};