#include "common_header.h"


namespace {

#include "counting_sort.h"

using ArrayType = std::vector<int>;

/** Counting Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 8.2.
 * @reference   https://www.geeksforgeeks.org/counting-sort/
 * @reference   C Program for Counting Sort
 *              https://www.geeksforgeeks.org/c-program-for-counting-sort-2/
 *
 * Counting sort is efficient if the range of input data is not significantly greater
 * than the number of objects to be sorted.
 */
auto CountingSort_NoNegative(const ArrayType &values) {
    constexpr ArrayType::value_type MAXIMUM = 1 << 8;

    assert(std::all_of(values.cbegin(), values.cend(), [](const auto v) {
        return v >= 0 and v < MAXIMUM;
    }));

    ArrayType::value_type counter[MAXIMUM] = {};
    for (const auto v : values) {
        ++counter[v];
    }

    for (ArrayType::value_type i = 1; i < MAXIMUM; ++i) {
        counter[i] += counter[i - 1];
    }

    ArrayType outputs(values.size(), 0);
    for (auto riter = values.crbegin(); riter != values.crend(); ++riter) {
        outputs[--counter[*riter]] = *riter;
    }

    return outputs;
}


/**
 * @reference   C++14 Language Extensions: Generalized lambda captures
 *              https://isocpp.org/wiki/faq/cpp14-language#lambda-captures
 */
auto CountingSort(const ArrayType &values) {
    if (values.empty()) {
        return values;
    }

    const auto min_max_pair = std::minmax_element(values.cbegin(), values.cend());
    const auto RANGE = *min_max_pair.second - *min_max_pair.first + 1;

    return CountingSort(values, RANGE, [min = *min_max_pair.first](const auto v) {
        return v - min;
    });
}


/**
 * @reference   Implementing Counting Sort using map in C++
 *              https://www.geeksforgeeks.org/implementing-counting-sort-using-map-in-c/
 */
auto CountingSort_Map(ArrayType values) {
    std::map<ArrayType::value_type, std::size_t> counter;
    for (const auto v : values) {
        ++counter[v];
    }

    ArrayType::size_type i = 0;
    for (const auto &value_count_pair : counter) {
        for (std::size_t j = 0; j < value_count_pair.second; ++j) {
            values[i++] = value_count_pair.first;
        }
    }

    return values;
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

const InitializerType VALUES1 = {};
const InitializerType VALUES2 = {1};
const InitializerType VALUES3 = {1, 2};
const InitializerType VALUES4 = {2, 3, 1};
const InitializerType EXPECTED4 = {1, 2, 3};
const InitializerType VALUES5 = {4, 3, 2, 1};
const InitializerType EXPECTED5 = {1, 2, 3, 4};
const InitializerType VALUES6 = {1, 2, 3, 1, 2, 2};
const InitializerType EXPECTED6 = {1, 1, 2, 2, 2, 3};


SIMPLE_BENCHMARK(CountingSort_NoNegative, VALUES6);

SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort_NoNegative, TestSAMPLE6, EXPECTED6, VALUES6);


const InitializerType VALUES7 = {-5, -10, 0, -3, 8, 5, -1, 10};
const InitializerType EXPECTED7 = {-10, -5, -3, -1, 0, 5, 8, 10};


SIMPLE_BENCHMARK(CountingSort, VALUES6);

SIMPLE_TEST(CountingSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(CountingSort, TestSAMPLE7, EXPECTED7, VALUES7);


SIMPLE_BENCHMARK(CountingSort_Map, VALUES6);

SIMPLE_TEST(CountingSort_Map, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(CountingSort_Map, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(CountingSort_Map, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(CountingSort_Map, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(CountingSort_Map, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(CountingSort_Map, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(CountingSort_Map, TestSAMPLE7, EXPECTED7, VALUES7);
