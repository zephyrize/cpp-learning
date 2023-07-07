cmake_minimum_required(VERSION 3.0)
project(Practice-1)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置输出目录为 build 文件夹
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
# 添加头文件搜索路径
include_directories(include())


# 添加可执行文件
add_executable(my_cmake_exe
    src/main.cpp 
    src/shape.cpp 
    src/rectangle.cpp 
    src/circle.cpp 
    src/color.cpp 
    src/shape_container.cpp 
    src/file_manager.cpp
)

# 主目录构建并编译项目
# cmake -B build
# cmake --build build 或者进入到build文件夹下直接使用命令 make

