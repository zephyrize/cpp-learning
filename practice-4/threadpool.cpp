#include <iostream>
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
    ThreadPool(int num_threads=2) : stop(false) {
        for (int i=0; i<num_threads; i++) {
            threads.emplace_back([this] {
                while (true) {
                    unique_lock<mutex> lock(this->mtx);
                    if (stop == true) {
                        break;
                    }
                    else if (task_queue.empty()) {
                        condition.wait(lock);
                    }
                    else {
                        auto task = task_queue.front();
                        task_queue.pop();
                        lock.unlock();
                        task();
                        lock.lock();
                    }
                }
            });
        }
    }
    // 使用完美转发进行优化
    template <typename T>
    void addTask(T &&task) {
        {
            lock_guard<mutex> lock(this->mtx);
            task_queue.emplace(std::forward<T>(task));
        }
        // 唤醒一个线程执行任务
        condition.notify_one();
    }

    ~ThreadPool() {
        // 先加锁然后设置stop为true
        {
            lock_guard<mutex> lock(this->mtx);
            this->stop = true;
        }
        // 析构函数，将所有还在挂起的线程唤醒，执行剩下的任务
        condition.notify_all();
        // 确保线程池中所有线程执行完毕
        for (auto &thread : this->threads) {
            thread.join();
        }
    }
};

void task1() {
    cout << "我在执行任务1" << endl;
}

void task2() {
    cout << "我在执行任务2" << endl;
}

void task3() {
    cout << "我在执行任务3" << endl;
}

void task4() {
    cout << "我在执行任务4" << endl;
}

int main() {
    ThreadPool thread_pool(4);
    thread_pool.addTask(task1);
    thread_pool.addTask(task2);
    thread_pool.addTask(task3);
    thread_pool.addTask(task4);

    this_thread::sleep_for(chrono::seconds(4));
    return 0;
}   
