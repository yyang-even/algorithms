# compile_benchmark
function (compile_benchmark name)
    if (WANT_BENCHMARKS)
        set(target_name ${name}_benchmark)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE WANT_BENCHMARKS)
        target_link_libraries(${target_name} benchmark::benchmark_main
                              ${PTHREAD_LIBRARY} ${ARGN})
    endif (WANT_BENCHMARKS)
endfunction ()

# compile_test
function (compile_test name)
    if (WANT_TESTS)
        set(target_name ${name}_test)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE WANT_TESTS)
        target_link_libraries(${target_name} gtest_main ${PTHREAD_LIBRARY} ${ARGN})
        add_test(${target_name} ${target_name})

        if (WANT_AUTO_TESTS)
            add_custom_command(
                TARGET ${target_name}
                POST_BUILD
                COMMAND ctest --output-on-failure -R ^${target_name}$
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Testing '${target_name}'"
                VERBATIM)
        endif (WANT_AUTO_TESTS)
    endif (WANT_TESTS)
endfunction ()

# compile_app
function (compile_app name)
    if (WANT_TERMINAL_APP)
        set(target_name ${name}_app)
        add_executable(${target_name} ${name}.cpp)
        target_compile_definitions(${target_name} PRIVATE WANT_TERMINAL_APP)
        target_link_libraries(${target_name} ${ARGN})
    endif (WANT_TERMINAL_APP)
endfunction ()

# discover all cpp target
function (discover_all_cpp_target directory)
    file(
        GLOB cpp_files
        RELATIVE ${directory}
        ${directory}/*.cpp)

    foreach (filename ${cpp_files})
        get_filename_component(target_name ${filename} NAME_WLE)

        compile_benchmark(${target_name})
        compile_test(${target_name})
    endforeach ()
endfunction ()

# discover all subdirectory
function (discover_all_subdirs directory)
    file(
        GLOB subdirectories
        RELATIVE ${directory}
        ${directory}/*)

    foreach (a_subdirectory ${subdirectories})
        if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${a_subdirectory})
            add_subdirectory(${a_subdirectory})
        endif ()
    endforeach ()
endfunction ()
