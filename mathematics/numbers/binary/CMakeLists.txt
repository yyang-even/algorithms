add_library(binary
    count_set_bits.cpp)

CompileBenchmarkExe(abs)
CompileTestExe(abs)

CompileBenchmarkExe(are_opposite_signs)
CompileTestExe(are_opposite_signs)

CompileBenchmarkExe(count_set_bits)
CompileTestExe(count_set_bits)

CompileBenchmarkExe(is_negative)
CompileTestExe(is_negative)
