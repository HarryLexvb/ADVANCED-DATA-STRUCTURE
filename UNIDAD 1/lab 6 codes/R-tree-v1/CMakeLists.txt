cmake_minimum_required(VERSION 3.23)
project(R_tree_v1)

set(CMAKE_CXX_STANDARD 23)

add_executable(R_tree_v1 main.cpp RTree.h Rectangle.h)
#add_executable(R_tree_v1 test.cpp RTree.h Rectangle.h)
