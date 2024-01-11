cmake_minimum_required(VERSION 3.25)
project(ds_work)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(E:/ku/easyx/include)
link_directories(E:/ku/easyx/lib64)
link_libraries(libeasyx.a)
add_executable(ds_work main.cpp)


