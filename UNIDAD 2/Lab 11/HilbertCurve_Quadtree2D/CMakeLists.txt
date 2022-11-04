cmake_minimum_required(VERSION 3.23)
project(HilbertCurve_Quadtree2D)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(HilbertCurve_Quadtree2D main.cpp Point.h quadtree.h HOrder.h)

target_link_libraries(HilbertCurve_Quadtree2D sfml-system sfml-window sfml-graphics)