cmake_minimum_required(VERSION 3.23)
project(R_tree_v2)

set(CMAKE_CXX_STANDARD 23)

add_executable(R_tree_v2 test-harness.cpp Rtree.h Rectangle.h)
