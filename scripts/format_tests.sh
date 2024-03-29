#!/bin/bash

oneTimeSetUp() {
    THIS_DIR=$(dirname "$0")
    source "$THIS_DIR/utils.sh"
}

testNoUnexpectedKeywordsOrder() {
    PROJECT_ROOT_DIR=$(GetProjectRootDir)
    QuietRun pushd "$PROJECT_ROOT_DIR"

    assertFalse "git grep 'constexpr inline' -- ':(exclude)*.sh'"
    assertFalse "git grep 'const inline' -- ':(exclude)*.sh'"
    assertFalse "git grep 'inline static' -- ':(exclude)*.sh'"

    QuietRun popd
}

testNoUnexpectedReferences() {
    PROJECT_ROOT_DIR=$(GetProjectRootDir)
    QuietRun pushd "$PROJECT_ROOT_DIR"

    assertFalse "git grep '/description' -- ':(exclude)*.sh'"

    QuietRun popd
}

testNoUnexpectedDebugStatement() {
    PROJECT_ROOT_DIR=$(GetProjectRootDir)
    QuietRun pushd "$PROJECT_ROOT_DIR"

    actual=$(git grep -l 'std::endl' -- ':(exclude)*.sh' | wc -l)
    assertEquals 5 "$actual"

    QuietRun popd
}

source /usr/bin/shunit2
