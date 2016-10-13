add_library(numbers
    gcd.cpp
    lcm.cpp)

CompileBenchmarkExe(gcd)
CompileTestExe(gcd)

CompileBenchmarkExe(lcm
    numbers)
CompileTestExe(lcm
    numbers)

add_subdirectory(binary)
add_subdirectory(prime)
