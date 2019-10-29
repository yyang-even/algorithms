#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Binary Search
 *
 * @reference   https://www.geeksforgeeks.org/binary-search/
 * @reference   C Program for Binary Search (Recursive and Iterative)
 *              https://www.geeksforgeeks.org/c-program-for-binary-search-recursive-and-iterative/
 * @reference   Linear Search vs Binary Search
 *              https://www.geeksforgeeks.org/linear-search-vs-binary-search/
 * @reference   Binary Search a String
 *              https://www.geeksforgeeks.org/binary-search-a-string/
 */
auto BinarySearch_Recursive(const ArrayType::const_iterator cbegin,
                            const ArrayType::size_type length, const ArrayType::const_iterator cend,
                            const ArrayType::value_type x) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x) {
            return mid;
        }
        if (*mid > x) {
            return BinarySearch_Recursive(cbegin, half, cend, x);
        }
        return BinarySearch_Recursive(std::next(mid), length - half - 1, cend, x);
    }

    return cend;
}

auto BinarySearch_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_Recursive(elements.cbegin(), elements.size(), elements.cend(), x);
}


inline auto BinarySearch_STL(const ArrayType &elements, const ArrayType::value_type x) {
    return std::lower_bound(elements.cbegin(), elements.cend(), x);
}


auto BinarySearch_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x) {
            return mid;
        }
        if (*mid > x) {
            length = half;
        } else {
            cbegin = std::next(mid);
            length -= (half + 1);
        }
    }

    return elements.cend();
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {2, 3, 4, 10, 40};


SIMPLE_BENCHMARK(BinarySearch_Recursive, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Recursive, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL, BinarySearch_Recursive, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Recursive, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(BinarySearch_Iterative, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Iterative, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL, BinarySearch_Iterative, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);
