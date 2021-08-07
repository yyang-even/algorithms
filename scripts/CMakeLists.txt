find_program(BASH_PROGRAM bash)

if (BASH_PROGRAM)
    add_test(duplicate_references_tests ${BASH_PROGRAM}
             ${CMAKE_CURRENT_SOURCE_DIR}/duplicate_references_tests.sh)

    add_test(format_tests ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/format_tests.sh)
endif (BASH_PROGRAM)
