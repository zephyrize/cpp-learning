#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <fstream>

using namespace std;

atomic<int> counter(0);
mutex mtx;

void atomic_increment(int num) {
    for (int i = 0; i < num; i++) {
        counter.fetch_add(1);
    }
}

void mutex_increment(int num) {
    for (int i = 0; i < num; i++) {
        // mtx.lock();
        // counter++;
        // mtx.unlock();

        std::lock_guard<std::mutex> lock(mtx);
        counter++;
    }
}

int main() {

    const int num_tests = 5;
    const int increments[] = {10000, 50000, 100000, 500000, 1000000};

    for (int i = 0; i < num_tests; i++) {

        int num_threads[] = {1, 2, 4, 8};
        int num_increments = increments[i];

        for (int j = 0; j < 4; j++) {
            
            int num_thread = num_threads[j];
            
            // 原子操作测试
            auto t1 = chrono::high_resolution_clock::now();

            vector<thread> threads;
            for (int k = 0; k < num_thread; k++) {
                threads.push_back(thread(atomic_increment, num_increments / num_thread));
            }
            for (auto &t : threads) {
                t.join();
            }

            auto t2 = chrono::high_resolution_clock::now();
            auto atomic_time = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();

            // 互斥锁测试
            t1 = chrono::high_resolution_clock::now();

            threads.clear();
            for (int k = 0; k < num_thread; k++) {
                threads.push_back(thread(mutex_increment, num_increments / num_thread));
            }
            for (auto &t : threads) {
                t.join();
            }

            t2 = chrono::high_resolution_clock::now();
            auto mutex_time = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();

            // 生成报告
            ofstream report("report_" + to_string(num_thread) + "_threads.txt", ios::app);
            report << "Test " << i + 1 << ": " << num_increments << " increments" << endl;
            report << "Threads: " << num_thread << endl;
            report << "Atomic time: " << atomic_time << " ms" << endl;
            report << "Mutex time: " << mutex_time << " ms" << endl
                   << endl;
        }
    }

    return 0;
}