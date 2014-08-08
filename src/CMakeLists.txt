add_executable(tc main.cpp) 

target_link_libraries(tc
	${CLANG_LIBS}
	z
	ncurses
	${LLVM_LDFLAGS}
	${LLVM_MODULE_LIBS}
)
