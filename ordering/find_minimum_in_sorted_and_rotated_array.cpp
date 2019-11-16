#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the minimum element in a sorted and rotated array
 *
 * @reference   https://www.geeksforgeeks.org/find-minimum-element-in-a-sorted-and-rotated-array/
 *
 * Assumes that all elements are distinct.
 */
auto FindMinInSortedAndRotatedArray(const ArrayType::const_iterator cbegin,
                                    const ArrayType::size_type length) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;
        const auto length_minus_1 = length - 1;

        if (not half or * mid < *std::prev(mid)) {
            return mid;
        }
        if (*cbegin < *std::next(cbegin, length_minus_1)) {
            return cbegin;
        }
        if (*cbegin > *mid) {
            return FindMinInSortedAndRotatedArray(cbegin, half);
        }
        return FindMinInSortedAndRotatedArray(std::next(mid), length_minus_1 - half);
    }
    return cbegin;
}

inline auto FindMinInSortedAndRotatedArray(const ArrayType &elements) {
    assert(not elements.empty());

    return *FindMinInSortedAndRotatedArray(elements.cbegin(), elements.size());
}

}//namespace


const ArrayType VALUES_EVEN = {5, 6, 1, 2, 3, 4};
const ArrayType VALUES_ODD = {2, 3, 4, 10, 40};


SIMPLE_BENCHMARK(FindMinInSortedAndRotatedArray, VALUES_EVEN);

#ifdef WANT_TESTS
class FindMinInSortedAndRotatedArrayTest: public ::testing::Test {
protected:
    void TestAllCasesOf(ArrayType elements) const {
        std::sort(elements.begin(), elements.end());
        const auto minimum_element = elements.front();

        for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
            auto sorted_elements = elements;
            std::rotate(sorted_elements.begin(), std::next(sorted_elements.begin(), i), sorted_elements.end());
            EXPECT_EQ_AND_PRINT_INPUTS(minimum_element, FindMinInSortedAndRotatedArray, sorted_elements);
        }
    }
};

#define DefineTestCase(testName, sampleArray) namespace {   \
    TEST_F(FindMinInSortedAndRotatedArrayTest, testName) {  \
        TestAllCasesOf(sampleArray);                        \
    }                                                       \
}

DefineTestCase(TestOdd, VALUES_ODD);
DefineTestCase(TestEven, VALUES_EVEN);
#endif
