add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(demo demo.cpp)

target_link_libraries(demo
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
