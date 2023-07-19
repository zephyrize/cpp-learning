/*
线程池改进版，可以为task传入不定参数
优化构造函数

其实只是代码的优化，经测试，性能并没有太大提升。
*/

#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>

using namespace std;
class ThreadPool {
private:
    vector<thread> threads;
    queue<function<void()>> tasks;
    mutex queue_mutex;
    condition_variable condition;
    bool stop;

public:
    ThreadPool(int num_threads) : stop(false) {
        /*
        这里测试使用四个线程
        构造函数开始执行，对于每个线程，设置一个死循环，循环体为不断地从任务队列中获取任务并执行。
        如果任务队列为空，或者没有接收到线程池终止的信号（stop），则阻塞线程，在该处等待。
        */
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(
                [this] {
                    while (true) {
                        function<void()> task;
                        {
                            unique_lock<mutex> lock(queue_mutex);
                            condition.wait(lock, [this] { return stop || !tasks.empty(); });
                            if (stop && tasks.empty())
                                return;
                            task = std::move(tasks.front());
                            tasks.pop();
                        }
                        task();
                    }
                }
            );
        }
    }

    template<class F, class... Args>
    void addTask(F&& f, Args&&... args) {
        // 完美转发
        auto task = bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            unique_lock<mutex> lock(queue_mutex);
            tasks.emplace(task);
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (auto& thread : threads)
            thread.join();
    }
};

// 测试任务
// void task(int id) {
//     cout << "Task " << id << " started" << endl;
//     // 任务实体
//     for (int i = 0; i < 2; ++i) {
//         cout << "I am doing Task " << id << " for " << i << endl;
//     }
//     cout << "Task " << id << " completed" << endl;
// }

// int main() {
//     // 创建一个包含6个线程的线程池
//     ThreadPool thread_pool(6);

//     // 添加任务到线程池
//     for (int i = 0; i < 6; ++i) {
//         thread_pool.addTask(task, i);
//     }

//     // 等待任务完成
//     this_thread::sleep_for(chrono::seconds(4));

//     return 0;
// }


void task (int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += sqrt(i);
    }
    // cout << sum << endl;
}

int main() {
    // ThreadPool thread_pool(4);
    // thread_pool.addTask(task1);
    // thread_pool.addTask(task2);
    // thread_pool.addTask(task3);
    // thread_pool.addTask(task4);

    // this_thread::sleep_for(chrono::seconds(4));

    ofstream outfile("report.csv");

    for (int num_threads = 1; num_threads <= 8; num_threads*=2) {
        
        // 记录执行时间
        auto start = chrono::high_resolution_clock::now();

        {
            ThreadPool pool(num_threads);
            int num_tasks = 8;

            for (int i = 0; i < num_tasks; i++) {
                pool.addTask([=] { task(1e8); }); 
            }
        }   

        // pool.addTask([] {});
        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        outfile << num_threads << "," << duration.count() << endl;
        cout << num_threads << " threads: " << duration.count() << " ms" << endl;
        
    }
    
    outfile.close();

    return 0;
}