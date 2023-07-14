一个cpp学习实践仓库

1. 类与对象，继承多态，指针引用，文件操作，STL用法、CMake使用和编译工程 &#9745; 
2. UML篇：类图、模块图、部署图、流程图、时序图、状态图等。项目1转为UML图 &#9745; 
3. C++11特性，lamda，function，智能指针，atomic原子操作等 &#9745; 
	1. 探索shared_ptr/weak_ptr的经典回调执行场景：任务对象智能指针加入执行队列，队列异步执行时如何判断某任务是否已经销毁。&#9745; 
	2. 写一些CAS原子操作的demo，测试一下原子锁和互斥锁的性能。&#9745; 
4. C++并行编程
	1. 同步模型：互斥锁、条件变量、信号量、消息队列
	2. 使用thread结合lamda写一个简单的线程池模型，可以添加任务，自动调度处理任务。测试线程池的并行处理速度。
5. 网络编程
	1. socket基本用法、select/poll模型、epoll模型。
	2. 使用socket模型写一个简单的客户端、服务器通讯程序，客户端可以通过网络发送请求给服务端，服务端执行完成后返回执行结果给客户端。模拟多客户端，测试一下服务端每秒最多处理几个请求。
6. libevent库使用
	1. 使用libevent改写上述程序，并测试效率进行对比。