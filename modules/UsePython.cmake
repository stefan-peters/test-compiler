find_package(PythonLibs ${REQUIRED_PYTHON_VERSION} REQUIRED)
find_package(PythonInterp ${PYTHONLIBS_VERSION_STRING} REQUIRED)

macro(add_python_test script)    
	add_test(NAME ${script}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/bindings
        COMMAND ${PYTHON_EXECUTABLE} ${script})
    set_tests_properties(${script}
    PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/bindings")
endmacro()