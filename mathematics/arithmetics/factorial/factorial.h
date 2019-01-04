#pragma once

unsigned long FactorialIterative(unsigned num) {
    unsigned long result = 1;
    for (; num > 1; --num) {
        result *= num;
    }
    return result;
}
