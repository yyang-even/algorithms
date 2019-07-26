#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Elements that occurred only once in the array
 *
 * @reference   https://www.geeksforgeeks.org/elements-that-occurred-only-once-in-the-array/
 *
 * Given an array arr that has numbers appearing twice or once. The task is to identify
 * numbers that occurred only once in the array.
 * Note: Duplicates appear side by side every time. Might be few numbers can occur one
 * time and just assume this is a right rotating array (just say an array can rotate k
 * times towards right). Order of the elements in the output doesn’t matter.
 */
auto ElementsThatOccurredOnlyOnce(const ArrayType &elements) {
    assert(elements.size() > 1ul);

    ArrayType::size_type i = 1ul;
    auto length = elements.size();

    if (elements.front() == elements.back()) {
        ++i;
        --length;
    }

    ArrayType output;
    for (; i < length; ++i) {
        const auto previous = elements[i - 1ul];
        if (elements[i] == previous) {
            ++i;
        } else {
            output.push_back(previous);
        }
    }

    if (elements[length - 1ul] != elements[length - 2ul]) {
        output.push_back(elements[length - 1ul]);
    }

    return output;
}

}//namespace


const ArrayType SAMPLE1 = {7, 7, 8, 8, 9, 1, 1, 4, 2, 2};
const ArrayType EXPECTED1 = {9, 4};
const ArrayType SAMPLE2 = { -9, -8, 4, 4, 5, 5, -1};
const ArrayType EXPECTED2 = { -9, -8, -1};
const ArrayType SAMPLE3 = {3, 7, 7, 8, 8, 9, 1, 1, 4, 2, 2, 3};
const ArrayType SAMPLE4 = {1, -9, -8, 4, 4, 5, 5, -1, 1};


SIMPLE_BENCHMARK(ElementsThatOccurredOnlyOnce, SAMPLE1);

SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE3, EXPECTED1, SAMPLE3);
SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE4, EXPECTED2, SAMPLE4);
