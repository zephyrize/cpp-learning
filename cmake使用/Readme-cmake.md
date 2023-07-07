
### 1. 配置开发环境
#### 1.1 安装GCC & GDB
```sh
sudo apt update
sudo apt install build-essential gdb
```
确认安装成功：
```sh
gcc --version # gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
g++ --version # g++ (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
gdb --version # GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2
```
#### 1.2 安装CMake
```sh
sudo apt install cmake
```
确认安装成功：
```sh
cmake --version # cmake version 3.16.3
```
### 2. 重要指令汇总
- `cmake_minimum_required(VERSION 3.0)` - 指定CMake最低版本的要求
- `project` - 定义工程名字
	- project(project_name)
- `set` - 定义变量
	> 定义SRC变量，其值为 hello.cpp swap.cpp
	> set (SRC hello.cpp swap.cpp)
	
- `link_directories` - 向工程添加多个特定的库文件搜索路径---相当于指定g++编译器的`-L`参数
- `add_library` - 生成库文件
- `add_compile_options` - 添加编译参数
- `add_executable` - 生成可执行文件
- `target_link_libraries` - 为target添加需要链接的共享库
- `add_subdirectory` - 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置
- `aux_source_directory` - 将一个目录下所有的源代码文件存储到一个变量中，这个指令被用来临时自动构建源文件列表

### 3. CMake常用变量
- `CMAKE_C_FLAGS` - gcc编译选项
- `CMAKE_CXX_FLAGS` - g++编译选项
- `CMAKE_BUILD_TYPE` - 编译类型
- `CMAKE_BINARY_DIR` -  等价于 `CMAKE_BINARY_DIR`编译目录，如果是in source build，那么是工程顶层目录；如果是out-of-source dir，指的是工程编译发生的目录
- `CMAKE_SOURCE_DIR` - 等价于 `PROJECT_SOURCE_DIR`工程顶层目录
- `EXECUTABLE_OUTPUT_PATH` - 可执行文件输出的目录
- `LIBRARY_OUTPUT_PATH` - 库文件的存放路径
- `CMAKE_CXX_COMPILER` - 指定C++编译器
- `CMAKE_C_COMPILER` - 指定C编译器

### 4. CMake编译工程
CMake目录结构，项目主目录存在一个CMakeLists.txt文件。
- 内部构建 - 不推荐使用，不写了。
- 外部构建
	```sh
	# 外部构建
	# 1. 当前目录下，创建build文件夹
	mkdir build
	# 2. 进入build文件夹
	cd build
	# 3. 编辑上级目录的CMakeLists.txt，生成Makefile和其它文件
	cmake ..
	# 4. 执行make命令，生成target
	make
	```
