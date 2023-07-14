#include <iostream>
#include <memory>
#include <queue>
#include <thread>

class Task {
public:
    using Callback = std::function<void(int)>;

    Task(int id, Callback callback) : id_(id), callback_(std::move(callback)) {}

    void execute() {
        std::cout << "Executing task " << id_ << std::endl;
        callback_(id_);
    }

private:
    int id_;
    Callback callback_;
};


class TaskQueue {
public:
    void addTask(std::shared_ptr<Task> task) {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.push(task);
    }

    void processTasks() {
        while (true) {
            
            // std::cout<<"Processing tasks"<<std::endl;

            /*
            由于是顺序队列任务，这里似乎没必要加锁，因为之前写了一个异步队列没跑起来，加锁的代码先留着，有时间重新再写一个异步队列尝试一下。
            */
            std::weak_ptr<Task> task;

            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (tasks_.empty()) {
                    break;
                }
                task = tasks_.front();
                tasks_.pop();
            }

            // std::cout << task.use_count() << std::endl;

            // 使用weak_ptr判断任务是否有效
            if (auto sharedTask = task.lock()) {
                sharedTask->execute();
            } else {
                std::cout << "Task has been destroyed." << std::endl;
            }
        }
    }

private:
    std::queue<std::shared_ptr<Task>> tasks_;
    std::mutex mutex_;
};

int main() {

    TaskQueue queue;

    // 添加任务1到任务队列中
    auto task1 = std::make_shared<Task>(1, [](int id) {
        std::cout << "Callback for task " << id << std::endl;
    });
    queue.addTask(std::ref(task1));

    // 添加任务2到队列任务中，但是该任务创建完成加入队列后就销毁
    {
        auto task2 = std::make_shared<Task>(2, [](int id) {
            std::cout << "Callback for task " << id << std::endl;
        });

        queue.addTask(std::ref(task2));

        // 输出任务已销毁信息
        task2.reset();
    }

    // 添加任务3到任务队列
    auto task3 = std::make_shared<Task>(3, [](int id) {
        std::cout << "Callback for task " << id << std::endl;
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