#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** First digit in product of an array of numbers
 *
 * @reference   https://www.geeksforgeeks.org/first-digit-in-product-of-an-array-of-numbers/
 */
inline ArrayType::value_type
FirstDigitInProductOfArray(const ArrayType &elements) {
    const auto S = std::accumulate(elements.cbegin(), elements.cend(), 0.0,
    [](const auto s, const auto one_element) {
        return s + std::log10(one_element);
    });

    const auto fractional_S = S - std::floor(S);

    return std::pow(10, fractional_S);
}

}//namespace


const ArrayType SAMPLE1 = {5, 8, 3, 7};
const ArrayType SAMPLE2 = {6, 7, 9};


THE_BENCHMARK(FirstDigitInProductOfArray, SAMPLE1);

SIMPLE_TEST(FirstDigitInProductOfArray, TestSAMPLE1, 8, SAMPLE1);
SIMPLE_TEST(FirstDigitInProductOfArray, TestSAMPLE2, 3, SAMPLE2);
