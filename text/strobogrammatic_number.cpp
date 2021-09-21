#include "common_header.h"


namespace {

using ArrayType = std::unordered_multiset<std::string>;

/** Strobogrammatic Number
 *
 * @reference   https://tenderleo.gitbooks.io/leetcode-solutions-/content/GoogleEasy/246.html
 *
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees
 * (looked at upside down). Write a function to determine if a number is strobogrammatic.
 * The number is represented as a string. For example, the numbers "69", "88", and "818"
 * are all strobogrammatic.
 */
const std::unordered_map<char, char> strobogrammatic_digit_map = {
    {'0', '0'},
    {'1', '1'},
    {'8', '8'},
    {'6', '9'},
    {'9', '6'}
};

auto isStrobogrammaticNumber(const std::string_view number) {
    int left = 0;
    int right = number.size() - 1;
    while (left <= right) {
        const auto iter = strobogrammatic_digit_map.find(number[left++]);
        if (iter == strobogrammatic_digit_map.cend() or iter->second != number[right--]) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Confusing Number
 *              https://www.goodtecher.com/leetcode-1056-confusing-number/
 *
 * Given a number N, return true if and only if it is a confusing number, which satisfies
 * the following condition: We can rotate digits by 180 degrees to form new digits. When
 * 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2,
 * 3, 4, 5 and 7 are rotated 180 degrees, they become invalid. A confusing number is a
 * number that when rotated 180 degrees becomes a different number with each digit valid.
 */
const std::unordered_map<int, int> confusing_digit_map = {
    {0, 0},
    {1, 1},
    {8, 8},
    {6, 9},
    {9, 6}
};

auto isConfusingNumber(const int n) {
    int rotated = 0;
    for (auto i = n; i; i /= 10) {
        const auto digit = i % 10;
        const auto iter = confusing_digit_map.find(digit);
        if (iter == confusing_digit_map.cend()) {
            return false;
        }
        rotated = rotated * 10 + iter->second;
    }

    return rotated != n;
}


/**
 * @reference   Strobogrammatic number
 *              https://www.geeksforgeeks.org/strobogrammatic-number/
 *
 * For the given length n, find all n-length Strobogrammatic numbers.
 *
 * @reference   Strobogrammatic Number II
 *              https://tenderleo.gitbooks.io/leetcode-solutions-/content/GoogleMedium/247.html
 */
ArrayType StrobogrammaticNumbers_Recursive(const int N, const int current) {
    if (current == 0)
        return {""};
    if (current == 1)
        return {"0", "1", "8"};

    const auto middles = StrobogrammaticNumbers_Recursive(N, current - 2);
    ArrayType results;
    for (const auto &a_mid : middles) {
        if (N != current) {
            results.insert("0" + a_mid + "0");
        }
        results.insert("1" + a_mid + "1");
        results.insert("8" + a_mid + "8");
        results.insert("6" + a_mid + "9");
        results.insert("9" + a_mid + "6");
    }

    return results;
}

inline auto StrobogrammaticNumbers_Recursive(const int N) {
    return StrobogrammaticNumbers_Recursive(N, N);
}


auto StrobogrammaticNumbers_Iterative(const int N) {
    auto results =
        (N % 2 == 0) ? ArrayType{""} :
        ArrayType{"0", "1", "8"};
    for (int i = (N % 2 == 0) ? 2 : 3; i <= N; i += 2) {
        ArrayType temp;
        for (const auto &a_mid : results) {
            if (N != i) {
                temp.insert("0" + a_mid + "0");
            }
            temp.insert("1" + a_mid + "1");
            temp.insert("8" + a_mid + "8");
            temp.insert("6" + a_mid + "9");
            temp.insert("9" + a_mid + "6");
        }

        results = std::move(temp);
    }

    return results;
}


/**
 * @reference   Strobogrammatic Number III
 *              http://buttercola.blogspot.com/2015/09/leetcode-strobogrammatic-number-iii.html
 *
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees
 * (looked at upside down). Write a function to count the total strobogrammatic numbers
 * that exist in the range of low <= num <= high. Note: Because the range might be a
 * large number, the low and high numbers are represented as string.
 */
void CountStrobogrammaticNumbersInRange(const std::string &low, const std::string &high,
                                        const std::string &mid, int &result) {
    if (mid.size() >= low.size() and mid.size() <= high.size()) {
        if (mid.size() == high.size() and mid > high) {
            return;
        }
        if (not(mid.size() > 1 and mid[0] == '0') and
            not(mid.size() == low.size() and mid < low)) {
            ++result;
        }
    }

    if (mid.size() + 2 > high.size()) {
        return;
    }

    CountStrobogrammaticNumbersInRange(low, high, "0" + mid + "0", result);
    CountStrobogrammaticNumbersInRange(low, high, "1" + mid + "1", result);
    CountStrobogrammaticNumbersInRange(low, high, "6" + mid + "9", result);
    CountStrobogrammaticNumbersInRange(low, high, "8" + mid + "8", result);
    CountStrobogrammaticNumbersInRange(low, high, "9" + mid + "6", result);
}

inline auto
CountStrobogrammaticNumbersInRange(const std::string &low, const std::string &high) {
    int result = 0;

    CountStrobogrammaticNumbersInRange(low, high, "", result);
    CountStrobogrammaticNumbersInRange(low, high, "0", result);
    CountStrobogrammaticNumbersInRange(low, high, "1", result);
    CountStrobogrammaticNumbersInRange(low, high, "8", result);

    return result;
}


/**
 * @reference   LeetCode 1088. Confusing Number II
 *              https://www.cnblogs.com/Dylan-Java-NYC/p/12382526.html
 *
 * We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated
 * 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated
 * 180 degrees, they become invalid. A confusing number is a number that when rotated 180
 * degrees becomes a different number with each digit valid.(Note that the rotated number
 * can be greater than the original number.) Given a positive integer N, return the number
 * of confusing numbers between 1 and N inclusive.
 */
void
CountConfusingNumber(const long N, const long num, const long rotated,
                     const long base, int &count) {
    if (num > N) {
        return;
    }

    if (num != rotated) {
        ++count;
    }

    for (const auto [digit, mapped] : confusing_digit_map) {
        if (num == 0 and digit == 0) {
            continue;
        }

        CountConfusingNumber(N, num * 10 + digit, mapped * base + rotated, base * 10, count);
    }
}

inline auto CountConfusingNumber(const int N) {
    int count = 0;
    CountConfusingNumber(N, 0, 0, 1, count);
    return count;
}

}//namespace


THE_BENCHMARK(isStrobogrammaticNumber, "818");

SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE1, true, "0");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE2, true, "1");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE3, true, "8");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE4, false, "6");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE5, false, "9");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE6, true, "88");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE7, true, "818");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE8, true, "69");
SIMPLE_TEST(isStrobogrammaticNumber, TestSAMPLE9, false, "68");


