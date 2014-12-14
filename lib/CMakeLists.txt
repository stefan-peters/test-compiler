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

add_library(coverage_default STATIC "src/instrument/default.c")

#
# TESTS
#

if(BUILD_TESTS)

	include(UseGoogleMock)

	include_directories(${GMOCK_INCLUDE_DIRS})
	link_directories(${GMOCK_LIBRARY_DIRS})

	macro(add_gmock_test source libraries)

	  	GET_FILENAME_COMPONENT(test_name ${source} NAME)
	  	add_executable(${test_name} ${source} "tests/main.cpp")
		add_dependencies(${test_name} GMockExternal ${CMAKE_PROJECT_NAME})

		target_link_libraries(${test_name} ${libraries} ${GMOCK_LIBS})
	  	add_test(NAME ${test_name} COMMAND ${test_name})
	endmacro()

    # ${CMAKE_PROJECT_NAME} this are the llvm libs

    add_gmock_test("tests/test_instrumentation_default.cpp" "")
    add_gmock_test("tests/test_instrumentation_file.cpp" "/Users/ghost/Documents/test-compiler/b/lib/libcoverage_default.a")

endif()
