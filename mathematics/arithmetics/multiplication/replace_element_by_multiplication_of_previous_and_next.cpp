#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Replace every array element by multiplication of previous and next
 *
 * @reference   https://www.geeksforgeeks.org/replace-every-array-element-by-multiplication-of-previous-and-next/
 *
 * Given an array of integers, update every element with multiplication of previous and
 * next elements with following exceptions.
 *  a) First element is replaced by multiplication of first and second.
 *  b) Last element is replaced by multiplication of last and second last.
 */
auto ReplaceElementByMultiplicationOfPreviousAndNext(ArrayType elements) {
    if (elements.size() > 1) {
        auto previous = elements.front();
        elements[0] *= elements[1];

        for (ArrayType::size_type i = 1; i < elements.size() - 1; ++i) {
            const auto current = elements[i];
            elements[i] = previous * elements[i + 1];
            previous = current;
        }

        elements[elements.size() - 1] *= previous;
    }

    return elements;
}

}//namespace


const ArrayType SAMPLE1 = {2, 3, 4, 5, 6};
const ArrayType EXPECTED1 = {6, 8, 15, 24, 30};


THE_BENCHMARK(ReplaceElementByMultiplicationOfPreviousAndNext, SAMPLE1);

SIMPLE_TEST(ReplaceElementByMultiplicationOfPreviousAndNext, TestSAMPLE1, EXPECTED1,
            SAMPLE1);
