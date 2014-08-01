cmake_minimum_required(VERSION 2.8)

project(test-compiler)
 
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(
	${test-compiler_SOURCE_DIR}/src
	${test-compiler_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()

add_test(NAME Demo COMMAND demo)

