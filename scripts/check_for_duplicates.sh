#!/bin/bash

oneTimeSetUp() {
    THIS_DIR=$(dirname "$0")
    source "$THIS_DIR/utils.sh"

    PROJECT_ROOT_DIR=$(git rev-parse --show-toplevel)
    pushd "$PROJECT_ROOT_DIR"
}

oneTimeTearDown() {
    popd
}

testNumberOfDuplicateReferencesAreExpected() {
    ALL_REFERENCES=$(GetAllReferenceURLs)

    actual=$(echo "$ALL_REFERENCES" | sort | uniq -D | wc -l)

    assertEquals 119 "$actual"
}

source /usr/bin/shunit2
