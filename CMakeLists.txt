cmake_minimum_required(VERSION 2.8)
 
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

project(test-compiler)
add_subdirectory(src)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
