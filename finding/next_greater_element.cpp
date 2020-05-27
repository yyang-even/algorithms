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
 */

}//namespace


const ArrayType SAMPLE1 = {4, 5, 2, 25};
const ArrayType EXPECTED1 = {5, 25, 25, -1};

const ArrayType SAMPLE2 = {4, 5, 2, 25, 10};
const ArrayType EXPECTED2 = {5, 25, 25, -1, -1};


SIMPLE_BENCHMARK(NextGreaterElement, SAMPLE1);

SIMPLE_TEST(NextGreaterElement, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(NextGreaterElement, TestSAMPLE2, EXPECTED2, SAMPLE2);
