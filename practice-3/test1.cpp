#include <iostream>
#include <memory>
#include <queue>
#include <thread>

using namespace std;

using Callback = function<void(int)>;

class Task {
private:
    int id_;
    Callback callback_;

public:
    Task(int id, Callback callback) : id_(id), callback_(std::move(callback)) {}

    void execute() {
        cout << "Executing task " << id_ << endl;
        callback_(id_);
    }
};


class TaskQueue {

private:
    queue<shared_ptr<Task>> tasks_;
    mutex mutex_;

public:
    void addTask(shared_ptr<Task> task) {
        lock_guard<mutex> lock(mutex_);
        tasks_.push(task);
    }

    void processTasks() {
        while (true) {
            
            // cout<<"Processing tasks"<<endl;

            weak_ptr<Task> task;

            {
                lock_guard<mutex> lock(mutex_);
                if (tasks_.empty()) {
                    break;
                }
                task = tasks_.front();
                tasks_.pop();
            }

            // cout << task.use_count() << endl;

            // 使用weak_ptr判断任务是否有效
            if (auto sharedTask = task.lock()) {
                sharedTask->execute();
            } else {
                cout << "Task has been destroyed." << endl;
            }
        }
    }
};

int main() {

    TaskQueue queue;

    // 添加任务1到任务队列中
    auto task1 = make_shared<Task>(1, [](int id) {
        cout << "Callback for task " << id << endl;
    });
    queue.addTask(ref(task1));

    // 添加任务2到队列任务中，但是该任务创建完成加入队列后就销毁
    {
        auto task2 = make_shared<Task>(2, [](int id) {
            cout << "Callback for task " << id << endl;
        });

        queue.addTask(ref(task2));

        // 输出任务已销毁信息
        task2.reset();
    }

    // 添加任务3到任务队列
    auto task3 = make_shared<Task>(3, [](int id) {
        cout << "Callback for task " << id << endl;
    });
    queue.addTask(task3);

    // 执行任务队列
    queue.processTasks();

    // std::thread worker([&]() {
    //     queue.processTasks();
    // });
    // worker.join();

    // vector<thread> workers;
    // for (int i = 0; i < 3; i++) {
    //     workers.emplace_back([&]() {
    //         queue.processTasks();
    //     });
    // }
    // for (auto& worker : workers) {
    //     worker.join();
    // }

    return 0;
}


/*
输出:
Executing task 1
Callback for task 1
Task has been destroyed.
Executing task 3
Callback for task 3
*/