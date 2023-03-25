#include "common_header.h"

#include "arithmetic_progression.h"


namespace {

using ArrayType = std::vector<int>;

/** Sum of first n odd numbers in O(1) Complexity
 *
 * @reference   https://www.geeksforgeeks.org/sum-first-n-odd-numbers-o1-complexity/
 *
 * To find the sum of first n odd numbers we can apply odd number theorem, it states that the sum of
 * first n odd numbers is equal to the square of n.
 */
inline constexpr auto SumOfFirstNOddNumbers(const unsigned N) {
    return N * N;
}


/**
 * @reference   Average of first n odd naturals numbers
 *              https://www.geeksforgeeks.org/average-of-first-n-odd-naturals-numbers/
 */


/**
 * @reference   Sum of all odd natural numbers in range L and R
 *              https://www.geeksforgeeks.org/sum-of-all-odd-natural-numbers-in-range-l-and-r/
 */
inline constexpr auto SumOfOddNumbersTillN(const unsigned N) {
    return SumOfFirstNOddNumbers((N + 1) / 2);
}

inline constexpr auto SumOfFirstNOddNumbersInRange(const unsigned L, const unsigned R) {
    assert(L);
    assert(L <= R);

    return SumOfOddNumbersTillN(R) - SumOfOddNumbersTillN(L - 1);
}


/** Sum of first n even numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-first-n-even-numbers/
 */
inline constexpr auto SumOfFirstNEvenNumbers(const unsigned N) {
    return N * (N + 1);
}


/**
 * @reference   Average of first n even natural numbers
 *              https://www.geeksforgeeks.org/average-of-first-n-even-natural-numbers/
 */


/**
 * @reference   Can Make Arithmetic Progression From Sequence
 *              https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/
 *
 * A sequence of numbers is called an arithmetic progression if the difference between any two
 * consecutive elements is the same.
 * Given an array of numbers arr, return true if the array can be rearranged to form an arithmetic
 * progression. Otherwise, return false.
 */
auto CanMakeArithmeticProgression(ArrayType nums) {
    const int N = nums.size();
    if (N <= 2) {
        return true;
    }

    const auto [min_iter, max_iter] = std::minmax_element(nums.cbegin(), nums.cend());
    if ((*max_iter - *min_iter) % (N - 1) != 0) {
        return false;
    }

    const auto delta = (*max_iter - *min_iter) / (N - 1);
    const auto minimum = *min_iter;
    for (int i = 0; i < N;) {
        if (nums[i] == minimum + i * delta) {
            ++i;
        } else if ((nums[i] - minimum) % delta != 0) {
            return false;
        } else {
            const int pos = (nums[i] - minimum) / delta;
            if (pos < i or nums[pos] == nums[i]) {
                return false;
            }
            std::swap(nums[i], nums[pos]);
        }
    }

    return true;
}


/** Find the average of first N natural numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-average-first-n-natural-numbers/
 */
inline constexpr auto AverageOfNaturalNumbers(const unsigned N) {
    return static_cast<double>(N + 1) / 2.0;
}


/**
 * @reference   Sum of first n natural numbers
 *              https://www.geeksforgeeks.org/sum-of-first-n-natural-numbers/
 *
 * Given a positive integer n. The task is to find the sum of the sum of first n natural number.
 */
inline constexpr auto SumOfSumOfNaturals(const unsigned N) {
    return N * (N + 1) * (N + 2) / 6;
}


/**
 * @reference   Sum of all natural numbers in range L to R
 *              https://www.geeksforgeeks.org/sum-of-all-natural-numbers-in-range-l-to-r/
 */
inline constexpr auto SumOfNaturalsInRange(const unsigned L, const unsigned R) {
    assert(L);
    assert(L <= R);

    return SumOfNaturals(R) - SumOfNaturals(L - 1);
}


/**
 * @reference   Arranging Coins
 *              https://leetcode.com/problems/arranging-coins/
 *
 * You have n coins and you want to build a staircase with these coins. The staircase consists of k rows
 * where the ith row has exactly i coins. The last row of the staircase may be incomplete.
 * Given the integer n, return the number of complete rows of the staircase you will build.
 */
constexpr auto ArrangingCoins_BinarySearch(const long n) {
    long left = 0, right = n;
    while (left <= right) {
        const auto mid = (left + right) / 2;
        const long sum = SumOfNaturals(mid);

        if (sum == n) {
            return mid;
        }

        if (n < sum) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return right;
}


inline constexpr int ArrangingCoins_Formula(const long n) {
    return std::sqrt(2 * n + 0.25) - 0.5;
}


/**
 * @reference   Distribute Candies to People
 *              https://leetcode.com/problems/distribute-candies-to-people/
 *
 * We distribute some number of candies, to a row of n = num_people people in the following way:
 * We then give 1 candy to the first person, 2 candies to the second person, and so on until we give n
 * candies to the last person.
 * Then, we go back to the start of the row, giving n + 1 candies to the first person, n + 2 candies to
 * the second person, and so on until we give 2 * n candies to the last person.
 * This process
 * repeats (with us giving one more candy each time, and moving to the start of the row after we reach
 * the end) until we run out of candies.  The last person will receive all of our remaining candies (not
 * necessarily one more than the previous gift).
 * Return an array (of length num_people and sum candies) that represents the final distribution of
 * candies.
 */
auto DistributeCandies(int candies, const int num_people) {
    ArrayType result(num_people);
    for (int i = 0; candies > 0; ++i) {
        result[i % num_people] += std::min(candies, i + 1);
        candies -= i + 1;
    }

    return result;
}


/**
 * @reference   Calculate Money in Leetcode Bank
 *              https://leetcode.com/problems/calculate-money-in-leetcode-bank/
 *
 * Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.
 * He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in
 * $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous
 * Monday.
 * Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth
 * day.
 */
inline constexpr auto TotalMoney(const long n) {
    constexpr auto DAYS_PER_WEEK = 7;
    constexpr auto SUM_OF_FIRST_WEEK = 28;

    const auto full_week_count = n / DAYS_PER_WEEK;
    return ArithmeticProgressionSum(SUM_OF_FIRST_WEEK, full_week_count, DAYS_PER_WEEK) +
           ArithmeticProgressionSum(full_week_count + 1, n % DAYS_PER_WEEK, 1);
}


/**
 * @reference   Number of Zero-Filled Subarrays
 *              https://leetcode.com/problems/number-of-zero-filled-subarrays/
 *
 * Given an integer array nums, return the number of subarrays filled with 0.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 */
auto NumZeroFilledSubarrays(const ArrayType &nums) {
    long count = 0;
    long result = 0;

    for (const auto n : nums) {
        if (n == 0) {
            ++count;
        } else {
            result += count * (count + 1) / 2;
            count = 0;
        }
    }
    result += count * (count + 1) / 2;

    return result;
}

} //namespace


THE_BENCHMARK(SumOfFirstNOddNumbers, 10);

SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE1, 100, 10);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE2, 25, 5);
SIMPLE_TEST(SumOfFirstNOddNumbers, TestSAMPLE3, 4, 2);


