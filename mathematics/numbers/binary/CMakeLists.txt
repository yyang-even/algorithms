add_library(binary
    count_set_bits.cpp
    log_base_2.cpp)

CompileBenchmarkExe(abs)
CompileTestExe(abs)

CompileBenchmarkExe(are_opposite_signs)
CompileTestExe(are_opposite_signs)

CompileBenchmarkExe(byte_range)
CompileTestExe(byte_range)

CompileBenchmarkExe(count_set_bits)
CompileTestExe(count_set_bits)

CompileBenchmarkExe(conditionally_set_or_clear)
CompileTestExe(conditionally_set_or_clear)

CompileBenchmarkExe(conditionally_negate)
CompileTestExe(conditionally_negate)

CompileBenchmarkExe(count_trailing_zeros)
CompileTestExe(count_trailing_zeros)

CompileBenchmarkExe(endianness)
CompileTestExe(endianness)

CompileBenchmarkExe(is_negative)
CompileTestExe(is_negative)

CompileBenchmarkExe(is_power_of_2)
CompileTestExe(is_power_of_2)

CompileBenchmarkExe(log_base_2)
CompileTestExe(log_base_2)

CompileBenchmarkExe(min_and_max)
CompileTestExe(min_and_max)

CompileBenchmarkExe(masked_bits_merge)
CompileTestExe(masked_bits_merge)

CompileBenchmarkExe(modulus)
CompileTestExe(modulus)

CompileBenchmarkExe(morton_number)
CompileTestExe(morton_number)

CompileBenchmarkExe(parity)
CompileTestExe(parity)

CompileBenchmarkExe(permutation)
CompileTestExe(permutation)

CompileBenchmarkExe(reverse)
CompileTestExe(reverse)

CompileBenchmarkExe(round_up_to_power_of_2)
CompileTestExe(round_up_to_power_of_2)

CompileBenchmarkExe(sign_extending)
CompileTestExe(sign_extending)

CompileBenchmarkExe(swap)
CompileTestExe(swap)

CompileBenchmarkExe(zig_zag_encoding)
CompileTestExe(zig_zag_encoding)
