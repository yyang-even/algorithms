#include "common_header.h"

#include "count_digits_in_integer.h"


namespace {

/** Program to count digits in an integer (4 Different Methods)
 *
 * @reference   https://www.geeksforgeeks.org/program-count-digits-integer-3-different-methods/
 * @reference   C program to Count the digits of a number
 *              https://www.geeksforgeeks.org/c-program-to-count-the-digits-of-a-number/
 */
auto CountDigits_Recursive(const int n) {
    if (not n) {
        return 0;
    }
    return 1 + CountDigits_Recursive(n / 10);
}


int CountDigits_Log(const int n) {
    if (not n) {
        return 0;
    }
    return std::floor(std::log10(n) + 1);
}


auto CountDigits_String(const int n) {
    assert(n > 0);

    const auto str_n = std::to_string(n);
    return str_n.size();
}


/**
 * @reference   TCS Coding Practice Question | Sum of Digits of a number
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-sum-of-digits-of-a-number/
 * @reference   C Program for Sum the digits of a given number
 *              https://www.geeksforgeeks.org/c-program-for-program-for-sum-the-digits-of-a-given-number/
 * @reference   Program for Sum of the digits of a given number
 *              https://www.geeksforgeeks.org/program-for-sum-of-the-digits-of-a-given-number/
 * @reference   Sum of digit of a number using recursion
 *              https://www.geeksforgeeks.org/sum-digit-number-using-recursion/
 */


/**
 * @reference   Program to calculate product of digits of a number
 *              https://www.geeksforgeeks.org/program-to-calculate-product-of-digits-of-a-number/
 */


/**
 * @reference   C Program to Print all digits of a given number
 *              https://www.geeksforgeeks.org/c-program-to-print-all-digits-of-a-given-number/
 */

}//namespace


SIMPLE_BENCHMARK(CountDigits_Iterative, Sample1, 345289467);

SIMPLE_TEST(CountDigits_Iterative, TestSAMPLE1, 9, 345289467);
SIMPLE_TEST(CountDigits_Iterative, TestSAMPLE2, 0, 0);


SIMPLE_BENCHMARK(CountDigits_Recursive, Sample1, 345289467);

SIMPLE_TEST(CountDigits_Recursive, TestSAMPLE1, 9, 345289467);
SIMPLE_TEST(CountDigits_Recursive, TestSAMPLE2, 0, 0);


SIMPLE_BENCHMARK(CountDigits_Log, Sample1, 345289467);

SIMPLE_TEST(CountDigits_Log, TestSAMPLE1, 9, 345289467);
SIMPLE_TEST(CountDigits_Log, TestSAMPLE2, 0, 0);


SIMPLE_BENCHMARK(CountDigits_String, Sample1, 345289467);

SIMPLE_TEST(CountDigits_String, TestSAMPLE1, 9, 345289467);
