#include <iostream>
#include <memory>
#include <queue>
#include <thread>

using namespace std;

class Task {
public:
    using Callback = function<void(int)>;

    Task(int id, Callback callback) : id_(id), callback_(move(callback)) {}

    void execute() {
        cout << "Executing task " << id_ << endl;
        callback_(id_);
    }

private:
    int id_;
    Callback callback_;
};


class TaskQueue {
public:
    void addTask(shared_ptr<Task> task) {
        lock_guard<mutex> lock(mutex_);
        tasks_.push(task);
    }

    void processTasks() {
        while (true) {
            
            // cout<<"Processing tasks"<<endl;

            /*
            由于是顺序队列任务，这里似乎没必要加锁，因为之前写了一个异步队列没跑起来，加锁的代码先留着，有时间重新再写一个异步队列尝试一下。
            */
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

private:
    queue<shared_ptr<Task>> tasks_;
    mutex mutex_;
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