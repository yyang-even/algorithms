#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Next Greater Element
 *
 * @reference   https://www.geeksforgeeks.org/next-greater-element/
 * @reference   Next greater element in same order as input
 *              https://www.geeksforgeeks.org/next-greater-element-in-same-order-as-input/
 *
 * Given an array, print the Next Greater Element (NGE) for every element. The Next greater Element for
 * an element x is the first greater element on the right side of x in array.  Elements for which no
 * greater element exist, consider next greater element as -1.
 *
 * @reference   Special Data Structure: Monotonic Stack
 *              https://labuladong.gitbook.io/algo-en/ii.-data-structure/monotonicstack
 */
auto NextGreaterElement(const ArrayType &elements) {
    ArrayType result(elements.size(), -1);

    std::stack<ArrayType::value_type> s;
    for (int i = elements.size() - 1; i >= 0; --i) {
        while (not s.empty() and s.top() <= elements[i]) {
            s.pop();
        }

        if (not s.empty()) {
            result[i] = s.top();
        }

        s.push(elements[i]);
    }

    return result;
}


/**
 * @reference   Final Prices With a Special Discount in a Shop
 *              https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/
 *
 * You are given an integer array prices where prices[i] is the price of the ith item in a shop.
 * There is a special discount for items in the shop. If you buy the ith item, then you will receive a
 * discount equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <=
 * prices[i]. Otherwise, you will not receive any discount at all.
 * Return an integer array answer where answer[i] is the final price you will pay for the ith item of
 * the shop, considering the special discount.
 */


/**
 * @reference   Daily Temperatures
 *              https://leetcode.com/problems/daily-temperatures/
 *
 * Given an array of integers temperatures represents the daily temperatures, return an array answer
 * such that answer[i] is the number of days you have to wait after the ith day to get a warmer
 * temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
 */
auto DailyTemperatures(const ArrayType &temperatures) {
    ArrayType result(temperatures.size(), 0);
    int hottest = 0;

    for (int i = temperatures.size() - 1; i >= 0; --i) {
        if (temperatures[i] >= hottest) {
            hottest = temperatures[i];
            continue;
        }

        int days = 1;
        while (temperatures[i + days] <= temperatures[i]) {
            days += result[i + days];
        }
        result[i] = days;
    }

    return result;
}


/**
 * @reference   Next Greater Element I
 *              https://leetcode.com/problems/next-greater-element-i/
 *
 * The next greater element of some element x in an array is the first greater element that is to the
 * right of x in the same array.
 * You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of
 * nums2.
 * For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the
 * next greater element of nums2[j] in nums2. If there is no next greater element, then the answer for
 * this query is -1.
 * Return an array ans of length nums1.length such that ans[i] is the next greater element as described
 * above.
 *  1 <= nums1.length <= nums2.length <= 1000
 *  0 <= nums1[i], nums2[i] <= 104
 *  All integers in nums1 and nums2 are unique.
 *  All the integers of nums1 also appear in nums2.
 * Follow up: Could you find an O(nums1.length + nums2.length) solution?
 */
auto TwoArrayNextGreaterElement(const ArrayType &sub, const ArrayType &an_array) {
    std::unordered_map<int, int> index_map;
    for (std::size_t i = 0; i < sub.size(); ++i) {
        index_map[sub[i]] = i;
    }

    ArrayType result(sub.size(), -1);
    std::stack<ArrayType::value_type> next_greaters;
    for (int i = an_array.size() - 1; i >= 0; --i) {
        while (not next_greaters.empty() and next_greaters.top() <= an_array[i]) {
            next_greaters.pop();
        }

        if (not next_greaters.empty()) {
            const auto iter = index_map.find(an_array[i]);
            if (iter != index_map.cend()) {
                result[iter->second] = next_greaters.top();
            }
        }

        next_greaters.push(an_array[i]);
    }

    return result;
}


