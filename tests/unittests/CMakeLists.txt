include(UseGoogleMock)

include_directories(${GMOCK_INCLUDE_DIRS})
link_directories(${GMOCK_LIBRARY_DIRS})

file(GLOB SOURCES "*.cpp")

add_executable(unittests ${SOURCES})
add_dependencies(unittests GMockExternal)

target_link_libraries(unittests
    ${GMOCK_LIBS}
)

add_test(NAME unittests COMMAND unittests)