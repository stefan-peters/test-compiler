file(GLOB SOURCES *.cpp)

add_executable(tc ${SOURCES}) 

target_link_libraries(tc
	${CLANG_LIBS}
	z
	ncurses
	${LLVM_LDFLAGS}
	${LLVM_MODULE_LIBS}
)
