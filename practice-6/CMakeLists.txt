cmake_minimum_required(VERSION 3.0)
project(Practice-6)

# find_package(libevent REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LIBRARIES_TO_LINK pthread event)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(server_exe
    server_libevent.cpp
)

add_executable(client_exe
    client_libevent.cpp
)

target_link_libraries(server_exe PRIVATE ${LIBRARIES_TO_LINK})
target_link_libraries(client_exe PRIVATE ${LIBRARIES_TO_LINK})