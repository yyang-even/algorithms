#include "common_header.h"


namespace {

#include "sorted_insert.h"

using ArrayType = std::vector<int>;

/** Search, insert and delete in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/search-insert-and-delete-in-a-sorted-array/
 */
inline auto SortedInsert(ArrayType elements, const ArrayType::value_type x) {
    elements.push_back(x);
    SortedInsert(elements.begin(), std::prev(elements.end()));
    return elements;
}

}//namespace


const ArrayType SAMPLE1 = {12, 16, 20, 40, 50, 70};
const ArrayType EXPECTED_MID = {12, 16, 20, 26, 40, 50, 70};
const ArrayType EXPECTED_FRONT = {11, 12, 16, 20, 40, 50, 70};
const ArrayType EXPECTED_BACK = {12, 16, 20, 40, 50, 70, 80};


THE_BENCHMARK(SortedInsert, SAMPLE1, 26);

SIMPLE_TEST(SortedInsert, TestSAMPLE1, EXPECTED_MID, SAMPLE1, 26);
SIMPLE_TEST(SortedInsert, TestFront, EXPECTED_FRONT, SAMPLE1, EXPECTED_FRONT.front());
SIMPLE_TEST(SortedInsert, TestBack, EXPECTED_BACK, SAMPLE1, EXPECTED_BACK.back());
