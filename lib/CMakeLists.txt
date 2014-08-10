file(GLOB SOURCES *.cpp)

include_directories (
	"."
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)

add_library(tc SHARED ${SOURCES}) 

target_link_libraries(tc
	${LLVM_LDFLAGS}
	${CLANG_LIBS}
	${LLVM_MODULE_LIBS}
	${LLVM_SYSTEM_LIBS}
	${PYTHON_LIBRARY}
)


set_target_properties(tc PROPERTIES 
	SOVERSION ${VERSION}
    VERSION ${VERSION}
)