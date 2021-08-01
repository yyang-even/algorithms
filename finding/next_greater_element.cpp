#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Next Greater Element
 *
 * @reference   https://www.geeksforgeeks.org/next-greater-element/
 * @reference   Next greater element in same order as input
 *              https://www.geeksforgeeks.org/next-greater-element-in-same-order-as-input/
 *
 * Given an array, print the Next Greater Element (NGE) for every element. The Next greater
 * Element for an element x is the first greater element on the right side of x in array.
 * Elements for which no greater element exist, consider next greater element as -1.
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
 * @reference   Previous greater element
 *              https://www.geeksforgeeks.org/previous-greater-element/
 *
 * @reference   The Stock Span Problem
 *              https://www.geeksforgeeks.org/the-stock-span-problem/
 *
 * The stock span problem is a financial problem where we have a series of n daily price
 * quotes for a stock and we need to calculate span of stock’s price for all n days.
 * The span Si of the stock’s price on a given day i is defined as the maximum number of
 * consecutive days just before the given day, for which the price of the stock on the
 * current day is less than or equal to its price on the given day.
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

}//namespace


const ArrayType SAMPLE1 = {4, 5, 2, 25};
const ArrayType EXPECTED1 = {5, 25, 25, -1};

const ArrayType SAMPLE2 = {4, 5, 2, 25, 10};
const ArrayType EXPECTED2 = {5, 25, 25, -1, -1};


THE_BENCHMARK(NextGreaterElement, SAMPLE1);

SIMPLE_TEST(NextGreaterElement, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(NextGreaterElement, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {100, 80, 60, 70, 60, 75, 85};
const ArrayType EXPECTED3 = {1, 1, 1, 2, 1, 4, 6};

const ArrayType SAMPLE4 = { 10, 4, 5, 90, 120, 80 };
const ArrayType EXPECTED4 = {1, 1, 2, 4, 5, 1};


THE_BENCHMARK(StockSpanProblem_Stack, SAMPLE3);

SIMPLE_TEST(StockSpanProblem_Stack, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(StockSpanProblem_Stack, TestSAMPLE4, EXPECTED4, SAMPLE4);


THE_BENCHMARK(StockSpanProblem, SAMPLE3);

SIMPLE_TEST(StockSpanProblem, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(StockSpanProblem, TestSAMPLE4, EXPECTED4, SAMPLE4);
