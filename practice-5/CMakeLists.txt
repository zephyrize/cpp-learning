cmake_minimum_required(VERSION 3.0)
project(Practice-5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(server_exe
    server.cpp
)

add_executable(client_exe
    client.cpp
)

target_link_libraries(server_exe pthread)
target_link_libraries(client_exe pthread)