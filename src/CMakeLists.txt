add_executable(tc main.cpp) 

target_link_libraries(tc 
clangFrontendTool 
clangFrontend 
clangDriver 
clangSerialization 
clangCodeGen
clangParse 
clangSema 
clangStaticAnalyzerFrontend 
clangStaticAnalyzerCheckers
clangStaticAnalyzerCore 
clangAnalysis 
clangARCMigrate 
clangRewriteFrontend 
clangEdit 
clangAST 
clangLex 
clangBasic
clangTooling
z
ncurses
${LLVM_LDFLAGS}
${LLVM_MODULE_LIBS}
)
