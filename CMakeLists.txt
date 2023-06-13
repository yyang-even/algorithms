cmake_minimum_required(VERSION 3.16)

project(Algorithms)

# ######################################################################################
# gcc
# ######################################################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}       -std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}       -g")

# Turn on warnings
# ~~~
# @reference    Warnings: -Weverything and the Kitchen Sink
#               https://embeddedartistry.com/blog/2017/3/7/clang-weverything
# ~~~
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}       -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}       -Wextra")

# Obtain all the diagnostics required by the standard as errors rather than warnings
# set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -pedantic-errors")

# Turn warning about any return statement with no return value in a function whose
# return type is not void
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}       -Werror=return-type")

include_directories("${PROJECT_SOURCE_DIR}")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(utils)

# ######################################################################################
# Options
# ######################################################################################
# define option explicitly for pretty ccmake/cmake-gui
option(BUILD_SHARED_LIBS "Build libraries as .dll's/.so's" true)
mark_as_advanced(CLEAR BUILD_SHARED_LIBS) # mark un-advanced

# ~~~
# @reference    -Werror is Not Your Friend
#               https://embeddedartistry.com/blog/2017/5/3/-werror-is-not-your-friend
# ~~~
option(WARNINGS_AS_ERRORS "Treat all warnings as build errors" ON)
if (WARNINGS_AS_ERRORS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}       -Werror")
endif (WARNINGS_AS_ERRORS)

option(WANT_TERMINAL_APP "We want terminal based applications" ON)
option(WANT_BENCHMARKS "We want benchmark executables" ON)

# Do we want unit tests?
option(WANT_TESTS "We want unit tests" ON)
option(WANT_AUTO_TESTS "We want to run tests that have been changed" ON)
if (WANT_TESTS)
    enable_testing()
    include(CTest)
    mark_as_advanced(BUILD_TESTING)

    # cmake-lint: disable=C0103
    set(gtest_force_shared_crt
        ON
        CACHE BOOL
              "Use shared run-time lib even when Google Test is built as static lib.")
    set(GTEST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/3rdParty/googletest/include)
    include_directories("${GTEST_INCLUDE_DIRS}")
endif (WANT_TESTS)

if (WANT_BENCHMARKS)
    set(BM_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/3rdParty/benchmark/include)
    include_directories("${BM_INCLUDE_DIRS}")
endif (WANT_BENCHMARKS)

# pthread
if (WANT_BENCHMARKS OR WANT_TESTS)
    # on unices, we also have to link with pthreads for GTest.
    if (UNIX)
        find_library(
            PTHREAD_LIBRARY
            NAMES pthread
            PATHS /lib64 /usr/lib64)
        if (NOT PTHREAD_LIBRARY)
            message(FATAL_ERROR "Unable to find pthread library.")
        endif (NOT PTHREAD_LIBRARY)
        message(STATUS "Pthread library is ${PTHREAD_LIBRARY}")
    endif (UNIX)
endif ()

# ######################################################################################
# Subdirectories
# ######################################################################################
add_subdirectory(3rdParty)
add_subdirectory(backtracking)
add_subdirectory(data_structure)
add_subdirectory(dynamic_programming)
add_subdirectory(finding)
add_subdirectory(graphics)
add_subdirectory(greedy)
add_subdirectory(hash)
add_subdirectory(mathematics)
add_subdirectory(ordering)
add_subdirectory(text)

if (WANT_TESTS)
    add_subdirectory(scripts)
endif ()

# ######################################################################################
# Top Level Tests
# ######################################################################################
compile_benchmark(common_header_test)
compile_test(common_header_test)