THE_BENCHMARK(SumOfFirstNOddNumbersInRange, 2, 5);

SIMPLE_TEST(SumOfFirstNOddNumbersInRange, TestSAMPLE1, 8, 2, 5);
SIMPLE_TEST(SumOfFirstNOddNumbersInRange, TestSAMPLE2, 40, 7, 13);


const ArrayType SAMPLE1C = {3, 5, 1};
const ArrayType SAMPLE2C = {1, 2, 4};


THE_BENCHMARK(CanMakeArithmeticProgression, SAMPLE1C);

SIMPLE_TEST(CanMakeArithmeticProgression, TestSAMPLE1, true, SAMPLE1C);
SIMPLE_TEST(CanMakeArithmeticProgression, TestSAMPLE2, false, SAMPLE2C);


THE_BENCHMARK(SumOfFirstNEvenNumbers, 10);

SIMPLE_TEST(SumOfFirstNEvenNumbers, TestSAMPLE1, 20, 4);
SIMPLE_TEST(SumOfFirstNEvenNumbers, TestSAMPLE2, 420, 20);


THE_BENCHMARK(SumOfNaturals, 7);

SIMPLE_TEST(SumOfNaturals, TestSAMPLE1, 6, 3);
SIMPLE_TEST(SumOfNaturals, TestSAMPLE2, 15, 5);