/**
 * @reference   Next Greater Element II
 *              https://leetcode.com/problems/next-greater-element-ii/
 *
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]),
 * return the next greater number for every element in nums.
 * The next greater number of a number x is the first greater number to its traversing-order next in the
 * array, which means you could search circularly to find its next greater number. If it doesn't exist,
 * return -1 for this number.
 */
auto CircularNextGreaterElement(const ArrayType &nums) {
    const int N = nums.size();
    ArrayType result(N, -1);

    std::stack<int> s;
    for (int i = N * 2 - 1; i >= 0; --i) {
        const auto index = i % N;
        while (not s.empty() and s.top() <= nums[index]) {
            s.pop();
        }

        if (i < N and not s.empty()) {
            result[i] = s.top();
        }

        s.push(nums[index]);
    }

    return result;
}


/**
 * @reference   Next Greater Element III
 *              https://leetcode.com/problems/next-greater-element-iii/
 *
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in
 * the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does
 * not fit in 32-bit integer, return -1.
 */
int NextGreaterElement_STL(const int n) {
    auto str = std::to_string(n);
    if (std::next_permutation(str.begin(), str.end())) {
        const auto result = stol(str);
        if (result <= INT_MAX) {
            return result;
        }
    }

    return -1;
}


/**
 * @reference   Previous greater element
 *              https://www.geeksforgeeks.org/previous-greater-element/
 *
 * @reference   The Stock Span Problem
 *              https://www.geeksforgeeks.org/the-stock-span-problem/
 *
 * The stock span problem is a financial problem where we have a series of n daily price quotes for a
 * stock and we need to calculate span of stock’s price for all n days.  The span Si of the stock’s
 * price on a given day i is defined as the maximum number of consecutive days just before the given
 * day, for which the price of the stock on the current day is less than or equal to its price on the
 * given day.
 */
auto StockSpanProblem_Stack(const ArrayType &prices) {
    ArrayType result;

    std::stack<ArrayType::size_type> s;
    for (ArrayType::size_type i = 0; i < prices.size(); ++i) {
        while (not s.empty() and prices[s.top()] <= prices[i]) {
            s.pop();
        }

        result.push_back(s.empty() ? (i + 1) : (i - s.top()));

        s.push(i);
    }

    return result;
}


auto StockSpanProblem(const ArrayType &prices) {
    ArrayType result = {1};

    for (ArrayType::size_type i = 1; i < prices.size(); ++i) {
        ArrayType::size_type counter = 1;
        while (i >= counter and prices[i] >= prices[i - counter]) {
            counter += result[i - counter];
        }
        result.push_back(counter);
    }

    return result;
}


/**
 * @reference   Online Stock Span
 *              https://leetcode.com/problems/online-stock-span/
 *
 * Design an algorithm that collects daily price quotes for some stock and returns the span of that
 * stock's price for the current day.
 * The span of the stock's price today is defined as the maximum number of consecutive days (starting
 * from today and going backward) for which the stock price was less than or equal to today's price.
 *  For example, if the price of a stock over the next 7 days were [100,80,60,70,60,75,85], then the
 *  stock spans would be [1,1,1,2,1,4,6].
 * Implement the StockSpanner class:
 *  StockSpanner() Initializes the object of the class.
 *  int next(int price) Returns the span of the stock's price given that today's price is price.
 */
class StockSpanner {
    std::stack<std::pair<int, int>> s;

public:
    auto next(const int price) {
        int result = 1;
        while (not s.empty() and s.top().first <= price) {
            result += s.top().second;
            s.pop();
        }

        s.emplace(price, result);

        return result;
    }
};

