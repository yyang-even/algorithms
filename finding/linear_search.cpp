#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Linear Search
 *
 * @reference   https://www.geeksforgeeks.org/linear-search/
 * @reference   C/C++ Program for Linear Search
 *              https://www.geeksforgeeks.org/c-c-program-for-linear-search/
 */
auto LinearSearch_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    auto iter = elements.cbegin();
    for (; iter != elements.cend() and * iter != x; ++iter);
    return iter;
}


inline auto LinearSearch_STL(const ArrayType &elements, const ArrayType::value_type x) {
    return std::find(elements.cbegin(), elements.cend(), x);
}


/**
 * @reference   Recursive program to linearly search an element in a given array
 *              https://www.geeksforgeeks.org/recursive-c-program-linearly-search-element-given-array/
 */
auto LinearSearch_Recursive(const ArrayType::const_iterator cbegin,
                            const ArrayType::const_iterator cend, const ArrayType::value_type x) {
    if (cbegin == cend) {
        return cend;
    }
    if (*cbegin == x) {
        return cbegin;
    }
    return LinearSearch_Recursive(std::next(cbegin), cend, x);
}

auto LinearSearch_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
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
 * Given a date and an array of integer containing the numbers of the cars traveling on that date(an integer),
 * the task is to calculate the total fine collected based on the following rules:
 *     * Odd numbered cars can travel on only odd dates.
 *     * Even numbered cars on only even dates.
 *     * Otherwise a car would be fined 250 Rs.
 */
auto TotalFine(const ArrayType &car_numbers, const ArrayType::value_type date) {
    return 250 * std::count_if(car_numbers.cbegin(), car_numbers.cend(),
    [date](const auto & car) {
        return (car % 2) != (date % 2);
    });
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};


SIMPLE_BENCHMARK(LinearSearch_Iterative, Sample1, VALUES2, 110);

SIMPLE_TEST(LinearSearch_Iterative, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(LinearSearch_Iterative, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(LinearSearch_STL, LinearSearch_Iterative, TestSample1, VALUES2, 110);
SIMPLE_TEST(LinearSearch_Iterative, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(LinearSearch_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(LinearSearch_Recursive, Sample1, VALUES2, 110);

SIMPLE_TEST(LinearSearch_Recursive, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(LinearSearch_Recursive, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(LinearSearch_STL, LinearSearch_Recursive, TestSample1, VALUES2, 110);
SIMPLE_TEST(LinearSearch_Recursive, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(LinearSearch_Recursive, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(LinearSearch_Sentinel, Sample1, VALUES2, 110);

SIMPLE_TEST(LinearSearch_Sentinel, TestBegin, 0, VALUES2, VALUES2.front());
SIMPLE_TEST(LinearSearch_Sentinel, TestSample1, 6, VALUES2, 110);
SIMPLE_TEST(LinearSearch_Sentinel, TestLast, VALUES2.size() - 1, VALUES2, VALUES2.back());
SIMPLE_TEST(LinearSearch_Sentinel, TestNotExist, -1, VALUES2, 999);


const ArrayType SAMPLE1 = {3, 4, 1, 2};
const ArrayType SAMPLE2 = {1, 2, 3};


SIMPLE_BENCHMARK(TotalFine, Sample1, SAMPLE1, 15);

SIMPLE_TEST(TotalFine, TestSample1, 500, SAMPLE1, 15);
SIMPLE_TEST(TotalFine, TestSample2, 500, SAMPLE2, 16);
