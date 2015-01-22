file(GLOB LIB_SOURCES "src/*.cpp")

add_definitions(
    ${LLVM_CFLAGS}
    -fno-rtti
    -fno-exceptions
)

include_directories (
	"src"
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)

add_library(${CMAKE_PROJECT_NAME} SHARED ${LIB_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}
	${LLVM_LDFLAGS}
	${CLANG_LIBS}
	${LLVM_MODULE_LIBS}
	${LLVM_SYSTEM_LIBS}
	${PYTHON_LIBRARY}
)


set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
	SOVERSION ${VERSION}
    VERSION ${VERSION}
)

add_library(coverage_cnt_file STATIC "src/instrument/default.c")
# just demo. needs a real implementation
add_library(coverage_hit_file STATIC "src/instrument/default.c")

#
# TESTS
#

if(BUILD_TESTS)

	include(UseGoogleMock)

	include_directories(${GMOCK_INCLUDE_DIRS})
	link_directories(${GMOCK_LIBRARY_DIRS})

	macro(add_gmock_test test_name sources libraries)

        set(sources ${sources}"tests/main.cpp")

	  	add_executable(${test_name} ${sources})
		add_dependencies(${test_name} GMockExternal ${CMAKE_PROJECT_NAME})

		target_link_libraries(${test_name} ${libraries} ${GMOCK_LIBS})
	  	add_test(NAME ${test_name} COMMAND ${test_name})
	endmacro()

    # ${CMAKE_PROJECT_NAME} this are the llvm libs

    set(sources "tests/test_instrumentation_default.cpp")
    add_gmock_test("default_instrumentation" "${sources}" "")

    set(sources "tests/test_instrumentation_file.cpp" "tests/data/data1.cpp")
    add_gmock_test("write_to_coverage_to_file" "${sources}" coverage_cnt_file)

endif()