auto testStockSpanner(const ArrayType prices) {
    StockSpanner spanner;
    ArrayType result;

    for (const auto p : prices) {
        result.push_back(spanner.next(p));
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {4, 5, 2, 25};
const ArrayType EXPECTED1 = {5, 25, 25, -1};

const ArrayType SAMPLE2 = {4, 5, 2, 25, 10};
const ArrayType EXPECTED2 = {5, 25, 25, -1, -1};


THE_BENCHMARK(NextGreaterElement, SAMPLE1);

SIMPLE_TEST(NextGreaterElement, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(NextGreaterElement, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {100, 80, 60, 70, 60, 75, 85};
const ArrayType EXPECTED3 = {1, 1, 1, 2, 1, 4, 6};

const ArrayType SAMPLE4 = {10, 4, 5, 90, 120, 80};
const ArrayType EXPECTED4 = {1, 1, 2, 4, 5, 1};


THE_BENCHMARK(StockSpanProblem_Stack, SAMPLE3);

SIMPLE_TEST(StockSpanProblem_Stack, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(StockSpanProblem_Stack, TestSAMPLE4, EXPECTED4, SAMPLE4);


THE_BENCHMARK(StockSpanProblem, SAMPLE3);

SIMPLE_TEST(StockSpanProblem, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(StockSpanProblem, TestSAMPLE4, EXPECTED4, SAMPLE4);


const ArrayType SAMPLE1S = {4, 1, 2};
const ArrayType SAMPLE1A = {1, 3, 4, 2};
const ArrayType EXPECTED1T = {-1, 3, -1};

const ArrayType SAMPLE2S = {2, 4};
const ArrayType SAMPLE2A = {1, 2, 3, 4};
const ArrayType EXPECTED2T = {3, -1};


THE_BENCHMARK(TwoArrayNextGreaterElement, SAMPLE1S, SAMPLE1A);

SIMPLE_TEST(TwoArrayNextGreaterElement, TestSAMPLE1, EXPECTED1T, SAMPLE1S, SAMPLE1A);
SIMPLE_TEST(TwoArrayNextGreaterElement, TestSAMPLE2, EXPECTED2T, SAMPLE2S, SAMPLE2A);


const ArrayType SAMPLE1C = {1, 2, 1};
const ArrayType EXPECTED1C = {2, -1, 2};

const ArrayType SAMPLE2C = {1, 2, 3, 4, 3};
const ArrayType EXPECTED2C = {2, 3, 4, -1, 4};


THE_BENCHMARK(CircularNextGreaterElement, SAMPLE1C);

SIMPLE_TEST(CircularNextGreaterElement, TestSAMPLE1, EXPECTED1C, SAMPLE1C);
SIMPLE_TEST(CircularNextGreaterElement, TestSAMPLE2, EXPECTED2C, SAMPLE2C);


THE_BENCHMARK(NextGreaterElement_STL, 12);

SIMPLE_TEST(NextGreaterElement_STL, TestSAMPLE1, 21, 12);
SIMPLE_TEST(NextGreaterElement_STL, TestSAMPLE2, -1, 21);


const ArrayType SAMPLE1D = {73, 74, 75, 71, 69, 72, 76, 73};
const ArrayType EXPECTED1D = {1, 1, 4, 2, 1, 1, 0, 0};

const ArrayType SAMPLE2D = {30, 40, 50, 60};
const ArrayType EXPECTED2D = {1, 1, 1, 0};

const ArrayType SAMPLE3D = {30, 60, 90};
const ArrayType EXPECTED3D = {1, 1, 0};


THE_BENCHMARK(DailyTemperatures, SAMPLE1D);

SIMPLE_TEST(DailyTemperatures, TestSAMPLE1, EXPECTED1D, SAMPLE1D);
SIMPLE_TEST(DailyTemperatures, TestSAMPLE2, EXPECTED2D, SAMPLE2D);
SIMPLE_TEST(DailyTemperatures, TestSAMPLE3, EXPECTED3D, SAMPLE3D);


const ArrayType SAMPLE1SS = {100, 80, 60, 70, 60, 75, 85};
const ArrayType EXPECTED1SS = {1, 1, 1, 2, 1, 4, 6};


THE_BENCHMARK(testStockSpanner, SAMPLE1SS);

SIMPLE_TEST(testStockSpanner, TestSAMPLE1, EXPECTED1SS, SAMPLE1SS);
