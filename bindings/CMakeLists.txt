set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")

set(ENV_SH_IN "${CMAKE_CURRENT_SOURCE_DIR}/env.source.sh.in")
set(ENV_SH "${CMAKE_BINARY_DIR}/env.source.sh")

set(DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/modules/__init__.py")
set(OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build/timestamp")

set(PY_MODULES_FOLDER "py-module")
set(PY_MODULES_PATH "${CMAKE_CURRENT_BINARY_DIR}/${PY_MODULES_FOLDER}")
set(PY_MODULE_PATH "${PY_MODULES_PATH}/${CMAKE_PROJECT_NAME}")

set(PY_MODULE_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

configure_file(${SETUP_PY_IN} ${SETUP_PY})
configure_file(${ENV_SH_IN} ${ENV_SH})

add_custom_command(OUTPUT ${OUTPUT}
                   COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} build
                   COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                   DEPENDS ${DEPS})

add_custom_target(copy_py_modules ALL
    ${CMAKE_COMMAND} -E make_directory ${PY_MODULE_PATH}
    COMMAND rsync -r "${CMAKE_CURRENT_SOURCE_DIR}/modules/." "${PY_MODULE_PATH}"
)

add_custom_target(target ALL DEPENDS copy_py_modules ${OUTPUT})

install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} install)")

# install(CODE "execute_process(COMMAND python setup.py install -f
# --prefix=${CMAKE_INSTALL_PREFIX} WORKING_DIRECTORY
# ../source/libmoleculizer-1.1.2/python-src/language_parser)")

if(APPLE)
  set(Boost_USE_STATIC_LIBS   ON)
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_RUNTIME ON)
else()
  set(Boost_USE_STATIC_LIBS   OFF)
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_RUNTIME OFF)
endif()

find_package(Boost COMPONENTS system thread python REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS} ${PYTHON_LIBRARY_DIRS})

macro(create_python_module name sources)
  set(ext_name ${name})
  add_library(${ext_name} SHARED ${sources})
  target_link_libraries(${ext_name} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${CMAKE_PROJECT_NAME})
  set_target_properties(${ext_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PY_MODULE_PATH}")
  add_dependencies(${ext_name} ${CMAKE_PROJECT_NAME})

  if(WIN32)
    set_target_properties(${ext_name} PROPERTIES PREFIX "" SUFFIX ".dll")
  else()
    set_target_properties(${ext_name} PROPERTIES PREFIX "" SUFFIX ".so")
  endif()
endmacro()


create_python_module(_annotate extensions/_annotate.cpp)


#
# TESTS
#

if(BUILD_TESTS)

  get_filename_component(abs_tests "tests/unit" ABSOLUTE)
  add_test(NAME python_unit_tests COMMAND ${PYTHON_EXECUTABLE} -B -m pytest -v ${abs_tests})
  set_tests_properties(python_unit_tests PROPERTIES ENVIRONMENT "PYTHONPATH=${PY_MODULES_PATH}")

  get_filename_component(abs_tests "tests/integration" ABSOLUTE)
  add_test(NAME python_integration_tests COMMAND ${PYTHON_EXECUTABLE} -B -m pytest -v ${abs_tests})
  set_tests_properties(python_integration_tests PROPERTIES ENVIRONMENT "PYTHONPATH=${PY_MODULES_PATH}")
  set_tests_properties(python_integration_tests PROPERTIES ENVIRONMENT "PATH=${PY_MODULE_BIN_DIR};$ENV{PATH}")

endif()
