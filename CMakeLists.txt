cmake_minimum_required(VERSION 2.8.12.2)

project (Algorithms)

###################################################
# gcc
###################################################
# Using C++17
set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -std=c++17")
set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -g")

# Turn on warnings
set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -Wall")
# Obtain all the diagnostics required by the standard as errors rather than warnings
#set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -pedantic-errors")
# Turn warning about any return statement with no return value in a function whose return type is not void
set(CMAKE_CXX_FLAGS       "${CMAKE_CXX_FLAGS}       -Werror=return-type")

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/3rdParty/nonius/include")

###################################################
# Options
###################################################
# define option explicitly for pretty ccmake/cmake-gui
option(BUILD_SHARED_LIBS "Build libraries as .dll's/.so's" true)
mark_as_advanced(CLEAR BUILD_SHARED_LIBS)# mark un-advanced

option(WANT_TERMINAL_APP "We want terminal based applications" ON)
option(WANT_BENCHMARKS "We want benchmark executables" ON)

# Do we want unit tests?
option(WANT_TESTS "We want unit tests" ON)
option(WANT_AUTO_TESTS "We want to run tests that have been changed" OFF)
if(WANT_TESTS)
    enable_testing()
    include(CTest)
    mark_as_advanced(BUILD_TESTING)

    #################################
    #gtest
    #################################
    set(gtest_force_shared_crt ON)
    set(GTEST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/3rdParty/googletest/include)
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
# Functions
###################################################
function(CompileBenchmarkExe name)
    if(WANT_BENCHMARKS)
        set(target_name ${name}_benchmark)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE NONIUS_RUNNER)
        target_link_libraries(${target_name}
            ${PTHREAD_LIBRARY}
            ${ARGN})
    endif(WANT_BENCHMARKS)
endfunction(CompileBenchmarkExe)

function(CompileTestExe name)
    if(WANT_TESTS)
        set(target_name ${name}_test)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE WANT_TESTS)
        target_link_libraries(${target_name}
            gtest_main
            ${PTHREAD_LIBRARY}
            ${ARGN})
        add_test(${target_name} ${target_name})

        if(WANT_AUTO_TESTS)
            add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND ctest --output-on-failure -R ^${target_name}$
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Testing '${target_name}'" VERBATIM)
        endif(WANT_AUTO_TESTS)
    endif(WANT_TESTS)
endfunction(CompileTestExe)

function(CompileTerminalApp name)
    if(WANT_TERMINAL_APP)
        set(target_name ${name}_app)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE WANT_TERMINAL_APP)
        target_link_libraries(${target_name}
            ${ARGN})
    endif(WANT_TERMINAL_APP)
endfunction(CompileTerminalApp)

###################################################
# Subdirectories
###################################################
add_subdirectory(3rdParty)
add_subdirectory(decision)
add_subdirectory(data_structure)
add_subdirectory(hash)
add_subdirectory(mathematics)
add_subdirectory(ordering)
add_subdirectory(text)
