#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** LCM - Least Common Multiple
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Exercise 4.2.
 *
 * The best way known to compute lcm(m, n) is to compute gcd(m, n) first and then to
 * divide mn by the gcd.
 *
 * @reference   Program to find LCM of two numbers
 *              https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/
 *
 * LCM (Least Common Multiple) of two numbers is the smallest number which can be divided
 * by both numbers.
 *
 * @reference   TCS Coding Practice Question | LCM of 2 Numbers
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-lcm-of-2-numbers/
 *
 * @reference   Inbuilt function for calculating LCM in C++
 *              https://www.geeksforgeeks.org/inbuilt-function-calculating-lcm-cpp/
 */
inline constexpr unsigned LCM(const unsigned m, const unsigned n) {
    return m * n / std::gcd(m, n);
}


/**
 * @reference   Program to find LCM of 2 numbers without using GCD
 *              https://www.geeksforgeeks.org/program-to-find-lcm-of-2-numbers-without-using-gcd/
 */
constexpr auto LCM_MOD(const unsigned m, const unsigned n) {
    const auto [min, max] = std::minmax(m, n);

    auto lcm = max;
    for (; lcm % min != 0; lcm += max);

    return lcm;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 31.2-8.
 * @reference   LCM of given array elements
 *              https://www.geeksforgeeks.org/lcm-of-given-array-elements/
 */
auto LCM_Array(const ArrayType &numbers) {
    assert(numbers.size() > 2);

    unsigned long long result = numbers.front();

    for (ArrayType::size_type i = 1; i < numbers.size(); ++i) {
        result = (numbers[i] * result) / std::gcd(numbers[i], result);
    }

    return result;
}

}//namespace


SIMPLE_BENCHMARK(LCM, Sample1, 12, 18);
SIMPLE_BENCHMARK(LCM, Sample2, 18, 12);

SIMPLE_TEST(LCM, Test1, 36, 12, 18);
SIMPLE_TEST(LCM, Test2, 36, 18, 12);


SIMPLE_BENCHMARK(LCM_MOD, Sample1, 12, 18);
SIMPLE_BENCHMARK(LCM_MOD, Sample2, 18, 12);

SIMPLE_TEST(LCM_MOD, Test1, 36, 12, 18);
SIMPLE_TEST(LCM_MOD, Test2, 36, 18, 12);


const ArrayType SAMPLE1 = {1, 2, 8, 3};
const ArrayType SAMPLE2 = {2, 7, 3, 9, 4};


THE_BENCHMARK(LCM_Array, SAMPLE1);

SIMPLE_TEST(LCM_Array, TestSample1, 24, SAMPLE1);
SIMPLE_TEST(LCM_Array, TestSample2, 252, SAMPLE2);
