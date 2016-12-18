add_library(binary
    count_set_bits.cpp)

CompileBenchmarkExe(abs)
CompileTestExe(abs)

CompileBenchmarkExe(are_opposite_signs)
CompileTestExe(are_opposite_signs)

CompileBenchmarkExe(count_set_bits)
CompileTestExe(count_set_bits)

CompileBenchmarkExe(conditionally_set_or_clear)
CompileTestExe(conditionally_set_or_clear)

CompileBenchmarkExe(is_negative)
CompileTestExe(is_negative)

CompileBenchmarkExe(is_power_of_2)
CompileTestExe(is_power_of_2)

CompileBenchmarkExe(min_and_max)
CompileTestExe(min_and_max)

CompileBenchmarkExe(sign_extending)
CompileTestExe(sign_extending)
