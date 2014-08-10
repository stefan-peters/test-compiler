macro(add_python_test script)
	GET_FILENAME_COMPONENT(test_name ${script} NAME)
	add_test(NAME ${test_name}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/bindings
        COMMAND ${PYTHON_EXECUTABLE} ${script})
    set_tests_properties(${test_name}
    PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/bindings")
endmacro()


file(GLOB SOURCES "*.py")

foreach(source ${SOURCES})
	add_python_test(${source})
endforeach()