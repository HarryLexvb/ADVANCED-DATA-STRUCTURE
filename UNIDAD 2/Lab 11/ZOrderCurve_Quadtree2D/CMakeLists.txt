cmake_minimum_required(VERSION 3.23)
project(ZOrderCurve_Quadtree2D)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(ZOrderCurve_Quadtree2D main.cpp quadtree.h ZOrder.h Point.h)

target_link_libraries(ZOrderCurve_Quadtree2D sfml-system sfml-window sfml-graphics)