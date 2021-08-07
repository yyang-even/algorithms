#!/bin/bash

testNoUnexpectedKeywordsOrder() {
    assertFalse "git grep 'constexpr inline'"
    assertFalse "git grep 'const inline'"
    assertFalse "git grep 'inline static'"
}

source /usr/bin/shunit2
