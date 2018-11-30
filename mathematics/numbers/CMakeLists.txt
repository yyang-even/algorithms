add_library(numbers
    large_integer.cpp)

CompileBenchmarkExe(large_integer)
CompileTestExe(large_integer)

CompileBenchmarkExe(rotate_for_a_max)
CompileTestExe(rotate_for_a_max)

add_subdirectory(binary)
add_subdirectory(fibonacci)
add_subdirectory(gcd)
add_subdirectory(prime)
