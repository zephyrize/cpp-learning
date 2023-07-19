#include <iostream>
#include <fstream>
#include "threadpool.h"

using namespace std;

ThreadPool::ThreadPool(int num_threads) : stop(false) {
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([this] {
            while (true) {
                unique_lock<mutex> lock(this->mtx);
                
                /*
                写的第一个版本，判断的逻辑有点问题
                */
                // if (stop == true) {
                //     break;
                // }
                // else if (task_queue.empty()) {
                //     condition.wait(lock);
                // }
                // else {
                //     auto task = task_queue.front();
                //     task_queue.pop();
                //     lock.unlock();
                //     task();
                //     lock.lock();
                // }

                /*
                上面的逻辑问题 主要表现在 析构函数会在线程完成所有任务前把ThreadPool释放掉。
                */
                if (!task_queue.empty()) {
                    auto task = task_queue.front();
                    task_queue.pop();
                    lock.unlock();
                    task();
                    lock.lock();
                }
                else if (stop == true) {
                    break;
                }
                else {
                    condition.wait(lock);
                }

            } 
        });
    }
}

ThreadPool::~ThreadPool() {
    // 先加锁然后设置stop为true
    {
        lock_guard<mutex> lock(mtx);
        stop = true;
    }
    // 析构函数，将所有还在挂起的线程唤醒，执行剩下的任务
    condition.notify_all();
    // 确保线程池中所有线程执行完毕
    for (auto &thread : threads) {
        thread.join();
    }
}

template <typename T>
void ThreadPool::addTask(T &&task) {
    {
        lock_guard<mutex> lock(this->mtx);
        task_queue.emplace(std::forward<T>(task));
    }
    // 唤醒一个线程执行任务
    condition.notify_one();
}

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

void task (int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += sqrt(i);
    }
}

int main() {
    // ThreadPool thread_pool(4);
    // thread_pool.addTask(task1);
    // thread_pool.addTask(task2);
    // thread_pool.addTask(task3);
    // thread_pool.addTask(task4);

    // this_thread::sleep_for(chrono::seconds(4));

    ofstream outfile("report.csv");

    for (int num_threads = 1; num_threads <= 16; num_threads+=1) {
        
        // 记录执行时间
        auto start = chrono::high_resolution_clock::now();

        {
            ThreadPool pool(num_threads);
            int num_tasks = 8;

            for (int i = 0; i < num_tasks; i++) {
                pool.addTask([=] { task(1e8); }); 
            }
        }
        
        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        outfile << num_threads << "," << duration.count() << endl;
        cout << num_threads << " threads: " << duration.count() << " ms" << endl;
        
    }
    
    outfile.close();

    return 0;
}