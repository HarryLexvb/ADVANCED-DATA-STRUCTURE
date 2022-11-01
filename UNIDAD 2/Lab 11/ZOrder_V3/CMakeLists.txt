cmake_minimum_required(VERSION 3.23)
project(ZOrder_V3)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(ZOrder_V3 main.cpp)

target_link_libraries(ZOrder_V3 sfml-system sfml-window sfml-graphics)
