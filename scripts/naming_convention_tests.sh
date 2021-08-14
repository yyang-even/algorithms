#!/bin/bash

oneTimeSetUp() {
    THIS_DIR=$(dirname "$0")
    source "$THIS_DIR/utils.sh"
}

testEachSourceShouldMatchNamingConvention() {
    PROJECT_ROOT_DIR=$(GetProjectRootDir)
    QuietRun pushd "$PROJECT_ROOT_DIR"

    source_files=$(git ls-files -- '*.cpp' '*.h' '*.sh')

    while IFS= read -r a_file; do
        assertTrue "$a_file doesn't match naming convention." "[[ $a_file =~ ^[-/_.0-9a-zA-Z]+$ ]]"
    done <<< "$source_files"

    QuietRun popd
}

source /usr/bin/shunit2
