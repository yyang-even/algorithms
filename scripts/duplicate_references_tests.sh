#!/bin/bash

oneTimeSetUp() {
    git checkout --quiet master

    PROJECT_ROOT_DIR=$(git rev-parse --show-toplevel)

    pushd "$PROJECT_ROOT_DIR"
}

oneTimeTearDown() {
    popd
}

testNumberOfDuplicateReferencesAreExpected() {
    ALL_REFERENCES=$(git grep --only-matching -E "[^ ]+://[^ ]+" -- */ | cut -d ":" -f 3-)

    actual=$(echo "$ALL_REFERENCES" | sort | uniq -D | wc -l)

    assertEquals 119 "$actual"
}

source /usr/bin/shunit2
