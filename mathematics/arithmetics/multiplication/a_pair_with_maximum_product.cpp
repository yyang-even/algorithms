#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find a pair with maximum product in array of Integers
 *
 * @reference   https://www.geeksforgeeks.org/return-a-pair-with-maximum-product-in-array-of-integers/
 *
 * Given an array with both +ive and -ive integers, return a pair with highest product.
 */
inline auto PairWithMaxProduct_Sort(ArrayType elements) {
    assert(elements.size() > 1);

    std::sort(elements.begin(), elements.end());

    return std::max(elements.front() * elements[1],
                    elements.back() * *(std::prev(elements.cend(), 2)));
}


auto PairWithMaxProduct(const ArrayType &elements) {
    assert(elements.size() > 1);

    auto maximum = std::numeric_limits<ArrayType::value_type>::min();
    auto second_max = std::numeric_limits<ArrayType::value_type>::min();
    auto minimum = std::numeric_limits<ArrayType::value_type>::max();
    auto second_min = std::numeric_limits<ArrayType::value_type>::max();
    for (const auto elem : elements) {
        if (elem > maximum) {
            second_max = maximum;
            maximum = elem;
        } else if (elem > second_max) {
            second_max = elem;
        }

        if (elem < minimum) {
            second_min = minimum;
            minimum = elem;
        } else if (elem < second_min) {
            second_min = elem;
        }
    }

    return std::max(maximum * second_max, minimum * second_min);
}

}//namespace


const ArrayType SAMPLE1 = {1, 4, 3, 6, 7, 0};
const ArrayType SAMPLE2 = {-1, -3, -4, 2, 0, -5};


THE_BENCHMARK(PairWithMaxProduct_Sort, SAMPLE1);

SIMPLE_TEST(PairWithMaxProduct_Sort, TestSAMPLE1, 42, SAMPLE1);
SIMPLE_TEST(PairWithMaxProduct_Sort, TestSAMPLE2, 20, SAMPLE2);


THE_BENCHMARK(PairWithMaxProduct, SAMPLE1);

SIMPLE_TEST(PairWithMaxProduct, TestSAMPLE1, 42, SAMPLE1);
SIMPLE_TEST(PairWithMaxProduct, TestSAMPLE2, 20, SAMPLE2);
