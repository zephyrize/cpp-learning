### 探索使用`shared_ptr`和`weak_ptr`来处理经典的回调执行场景:<br>

`test1.cpp`采用如下流程测试shared_ptr/weak_ptr的经典回调执行场景：任务对象智能指针加入执行队列，任务队列执行时如何判断某任务是否已经销毁（暂未实现异步队列，计划下次实现线程池时，在这里重新写一个测试代码，将任务队列添加到线程池中）。<br>

1. 定义任务对象：定义了一个`Task`类，其中包含一个回调函数和一个标识符。回调函数将在执行任务时被调用。
   
2. 创建执行队列：创建了一个`TaskQueue`类，用于管理任务的执行队列。任务对象使用`shared_ptr`进行管理，以确保在需要时可以正确地共享和管理任务的生命周期。
   
3. 添加任务：将任务对象使用`shared_ptr`添加到执行队列中。执行队列通过一个`std::queue`来存储任务。
   
4. 检查任务有效性：在执行队列中处理任务时，我们使用`weak_ptr`来检查任务是否有效。通过调用`lock()`方法，可以获取一个有效的`shared_ptr`，如果任务已被销毁，则返回一个空的`shared_ptr`。
   
5. 执行任务：对于有效的任务，调用其回调函数进行相应的操作。对于已销毁的任务，可以输出相应的信息。

**过程：**<br>

1. 在任务执行之前，将任务对象的`shared_ptr`通过引用传递到执行队列中。
   
2. 当队列中的任务准备执行时，使用`weak_ptr`的`lock()`方法尝试获取一个有效的`shared_ptr`。
   
3. 如果获取的`shared_ptr`有效，表示任务仍然存在，可以安全地执行该任务的回调函数。
   
4. 如果获取的`shared_ptr`为空，表示任务已经被销毁，可以相应地处理无效任务，输出相应的信息。

**思考：**

1. 为什么要使用`weak_ptr`判断某个任务是否被销毁？
    > 使用`weak_ptr`来判断某个任务是否被销毁的原因是为了避免访问已经销毁的对象。当一个对象被管理为`shared_ptr`时，它的生命周期由`shared_ptr`管理，当没有任何`shared_ptr`指向该对象时，对象会被销毁。
    > 
    > 使用`weak_ptr`可以避免这个问题。`weak_ptr`是一种弱引用，它可以从一个`shared_ptr`对象创建，但不会增加对象的引用计数。通过`weak_ptr`，我们可以尝试获取一个有效的`shared_ptr`来访问任务对象，如果任务对象已经被销毁，则`weak_ptr`会返回一个空的`shared_ptr`。

2. 在使用weak_ptr判断share_ptr对象是否被销毁时，`test1.cpp`中采用`lock()`的方式判断返回的是否为一个`nullptr`以此判断任务对象是否被销毁，是否可以用`weak_ptr.expired()`或者`weak_ptr.use_count()`的计数是否为0来判断`share_ptr`对象是否被销毁？
    > `use_count()函数`：`use_count()`函数用于返回与`shared_ptr`关联的引用计数，而不是用来判断对象是否被销毁。当引用计数变为零时，不一定表示对象已经被销毁，而可能是由于其他`shared_ptr`实例释放了对该对象的所有权。因此，`use_count()`并不能准确地判断对象的销毁状态。
    > 
    > `expired()函数`：`weak_ptr`的`expired()`函数是专门用于检查其所指对象是否已被销毁的成员函数。它会返回一个布尔值，指示`weak_ptr`所指对象是否有效。通过调用expired()函数，可以直接判断任务对象是否已被销毁。

------

### 写一些CAS原子操作的demo，测试一下原子锁和互斥锁的性能，形成数据报告。

在`test3.cpp`中，在线程数量分别为1、2、4、8下，执行10000, 50000, 100000, 500000, 1000000次自增操作，生成四份测试结果存放在`report_{nums}_threads.txt`中。

> 注意：每个txt文件中做了两组实验，第一组mutex操作使用以下语句测试：<br>
>   // mtx.lock();<br>
>   // counter++;<br>
>   // mtx.unlock();<br>
>   第二组mutex操作采用`lock_guard`测试：<br>
>   // std::lock_guard<std::mutex> lock(mtx);<br>
>   // counter++;<br>

**结论：**
从测试结果中，可以看出：

1. 性能上,atomic原子操作的执行时间普遍比mutex更少。

2. 当线程数量增多时,mutex互斥锁的执行时间增长更快。这是因为mutex需要进行lock/unlock操作,多线程竞争lock时会引起上下文切换,降低效率。而atomic可以无锁地进行原子操作,不需要lock,可扩展性更好。

3. 当迭代次数较小时(10万以下),两者执行时间差别不大,随着迭代次数增加,性能差距加大。

4. mutex的最大优点是可以在锁住的代码块内执行复杂的多行逻辑,而atomic一次只能保证一个简单操作的原子性。所以atomic适合简单读取/更新等场景,mutex适合需要同步复杂逻辑的场景。

5. atomic提供了比mutex更细粒度的同步控制,可以只锁住一个共享变量的访问,而mutex会锁住整个代码块。

总之，对于简单的原子操作,特别是高并发场景下,atomic能提供更好的性能和可扩展性。 但是当需要对代码块进行数据安全保护的时候,就需要选择使用锁机制了。


另外值得注意的有趣的现象是采用`lock_guard`比普通的加锁再解锁操作消耗时间更长一点，我个人猜测可能是因为标准库封装的`lock_guard`的实现更复杂，需要额外的开销，比如构造函数和析构函数的调用，并且锁的范围会限制在一个代码块的作用域内，可能会导致锁的持有时间变长吧。但是该测试环境显然不符合后者理论，因为毕竟只有一个自增操作代码，所以最有可能的原因是构造函数和析构函数的调用。

不过还是使用`lock_guard`更靠谱一些，毕竟是一个RAII封装，并且性能差异也并不明显。