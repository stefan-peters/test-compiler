file(GLOB SOURCES *.cpp)

add_executable(tc ${SOURCES}) 

target_link_libraries(tc
	${LLVM_LDFLAGS}
	${CLANG_LIBS}
	${LLVM_MODULE_LIBS}
	${LLVM_SYSTEM_LIBS}
)
