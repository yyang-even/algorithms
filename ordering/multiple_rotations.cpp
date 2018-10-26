#include "common_header.h"


using ArrayType = std::vector<std::size_t>;

/** Quickly find multiple left rotations of an array | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/quickly-find-multiple-left-rotations-of-an-array/
 *
 * Given an array of size n and multiple values around which we need to left rotate the array.
 * How to quickly find multiple left rotations?
 */
auto MultipleLeftRotations(const ArrayType elements, const ArrayType Ks) {
    auto temp = elements;
    for (const auto elem : elements) {
        temp.push_back(elem);
    }

    std::vector<ArrayType> outputs;
    for (const auto k : Ks) {
        const auto k_mod_n = k % elements.size();
        const auto begin = temp.cbegin() + k_mod_n;
        outputs.emplace_back(begin, begin + elements.size());
    }

    return outputs;
}


auto MultipleLeftRotationsInPlace(const ArrayType elements, const ArrayType Ks) {
    std::vector<ArrayType> outputs;
    for (const auto k : Ks) {
        const auto last = k + elements.size();
        ArrayType rotation;

        for (auto i = k; i < last; ++i) {
            rotation.push_back(elements[i % elements.size()]);
        }

        outputs.emplace_back(std::move(rotation));
    }
    return outputs;
}


const ArrayType SampleArray = {1, 3, 5, 7, 9};
const ArrayType SampleArrayK1 = {1, 3, 4, 6};
const ArrayType SampleArrayK2 = {14};
const std::vector<ArrayType> ExpectedArray = {{3, 5, 7, 9, 1},
    {7, 9, 1, 3, 5},
    {9, 1, 3, 5, 7},
    {3, 5, 7, 9, 1}
};
const std::vector<ArrayType> ExpectedArray2 = {{9, 1, 3, 5, 7}};

SIMPLE_BENCHMARK(MultipleLeftRotations, SampleArray, SampleArrayK1);

SIMPLE_TEST(MultipleLeftRotations, TestSample, ExpectedArray, SampleArray, SampleArrayK1);
SIMPLE_TEST(MultipleLeftRotations, TestSample2, ExpectedArray2, SampleArray, SampleArrayK2);

SIMPLE_BENCHMARK(MultipleLeftRotationsInPlace, SampleArray, SampleArrayK1);

SIMPLE_TEST(MultipleLeftRotationsInPlace, TestSample, ExpectedArray, SampleArray, SampleArrayK1);
SIMPLE_TEST(MultipleLeftRotationsInPlace, TestSample2, ExpectedArray2, SampleArray, SampleArrayK2);
