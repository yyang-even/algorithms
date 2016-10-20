add_library(prime
    largest_power_of_p_divides_factorial_n.cpp
    primes_below_n.cpp)
target_link_libraries(prime
    binary)

CompileBenchmarkExe(prime_factors_of_n)
CompileTestExe(prime_factors_of_n)

CompileBenchmarkExe(primes_below_n)
CompileTestExe(primes_below_n)

CompileBenchmarkExe(largest_power_of_p_divides_factorial_n
    binary)
CompileTestExe(largest_power_of_p_divides_factorial_n
    binary)
