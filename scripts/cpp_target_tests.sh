#!/bin/bash

oneTimeSetUp() {
    THIS_DIR=$(dirname "$0")
    source "$THIS_DIR/utils.sh"
}

testEachCppShouldHaveAtLeastOneCmakeTarget() {
    PROJECT_ROOT_DIR=$(GetProjectRootDir)
    QuietRun pushd "$PROJECT_ROOT_DIR"

    cpp_file_names=$(git ls-files -- ':(exclude)scripts/' | grep --only-matching -E "[-_0-9a-zA-Z]+\.cpp" | cut -d ":" -f 2 | cut -d "." -f 1)

    while IFS= read -r a_name; do
        assertTrue "$a_name doesn't have a target." "git grep -E \($a_name\) -- '*.txt'"
    done <<< "$cpp_file_names"

    QuietRun popd
}

source /usr/bin/shunit2
