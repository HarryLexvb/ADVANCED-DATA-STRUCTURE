cmake_minimum_required(VERSION 3.23)
project(Priority_Queue)

set(CMAKE_CXX_STANDARD 17)

add_executable(Priority_Queue main.cpp C_vector.h C_priority_queue.h tests.h)
