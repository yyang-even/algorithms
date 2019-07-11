#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Program for multiplication of array elements
 *
 * @reference   https://www.geeksforgeeks.org/program-multiplication-array-elements/
 *
 * We are given an array and we have to calculate the product of an array using both iterative and recursive method.
 */
auto Multiplication_Recersive(const ArrayType::const_iterator cbegin,
                              const ArrayType::const_iterator cend) {
    if (cbegin == cend) {
        return 1ll;
    } else {
        return Multiplication_Recersive(cbegin + 1, cend) * (*cbegin);
    }
}
auto Multiplication_Recersive(const ArrayType &elements) {
    return Multiplication_Recersive(elements.cbegin(), elements.cend());
}


/** Product of the nodes of a Singly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/product-of-the-nodes-of-a-singly-linked-list/
 */

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5, 6};
const ArrayType SAMPLE2 = {1, 3, 5, 7, 9};


SIMPLE_BENCHMARK(Multiplication_Recersive, SAMPLE1);

SIMPLE_TEST(Multiplication_Recersive, TestSAMPLE1, 720, SAMPLE1);
SIMPLE_TEST(Multiplication_Recersive, TestSAMPLE2, 945, SAMPLE2);