const ArrayType EXPECTED1 = {"0", "1", "8"};
const ArrayType EXPECTED2 = {"11", "88", "69", "96"};
const ArrayType EXPECTED4 = {"8008", "1001", "9006", "6009", "8888", "1881", "9886", "6889", "8118", "1111", "9116", "6119", "8968", "1961", "9966", "6969", "8698", "1691", "9696", "6699"};


THE_BENCHMARK(StrobogrammaticNumbers_Recursive, 4);

SIMPLE_TEST(StrobogrammaticNumbers_Recursive, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(StrobogrammaticNumbers_Recursive, TestSAMPLE2, EXPECTED2, 2);
SIMPLE_TEST(StrobogrammaticNumbers_Recursive, TestSAMPLE4, EXPECTED4, 4);


THE_BENCHMARK(StrobogrammaticNumbers_Iterative, 4);

SIMPLE_TEST(StrobogrammaticNumbers_Iterative, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(StrobogrammaticNumbers_Iterative, TestSAMPLE2, EXPECTED2, 2);
SIMPLE_TEST(StrobogrammaticNumbers_Iterative, TestSAMPLE4, EXPECTED4, 4);


THE_BENCHMARK(CountStrobogrammaticNumbersInRange, "50", "100");

SIMPLE_TEST(CountStrobogrammaticNumbersInRange, TestSAMPLE1, 3, "50", "100");
SIMPLE_TEST(CountStrobogrammaticNumbersInRange, TestSAMPLE2, 3, "0", "8");
SIMPLE_TEST(CountStrobogrammaticNumbersInRange, TestSAMPLE3, 4, "9", "100");


THE_BENCHMARK(isConfusingNumber, 89);

SIMPLE_TEST(isConfusingNumber, TestSAMPLE1, true, 6);
SIMPLE_TEST(isConfusingNumber, TestSAMPLE2, true, 89);
SIMPLE_TEST(isConfusingNumber, TestSAMPLE3, false, 11);
SIMPLE_TEST(isConfusingNumber, TestSAMPLE4, false, 25);


THE_BENCHMARK(CountConfusingNumber, 100);

SIMPLE_TEST(CountConfusingNumber, TestSAMPLE1, 19, 100);
SIMPLE_TEST(CountConfusingNumber, TestSAMPLE2, 6, 20);
