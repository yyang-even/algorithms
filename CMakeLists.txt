cmake_minimum_required(VERSION 2.8.12.2)

project (Algorithms)

###################################################
# gcc
#   1. Using C++11;
#   2. Enable gdb
###################################################
list(APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS} -g")

include_directories ("${PROJECT_SOURCE_DIR}")

###################################################
# Options
###################################################
option(WANT_BENCHMARKS "We want benchmark executables" ON)
# Do we want unit tests?
option(WANT_TESTS "We want unit tests" ON)
if(WANT_TESTS)
    enable_testing()
    include(CTest)
    mark_as_advanced(BUILD_TESTING)

    #################################
    #gtest
    #################################
    set(gtest_force_shared_crt ON)
    set(GTEST_VER 1.7.0)
    set(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/3rdParty/googletest-release-${GTEST_VER}/include)
    include_directories ("${GTEST_INCLUDE_DIRS}")
endif(WANT_TESTS)

# pthread
if(WANT_BENCHMARKS OR WANT_TESTS)
    # on unices, we also have to link with pthreads for GTest.
    if(UNIX)
        find_library(PTHREAD_LIBRARY
            NAMES pthread
            PATHS /lib64 /usr/lib64
        )
        if(NOT PTHREAD_LIBRARY)
            message(FATAL_ERROR "Unable to find pthread library.")
        endif(NOT PTHREAD_LIBRARY)
        message(STATUS "Pthread library is ${PTHREAD_LIBRARY}")
    endif(UNIX)
endif()

###################################################
# Macros
###################################################
macro(CompileBenchmarkExe name)
    if(WANT_BENCHMARKS)
        set(target_name ${name}_benchmark)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE NONIUS_RUNNER)
        target_link_libraries(${target_name} ${PTHREAD_LIBRARY})
    endif(WANT_BENCHMARKS)
endmacro(CompileBenchmarkExe)

macro(CompileTestExe name)
    if(WANT_TESTS)
        set(target_name ${name}_test)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE WANT_TESTS)
        target_link_libraries(${target_name}
            gtest_main
            ${PTHREAD_LIBRARY})
        add_test(${target_name} ${target_name})
    endif(WANT_TESTS)
endmacro(CompileTestExe)

###################################################
# Subdirectories
###################################################
add_subdirectory(3rdParty)
add_subdirectory(recurrent)
