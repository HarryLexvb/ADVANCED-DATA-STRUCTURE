cmake_minimum_required(VERSION 3.23)
project(Concurrent_Priority_Queue_V1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Concurrent_Priority_Queue_V1 main.cpp concurrent_priority_queue.h concurrent_priority_queue.h C_priority_queue.h C_vector.h)
