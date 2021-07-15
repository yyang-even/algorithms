#!/bin/bash

oneTimeSetUp() {
    THIS_DIR=$(dirname "$0")
    source "$THIS_DIR/utils.sh"
}

testNumberOfDuplicateReferencesAreExpected() {
    ALL_REFERENCES=$(GetAllReferenceURLs)

    actual=$(echo "$ALL_REFERENCES" | sort | uniq -D | wc -l)

    assertEquals 103 "$actual"
}

source /usr/bin/shunit2
