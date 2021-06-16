#include "common_header.h"

#include "finding.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Sparse Search
 *
 * @reference   https://www.geeksforgeeks.org/sparse-search/
 * @reference   Search in an array of strings where non-empty strings are sorted
 *              https://www.geeksforgeeks.org/search-in-an-array-of-strings-where-non-empty-strings-are-sorted/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.5.
 *
 * Given a sorted array of strings which is interspersed with empty strings, write a
 * method to find the location of a given string.
 */
auto SparseSearch(const ArrayType &elements, const std::string_view key,
                  const int low, const int high) {
    assert(not key.empty());

    if (low > high) {
        return NOT_FOUND;
    }

    auto mid = (low + high) / 2;

    if (elements[mid].empty()) {
        for (int left = mid - 1, right = mid + 1; true; --left, ++right) {
            if (left < low and right > high) {
                return NOT_FOUND;
            }

            if (left >= low and not elements[left].empty()) {
                mid = left;
                break;
            }

            if (right <= high and not elements[right].empty()) {
                mid = right;
                break;
            }
        }
    }

    if (elements[mid] == key) {
        return mid;
    } else if (elements[mid] > key) {
        return SparseSearch(elements, key, low, mid - 1);
    } else {
        return SparseSearch(elements, key, mid + 1, high);
    }
}

inline auto SparseSearch(const ArrayType &elements, const std::string_view key) {
    return SparseSearch(elements, key, 0, elements.size() - 1);
}

}//namespace


const ArrayType SAMPLE1 = {"for", "geeks", "", "", "", "", "ide", "practice", "", "", "", "quiz"};
const ArrayType SAMPLE2 = {"for", "", "", "", "geeks", "ide", "", "practice", "", "", "quiz", "", ""};


THE_BENCHMARK(SparseSearch, SAMPLE1, "geeks");

SIMPLE_TEST(SparseSearch, TestSAMPLE1, 1, SAMPLE1, "geeks");
SIMPLE_TEST(SparseSearch, TestSAMPLE2, NOT_FOUND, SAMPLE1, "ds");
SIMPLE_TEST(SparseSearch, TestSAMPLE3, 10, SAMPLE2, "quiz");
