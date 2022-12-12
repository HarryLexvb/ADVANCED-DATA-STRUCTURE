cmake_minimum_required(VERSION 3.23)
project(Concurrent_Priority_Queue_V2)

set(CMAKE_CXX_STANDARD 23)

add_executable(Concurrent_Priority_Queue_V2 main.cpp Concurrent_PriorityQueue Lock_Free_SkipList.h)
