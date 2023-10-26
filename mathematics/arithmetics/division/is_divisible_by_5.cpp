#include "common_header.h"

#include "mathematics/arithmetics/modulo/modulo.h"


namespace {

using ArrayType = std::vector<int>;

/** Multiply the given number by 2 such that it is divisible by 10
 *
 * @reference   https://www.geeksforgeeks.org/multiply-the-given-number-by-2-such-that-it-is-divisible-by-10/
 *
 * Given a number, the only operation allowed is to multiply the number by 2. Calculate the minimum
 * number of operations to make the number divisible by 10.
 * NOTE: If it is not possible to convert then print -1.
 */

inline constexpr auto isDivisibleBy5_Mod(const int n) {
    return n % 5 == 0;
}


inline constexpr auto isDivisibleBy5_LastDigit(const int n) {
    const auto last_digit = n % 10;
    return (last_digit == 0) or (last_digit == 5) or (last_digit == -5);
}


/** Is divisible by 5
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              https://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 *
 * Given a positive number n, write a function isMultipleof5(int n) that returns true if n is multiple
 * of 5, otherwise false. You are not allowed to use % and / operators.
*/
inline constexpr auto isDivisibleBy5_Subtraction(int n) {
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        n -= 5;
    }

    return n == 0;
}


inline auto isDivisibleBy5_ToString(const int n) {
    const auto str_n = std::to_string(n);
    return str_n.back() == '0' or str_n.back() == '5';
}


/** Set last digit as 0 and use floating point trick
 *
 * @reference   Check if a number is multiple of 5 without using / and % operators
 *              https://www.geeksforgeeks.org/check-if-a-number-is-multiple-of-5-without-using-and-operators/
 *
 * A number n can be a multiple of 5 in two cases. When last digit of n is 5 or 10.  If last bit in
 * binary equivalent of n is set (which can be the case when last digit is 5) then we multiply by 2
 * using n<<=1 to make sure that if the number is multiple of 5 then we have the last digit as 0. Once
 * we do that, our work is to just check if the last digit is 0 or not, which we can do using float and
 * integer comparison trick.
 */
inline constexpr auto isDivisibleBy5_Float(const int n) {
    //Make it unsigned to prevent integer overflow error
    unsigned positive_n = n;
    if (n < 0) {
        positive_n = -n;
    }
    if (positive_n & 1) {
        positive_n <<= 1;
    }

    //Use static_cast<unsigned> instead of std::floor() to avoid float accuracy issue
    const auto x = static_cast<unsigned>(static_cast<double>(positive_n) * 0.1) * 10;

    return x == positive_n;
}


inline constexpr auto isDivisibleBy5_LastDigitStrict(const int n) {
    const auto last_digit = Mod10_Float(n);
    return (last_digit == 0) or (last_digit == 5) or (last_digit == -5);
}


/**
 * @reference   Binary Prefix Divisible By 5
 *              https://leetcode.com/problems/binary-prefix-divisible-by-5/
 *
 * You are given a binary array nums (0-indexed).
 * We define xi as the number whose binary representation is the subarray nums[0..i] (from
 * most-significant-bit to least-significant-bit).
 *  For example, if nums = [1,0,1], then x0 = 1, x1 = 2, and x2 = 5.
 * Return an array of booleans answer where answer[i] is true if xi is divisible by 5.
 */
std::vector<bool> BinaryPrefixesDivisibleBy5(const ArrayType &nums) {
    std::vector<bool> result;
    int v = 0;
    for (const auto n : nums) {
        v = (v * 2 + n) % 5;
        result.push_back(v == 0);
    }

    return result;
}


/**
 * @reference   Minimum Operations to Make a Special Number
 *              https://leetcode.com/problems/minimum-operations-to-make-a-special-number/
 *
 * You are given a 0-indexed string num representing a non-negative integer.
 * In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits
 * of num, num becomes 0.
 * Return the minimum number of operations required to make num special.
 * An integer x is considered special if it is divisible by 25.
 */
