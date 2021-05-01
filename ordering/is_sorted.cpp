#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Program to check if an array is sorted or not (Iterative and Recursive)
 *
 * @reference   https://www.geeksforgeeks.org/program-check-array-sorted-not-iterative-recursive/
 */
inline auto isSortedRecursive(const ArrayType::const_iterator cbegin,
                              const ArrayType::const_iterator cend) {
    if (cbegin == cend) {
        return true;
    }
    return *(cbegin - 1) > *cbegin ? false : isSortedRecursive(cbegin + 1, cend);
}

inline bool isSortedRecursive(const ArrayType &values) {
    return values.size() > 1 ? isSortedRecursive(values.cbegin() + 1, values.cend()) : true;
}


auto isSortedIterative(const ArrayType &values) {
    if (values.size() > 1) {
        for (auto iter = values.cbegin() + 1; iter != values.cend(); ++iter) {
            if (*(iter - 1) > *iter) {
                return false;
            }
        }
    }
    return true;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType VALUES5 = {4, 3, 2, 1};


THE_BENCHMARK(isSortedRecursive, VALUES5);

SIMPLE_TEST(isSortedRecursive, TestSAMPLE1, true, VALUES1);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE2, true, VALUES2);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE3, true, VALUES3);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE4, false, VALUES4);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE5, false, VALUES5);


THE_BENCHMARK(isSortedIterative, VALUES5);

SIMPLE_TEST(isSortedIterative, TestSAMPLE1, true, VALUES1);
SIMPLE_TEST(isSortedIterative, TestSAMPLE2, true, VALUES2);
SIMPLE_TEST(isSortedIterative, TestSAMPLE3, true, VALUES3);
SIMPLE_TEST(isSortedIterative, TestSAMPLE4, false, VALUES4);
SIMPLE_TEST(isSortedIterative, TestSAMPLE5, false, VALUES5);