THE_BENCHMARK(AverageOfNaturalNumbers, 7);

SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE1, 5.5, 10);
SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE2, 4, 7);
SIMPLE_TEST(AverageOfNaturalNumbers, TestSAMPLE3, 10.5, 20);


THE_BENCHMARK(SumOfSumOfNaturals, 3);

SIMPLE_TEST(SumOfSumOfNaturals, TestSAMPLE1, 10, 3);
SIMPLE_TEST(SumOfSumOfNaturals, TestSAMPLE2, 4, 2);
SIMPLE_TEST(SumOfSumOfNaturals, TestSAMPLE3, 20, 4);


THE_BENCHMARK(SumOfNaturalsInRange, 2, 5);

SIMPLE_TEST(SumOfNaturalsInRange, TestSAMPLE1, 14, 2, 5);
SIMPLE_TEST(SumOfNaturalsInRange, TestSAMPLE2, 165, 10, 20);


THE_BENCHMARK(ArrangingCoins_BinarySearch, 5);

SIMPLE_TEST(ArrangingCoins_BinarySearch, TestSAMPLE1, 2, 5);
SIMPLE_TEST(ArrangingCoins_BinarySearch, TestSAMPLE2, 3, 8);
SIMPLE_TEST(ArrangingCoins_BinarySearch, TestSAMPLE3, 2, 3);


THE_BENCHMARK(ArrangingCoins_Formula, 5);

SIMPLE_TEST(ArrangingCoins_Formula, TestSAMPLE1, 2, 5);
SIMPLE_TEST(ArrangingCoins_Formula, TestSAMPLE2, 3, 8);
SIMPLE_TEST(ArrangingCoins_Formula, TestSAMPLE3, 2, 3);


const ArrayType EXPECTED1 = {1, 2, 3, 1};
const ArrayType EXPECTED2 = {5, 2, 3};


THE_BENCHMARK(DistributeCandies, 7, 4);

SIMPLE_TEST(DistributeCandies, TestSAMPLE1, EXPECTED1, 7, 4);
SIMPLE_TEST(DistributeCandies, TestSAMPLE2, EXPECTED2, 10, 3);


THE_BENCHMARK(TotalMoney, 20);

SIMPLE_TEST(TotalMoney, TestSAMPLE1, 96, 20);
SIMPLE_TEST(TotalMoney, TestSAMPLE2, 37, 10);
SIMPLE_TEST(TotalMoney, TestSAMPLE3, 10, 4);


const ArrayType SAMPLE1Z = {1, 3, 0, 0, 2, 0, 0, 4};
const ArrayType SAMPLE2Z = {0, 0, 0, 2, 0, 0};
const ArrayType SAMPLE3Z = {2, 10, 2019};


THE_BENCHMARK(NumZeroFilledSubarrays, SAMPLE1Z);

SIMPLE_TEST(NumZeroFilledSubarrays, TestSAMPLE1, 6, SAMPLE1Z);
SIMPLE_TEST(NumZeroFilledSubarrays, TestSAMPLE2, 9, SAMPLE2Z);
SIMPLE_TEST(NumZeroFilledSubarrays, TestSAMPLE3, 0, SAMPLE3Z);
