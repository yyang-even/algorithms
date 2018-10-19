#include "common_header.h"

#include "mathematics/numbers/gcd.h"

using ArrayType = std::vector<int>;
/** Program for array rotation
 *
 * @reference   https://www.geeksforgeeks.org/array-rotation/
 *
 * Write a function rotate(ar[], d, n) that rotates arr[] of size n by d elements.
 */
auto LeftRotateSimple(const ArrayType &arr, const ArrayType::size_type d) {
    auto output = arr;
    const auto mid = arr.cbegin() + d;
    const auto iter = std::copy(mid, arr.cend(), output.begin());
    std::copy(arr.cbegin(), mid, iter);
    return output;
}

auto LeftRotateGCD(ArrayType arr, const ArrayType::size_type d) {
    const auto step = gcd(arr.size(), d);

    for (ArrayType::size_type i = 0; i < step; ++i) {
        auto j = i;
        while (true) {
            auto k = j + d;
            if (k >= arr.size()) {
                k -= arr.size();
            }
            if (k == i) {
                break;
            }
            std::swap(arr[j], arr[k]);
            j = k;
        }
    }
    return arr;
}


const ArrayType SampleArray = {1, 2, 3, 4, 5, 6, 7};
const ArrayType ExpectedSortedArray = {3, 4, 5, 6, 7, 1, 2};
const ArrayType SampleArray2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const ArrayType ExpectedSortedArray2 = {4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3};

SIMPLE_BENCHMARK(LeftRotateSimple, SampleArray, 2);

SIMPLE_TEST(LeftRotateSimple, TestSample, ExpectedSortedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotateSimple, TestSample2, ExpectedSortedArray2, SampleArray2, 3);

SIMPLE_BENCHMARK(LeftRotateGCD, SampleArray2, 3);

SIMPLE_TEST(LeftRotateGCD, TestSample1, ExpectedSortedArray, SampleArray, 2);
SIMPLE_TEST(LeftRotateGCD, TestSample2, ExpectedSortedArray2, SampleArray2, 3);
