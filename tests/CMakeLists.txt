
include(UseGoogleMock)

include_directories(${GMOCK_INCLUDE_DIRS})
link_directories(${GMOCK_LIBRARY_DIRS})

add_executable(demo demo.cpp)
add_dependencies(demo GMockExternal)

target_link_libraries(demo
    ${GMOCK_LIBS}
)
