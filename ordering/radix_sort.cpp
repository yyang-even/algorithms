#include "common_header.h"

#include "counting_sort.h"


namespace {

using ArrayType = std::vector<int>;

/** Radix Sort
 *
 * @reference   https://www.geeksforgeeks.org/radix-sort/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 8.3.
 */
auto RadixSort(ArrayType values) {
    if (values.empty()) {
        return values;
    }

    const auto max_value = *std::max_element(values.cbegin(), values.cend());
    constexpr auto BASE = 10;
    for (ArrayType::value_type mask = 1; max_value / mask > 0; mask *= BASE) {
        values = CountingSort(values, BASE, [mask](const auto v) {
            return (v / mask) % BASE;
        });
        std::cout << values << std::endl;
    }

    return values;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};
const ArrayType VALUES6 = {170, 45, 75, 90, 802, 24, 2, 66};
const ArrayType EXPECTED6 = {2, 24, 45, 66, 75, 90, 170, 802};


SIMPLE_BENCHMARK(RadixSort, VALUES6);

SIMPLE_TEST(RadixSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(RadixSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(RadixSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(RadixSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(RadixSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(RadixSort, TestSAMPLE6, EXPECTED6, VALUES6);
