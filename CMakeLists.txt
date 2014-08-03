cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER clang++)

project(test-compiler)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules")
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

find_package(LLVM REQUIRED)
find_package(Clang REQUIRED)

link_directories(
    ${LLVM_LIBRARY_DIRS}
    ${CLANG_LIBRARY_DIRS}
)

add_definitions(
    ${LLVM_CFLAGS}
    -fno-rtti
    -fno-exceptions
)

include_directories(
    ${test-compiler_SOURCE_DIR}/src
    ${test-compiler_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}   
 	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1
)


add_subdirectory(src)
add_subdirectory(tests)

enable_testing()

add_test(NAME Demo COMMAND demo)

