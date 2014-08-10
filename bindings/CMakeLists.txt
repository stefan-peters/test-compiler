set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/tc/__init__.py")
set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build/timestamp")

configure_file(${SETUP_PY_IN} ${SETUP_PY})

add_custom_command(OUTPUT ${OUTPUT}
                   COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} build
                   COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                   DEPENDS ${DEPS})

add_custom_target(target ALL DEPENDS ${OUTPUT})

install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} install)")

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost COMPONENTS system thread python REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS} ${PYTHON_LIBRARY_DIRS})

add_library(spam SHARED
        tc/spam.cpp
    )

target_link_libraries(spam
        ${PYTHON_LIBRARIES}
    )

if(APPLE)
  set_target_properties(spam PROPERTIES PREFIX "" SUFFIX ".so")
endif()