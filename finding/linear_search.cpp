#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Linear Search
 *
 * @reference   https://www.geeksforgeeks.org/linear-search/
 * @reference   C/C++ Program for Linear Search
 *              https://www.geeksforgeeks.org/c-c-program-for-linear-search/
 */
inline auto
LinearSearch_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    auto iter = elements.cbegin();
    for (; iter != elements.cend() and * iter != x; ++iter);
    return iter;
}


inline auto
LinearSearch_STL(const ArrayType &elements, const ArrayType::value_type x) {
    return std::find(elements.cbegin(), elements.cend(), x);
}


/**
 * @reference   Recursive program to linearly search an element in a given array
 *              https://www.geeksforgeeks.org/recursive-c-program-linearly-search-element-given-array/
 */
inline auto
LinearSearch_Recursive(const ArrayType::const_iterator cbegin,
                       const ArrayType::const_iterator cend, const ArrayType::value_type x) {
    if (cbegin == cend) {
        return cend;
    }
    if (*cbegin == x) {
        return cbegin;
    }
    return LinearSearch_Recursive(std::next(cbegin), cend, x);
}

inline auto
LinearSearch_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
    return LinearSearch_Recursive(elements.cbegin(), elements.cend(), x);
}


/**
 * @reference   Sentinel Linear Search
 *              https://www.geeksforgeeks.org/sentinel-linear-search/
 * @reference   Search an element in an unsorted array using minimum number of comparisons
 *              https://www.geeksforgeeks.org/search-element-unsorted-array-using-minimum-number-comparisons/
 */
auto LinearSearch_Sentinel(ArrayType elements, const ArrayType::value_type x) {
    assert(not elements.empty());

    const auto last = elements.back();
    if (x == last) {
        return elements.size() - 1;
    }

    elements.back() = x;

    ArrayType::size_type i = 0;
    for (; elements[i] != x; ++i);

    return i < elements.size() - 1 ? i : -1;
}


/**
 * @reference   Calculate the total fine to be collected
 *              https://www.geeksforgeeks.org/calculate-the-total-fine-to-be-collected/
 *
 * Given a date and an array of integer containing the numbers of the cars traveling on
 * that date(an integer), the task is to calculate the total fine collected based on the
 * following rules:
 *     * Odd numbered cars can travel on only odd dates.
 *     * Even numbered cars on only even dates.
 *     * Otherwise a car would be fined 250 Rs.
 */
inline auto
TotalFine(const ArrayType &car_numbers, const ArrayType::value_type date) {
    return 250 * std::count_if(car_numbers.cbegin(), car_numbers.cend(),
    [date](const auto & car) {
        return (car % 2) != (date % 2);
    });
}


/**
 * @reference   Count Items Matching a Rule
 *              https://leetcode.com/problems/count-items-matching-a-rule/
 *
 * You are given an array items, where each items[i] = [typei, colori, namei] describes
 * the type, color, and name of the ith item. You are also given a rule represented by
 * two strings, ruleKey and ruleValue.
 * The ith item is said to match the rule if one of the following is true:
 *  ruleKey == "type" and ruleValue == typei.
 *  ruleKey == "color" and ruleValue == colori.
 *  ruleKey == "name" and ruleValue == namei.
 * Return the number of items that match the given rule.
 */


/**
 * @reference   Sign of the Product of an Array
 *              https://leetcode.com/problems/sign-of-the-product-of-an-array/
 *
 * There is a function signFunc(x) that returns:
 *  1 if x is positive.
 *  -1 if x is negative.
 *  0 if x is equal to 0.
 * You are given an integer array nums. Let product be the product of all values in the
 * array nums.
 * Return signFunc(product).
 */


/** Detect Capital
 *
 * @reference   https://leetcode.com/problems/detect-capital/
 *
 * We define the usage of capitals in a word to be right when one of the following cases
 * holds:
 *  All letters in this word are capitals, like "USA".
 *  All letters in this word are not capitals, like "leetcode".
 *  Only the first letter in this word is capital, like "Google".
 * Given a string word, return true if the usage of capitals in it is right.
 */
inline auto DetectCapital(const std::string_view word) {
    const std::size_t number_capitals =
        std::count_if(word.cbegin(), word.cend(), ToLambda(std::isupper));
    if (number_capitals == 0 or number_capitals == word.size()) {
        return true;
    }
    return number_capitals == 1 and std::isupper(word.front());
}


/**
 * @reference   Minimum Distance to the Target Element
 *              https://leetcode.com/problems/minimum-distance-to-the-target-element/
 *
 * Given an integer array nums (0-indexed) and two integers target and start, find an
 * index i such that nums[i] == target and abs(i - start) is minimized. Note that abs(x)
 * is the absolute value of x.
 * Return abs(i - start).
 * It is guaranteed that target exists in nums.
 */

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};


THE_BENCHMARK(LinearSearch_Iterative, VALUES2, 110);

SIMPLE_TEST(LinearSearch_Iterative, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(LinearSearch_Iterative, TestBegin, VALUES2.cbegin(),
            VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(LinearSearch_STL, LinearSearch_Iterative, TestSample1, VALUES2, 110);
SIMPLE_TEST(LinearSearch_Iterative, TestLast, std::prev(VALUES2.cend()),
            VALUES2, VALUES2.back());
SIMPLE_TEST(LinearSearch_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);


THE_BENCHMARK(LinearSearch_Recursive, VALUES2, 110);

SIMPLE_TEST(LinearSearch_Recursive, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(LinearSearch_Recursive, TestBegin, VALUES2.cbegin(),
            VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(LinearSearch_STL, LinearSearch_Recursive, TestSample1, VALUES2, 110);
SIMPLE_TEST(LinearSearch_Recursive, TestLast, std::prev(VALUES2.cend()),
            VALUES2, VALUES2.back());
SIMPLE_TEST(LinearSearch_Recursive, TestNotExist, VALUES2.cend(), VALUES2, 999);


THE_BENCHMARK(LinearSearch_Sentinel, VALUES2, 110);

SIMPLE_TEST(LinearSearch_Sentinel, TestBegin, 0, VALUES2, VALUES2.front());
SIMPLE_TEST(LinearSearch_Sentinel, TestSample1, 6, VALUES2, 110);
SIMPLE_TEST(LinearSearch_Sentinel, TestLast, VALUES2.size() - 1,
            VALUES2, VALUES2.back());
SIMPLE_TEST(LinearSearch_Sentinel, TestNotExist, -1, VALUES2, 999);


const ArrayType SAMPLE1 = {3, 4, 1, 2};
const ArrayType SAMPLE2 = {1, 2, 3};


THE_BENCHMARK(TotalFine, SAMPLE1, 15);

SIMPLE_TEST(TotalFine, TestSample1, 500, SAMPLE1, 15);
SIMPLE_TEST(TotalFine, TestSample2, 500, SAMPLE2, 16);


THE_BENCHMARK(DetectCapital, "USA");

SIMPLE_TEST(DetectCapital, TestSAMPLE1, true, "USA");
SIMPLE_TEST(DetectCapital, TestSAMPLE2, true, "leetcode");
SIMPLE_TEST(DetectCapital, TestSAMPLE3, true, "Google");
SIMPLE_TEST(DetectCapital, TestSAMPLE4, false, "FlaG");