int MinOperationsToMakeSpecialNumber(const std::string_view num) {
    bool has_five = false;
    bool has_zero = false;

    for (int i = num.size() - 1; i >= 0; --i) {
        const auto digit = num[i];
        if (has_zero) {
            if ((digit == '0') or (digit == '5')) {
                return num.size() - i - 2;
            }
        }

        if (has_five) {
            if ((digit == '2') or (digit == '7')) {
                return num.size() - i - 2;
            }
        }

        if (digit == '5') {
            has_five = true;
        } else if (digit == '0') {
            has_zero = true;
        }
    }

    if (has_zero) {
        return num.size() - 1;
    }

    return num.size();
}

} //namespace


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();
constexpr int SAMPLE1 = -4;
constexpr int SAMPLE2 = -40;
constexpr int SAMPLE3 = 189;
constexpr int SAMPLE4 = 2600;


SIMPLE_BENCHMARK(isDivisibleBy5_Mod, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_Mod, Sample2, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_Mod, Sample3, SAMPLE3);

SIMPLE_TEST(isDivisibleBy5_Mod, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5_Mod, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_Mod, TestSAMPLE4, true, SAMPLE4);


SIMPLE_BENCHMARK(isDivisibleBy5_LastDigit, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigit, Sample2, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigit, Sample3, SAMPLE3);

SIMPLE_TEST(isDivisibleBy5_LastDigit, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5_LastDigit, TestSAMPLE5, true, -970991465);

MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_LastDigit, LOWER, UPPER);


SIMPLE_BENCHMARK(isDivisibleBy5_Subtraction, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_Subtraction, Sample2, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_Subtraction, Sample3, SAMPLE3);

SIMPLE_TEST(isDivisibleBy5_Subtraction, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_Subtraction, TestSAMPLE4, true, SAMPLE4);


SIMPLE_BENCHMARK(isDivisibleBy5_ToString, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_ToString, Sample2, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_ToString, Sample3, SAMPLE3);

SIMPLE_TEST(isDivisibleBy5_ToString, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5_ToString, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_ToString, TestSAMPLE4, true, SAMPLE4);


SIMPLE_BENCHMARK(isDivisibleBy5_Float, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_Float, Sample2, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_Float, Sample3, SAMPLE3);

SIMPLE_TEST(isDivisibleBy5_Float, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5_Float, TestLOWERPlusOne, false, LOWER + 1);
SIMPLE_TEST(isDivisibleBy5_Float, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5_Float, TestSAMPLE5, true, -1082066345);

MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_Subtraction, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_ToString, LOWER, UPPER);
MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_Float, LOWER, UPPER);


SIMPLE_BENCHMARK(isDivisibleBy5_LastDigitStrict, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigitStrict, Sample2, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy5_LastDigitStrict, Sample3, SAMPLE3);

SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestLOWERPlusOne, false, LOWER + 1);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isDivisibleBy5_LastDigitStrict, TestSAMPLE5, true, -1082066345);

MUTUAL_RANDOM_TEST(isDivisibleBy5_Mod, isDivisibleBy5_LastDigitStrict, LOWER, UPPER);


const ArrayType SAMPLE1B = {0, 1, 1};
const std::vector EXPECTED1 = {true, false, false};

const ArrayType SAMPLE2B = {1, 1, 1};
const std::vector EXPECTED2 = {false, false, false};

const ArrayType SAMPLE3B = {0, 1, 1, 1, 1, 1};
const std::vector EXPECTED3 = {true, false, false, false, true, false};

const ArrayType SAMPLE4B = {1, 1, 1, 0, 1};
const std::vector EXPECTED4 = {false, false, false, false, false};


THE_BENCHMARK(BinaryPrefixesDivisibleBy5, SAMPLE1B);

SIMPLE_TEST(BinaryPrefixesDivisibleBy5, TestSAMPLE1, EXPECTED1, SAMPLE1B);
SIMPLE_TEST(BinaryPrefixesDivisibleBy5, TestSAMPLE2, EXPECTED2, SAMPLE2B);
SIMPLE_TEST(BinaryPrefixesDivisibleBy5, TestSAMPLE3, EXPECTED3, SAMPLE3B);
SIMPLE_TEST(BinaryPrefixesDivisibleBy5, TestSAMPLE4, EXPECTED4, SAMPLE4B);


THE_BENCHMARK(MinOperationsToMakeSpecialNumber, "2245047");

SIMPLE_TEST(MinOperationsToMakeSpecialNumber, TestSAMPLE1, 2, "2245047");
SIMPLE_TEST(MinOperationsToMakeSpecialNumber, TestSAMPLE2, 3, "2908305");
SIMPLE_TEST(MinOperationsToMakeSpecialNumber, TestSAMPLE3, 1, "10");
