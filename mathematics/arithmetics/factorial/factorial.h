#pragma once

/**
 * @reference   TCS Coding Practice Question | Factorial of a Number
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-factorial-of-a-number/
 */
auto Factorial_Iterative(unsigned num) {
    unsigned long result = 1;
    for (; num > 1; --num) {
        result *= num;
    }
    return result;
}
