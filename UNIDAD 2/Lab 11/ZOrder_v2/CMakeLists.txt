cmake_minimum_required(VERSION 3.23)
project(ZOrder_v2)

set(CMAKE_CXX_STANDARD 23)


find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(ZOrder_v2 main.cpp)

target_link_libraries(ZOrder_v2 sfml-system sfml-window sfml-graphics)

