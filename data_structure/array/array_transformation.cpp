#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Array Transformation
 *
 * @reference   https://massivealgorithms.blogspot.com/2020/01/leetcode-1243-array-transformation.html
 *
 * Given an initial array arr, every day you produce a new array using the array of the previous
 * day. On the i-th day, you do the following operations on the array of day i-1 to produce the
 * array of day i:
 *  If an element is smaller than both its left neighbor and its right neighbor, then this element
 *      is incremented.
 *  If an element is bigger than both its left neighbor and its right neighbor, then this element
 *      is decremented.
 *  The first and last elements never change.
 * After some days, the array does not change. Return that final array.
 */
auto ArrayTransformation(ArrayType prev) {
    const auto size = prev.size();

    auto curr = prev;
    bool changed = true;
    while (changed) {
        changed = false;
        for (std::size_t i = 1; i < size - 1; ++i) {
            if (prev[i] > prev[i - 1] and prev[i] > prev[i + 1]) {
                curr[i] = prev[i] - 1;
                changed = true;
            } else if (prev[i] < prev[i - 1] and prev[i] < prev[i + 1]) {
                curr[i] = prev[i] + 1;
                changed = true;
            } else {
                curr[i] = prev[i];
            }
        }

        std::swap(curr, prev);
    }

    return curr;
}

} //namespace


const ArrayType SAMPLE1 = {6, 2, 3, 4};
const ArrayType EXPECTED1 = {6, 3, 3, 4};

const ArrayType SAMPLE2 = {1, 6, 3, 4, 3, 5};
const ArrayType EXPECTED2 = {1, 4, 4, 4, 4, 5};


THE_BENCHMARK(ArrayTransformation, SAMPLE1);

SIMPLE_TEST(ArrayTransformation, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ArrayTransformation, TestSAMPLE2, EXPECTED2, SAMPLE2);
