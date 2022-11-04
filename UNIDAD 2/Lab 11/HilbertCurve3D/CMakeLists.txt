cmake_minimum_required(VERSION 3.23)
project(HilbertCurve3D)

set(CMAKE_CXX_STANDARD 23)


find_package(GLUT)

add_executable(HilbertCurve3D main.cpp hilbert.cpp hilbert.h)


target_link_libraries(HilbertCurve3D GLUT::GLUT -lopengl32 -g -lfreeglut -lglu32)