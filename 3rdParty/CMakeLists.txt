#Ignore warnings in third party libraries.
set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -w")

if(WANT_TESTS)
    add_subdirectory(googletest)
endif(WANT_TESTS)

if(WANT_BENCHMARKS)
    add_subdirectory(benchmark)
endif(WANT_BENCHMARKS)
