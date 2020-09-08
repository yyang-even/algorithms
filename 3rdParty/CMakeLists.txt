#Ignore warnings in third party libraries.
set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -w")

if(WANT_TESTS)
    add_subdirectory(googletest)
endif(WANT_TESTS)

if(WANT_BENCHMARKS)
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Enable testing of the benchmark library.")
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Enable building the unit tests which depend on gtest")
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Enable installation of benchmark. (Projects embedding benchmark may want to turn this OFF.)")
    add_subdirectory(benchmark)
endif(WANT_BENCHMARKS)
