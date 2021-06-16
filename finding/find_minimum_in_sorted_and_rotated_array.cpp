#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

#include "find_minimum_in_sorted_and_rotated_array.h"


inline auto FindMinInSortedAndRotatedArray(const ArrayType &elements) {
    assert(not elements.empty());

    return *FindMinInSortedAndRotatedArray(elements.cbegin(), elements.size());
}


/** Maximum element in a sorted and rotated array
 *
 * @reference   https://www.geeksforgeeks.org/maximum-element-in-a-sorted-and-rotated-array/
 */


/** Sort a Rotated Sorted Array
 *
 * @reference   https://www.geeksforgeeks.org/sort-rotated-sorted-array/
 */

}//namespace


const ArrayType VALUES_EVEN = {5, 6, 1, 2, 3, 4};
const ArrayType VALUES_ODD = {2, 3, 4, 10, 40};


THE_BENCHMARK(FindMinInSortedAndRotatedArray, VALUES_EVEN);

#ifdef WANT_TESTS
class FindMinInSortedAndRotatedArrayTest: public ::testing::Test {
protected:
    void TestAllCasesOf(ArrayType elements) const {
        std::sort(elements.begin(), elements.end());
        const auto minimum_element = elements.front();

        for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
            auto sorted_elements = elements;
            std::rotate(
                sorted_elements.begin(), std::next(sorted_elements.begin(), i), sorted_elements.end());
            EXPECT_EQ_AND_PRINT_INPUTS(
                minimum_element, FindMinInSortedAndRotatedArray, sorted_elements);
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
