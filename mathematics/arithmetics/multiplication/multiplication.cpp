#include "common_header.h"

using ArrayType = std::vector<int>;

/** Program for multiplication of array elements
 *
 * @reference   https://www.geeksforgeeks.org/program-multiplication-array-elements/
 *
 * We are given an array and we have to calculate the product of an array using both iterative and recursive method.
 */
auto MultiplicationRecersive(const ArrayType::const_iterator cbegin,
                             const ArrayType::const_iterator cend) {
    if (cbegin == cend) {
        return 1ll;
    } else {
        return MultiplicationRecersive(cbegin + 1, cend) * (*cbegin);
    }
}
auto MultiplicationRecersive(const ArrayType &elements) {
    return MultiplicationRecersive(elements.cbegin(), elements.cend());
}


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5, 6};
const ArrayType SAMPLE2 = {1, 3, 5, 7, 9};


SIMPLE_BENCHMARK(MultiplicationRecersive, SAMPLE1);

SIMPLE_TEST(MultiplicationRecersive, TestSAMPLE1, 720, SAMPLE1);
SIMPLE_TEST(MultiplicationRecersive, TestSAMPLE2, 945, SAMPLE2);
