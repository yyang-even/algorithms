add_library(binary
    count_set_bits.cpp)

CompileBenchmarkExe(count_set_bits)
CompileTestExe(count_set_bits)

CompileBenchmarkExe(is_negative)
CompileTestExe(is_negative)
