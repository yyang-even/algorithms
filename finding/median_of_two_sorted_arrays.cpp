#include "common_header.h"

#include "ordering/median.h"


namespace {

using ArrayType = std::vector<int>;

inline constexpr auto
MedianOf4(const ArrayType::value_type smaller_one,
          const ArrayType::value_type greater_one,
          const ArrayType::value_type smaller_two,
          const ArrayType::value_type greater_two) {
    assert(smaller_one <= greater_one);
    assert(smaller_two <= greater_two);

    return std::pair(std::max(smaller_one, smaller_two),
                     std::min(greater_one, greater_two));
}

/** Median of two sorted arrays of same size
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 9.3-8.
 * @reference   Median of two sorted arrays of same size
 *              https://www.geeksforgeeks.org/median-of-two-sorted-arrays/
 *
 * Note: Since size of the set for which we are looking for median is even (2n), we need
 * take average of middle two numbers and return floor of the average.
 */
auto MedianOfTwoSortedArrays_SameSize(const ArrayType::const_iterator &cbegin_one,
                                      const ArrayType::const_iterator &cbegin_two, const ArrayType::size_type length) {
    assert(length);

    if (length == 1) {
        return (*cbegin_one + *cbegin_two) / 2;
    }
    if (length == 2) {
        const auto median_pair = MedianOf4(*cbegin_one, *std::next(cbegin_one), *cbegin_two,
                                           *std::next(cbegin_two));
        return (median_pair.first + median_pair.second) / 2;
    }

    const auto is_even = ((length % 2) == 0);
    const auto half = length / 2;
    const auto mid_iter_one = cbegin_one + half;
    const auto mid_iter_two = cbegin_two + half;
    ArrayType::value_type mid_value_one = 0;
    ArrayType::value_type mid_value_two = 0;
    auto before_mid_one = mid_iter_one;
    auto before_mid_two = mid_iter_two;

    if (is_even) {
        std::advance(before_mid_one, -1);
        mid_value_one = (*before_mid_one + *mid_iter_one) / 2;
        std::advance(before_mid_two, -1);
        mid_value_two = (*before_mid_two + *mid_iter_two) / 2;
    } else {
        mid_value_one = *mid_iter_one;
        mid_value_two = *mid_iter_two;
    }

    if (mid_value_one == mid_value_two) {
        return mid_value_one;
    }
    if (mid_value_one < mid_value_two) {
        if (is_even) {
            return MedianOfTwoSortedArrays_SameSize(before_mid_one, cbegin_two, length - half + 1);
        }
        return MedianOfTwoSortedArrays_SameSize(mid_iter_one, cbegin_two, length - half);
    } else {
        if (is_even) {
            return MedianOfTwoSortedArrays_SameSize(before_mid_two, cbegin_one, length - half + 1);
        }
        return MedianOfTwoSortedArrays_SameSize(mid_iter_two, cbegin_one, length - half);
    }
}

inline auto
MedianOfTwoSortedArrays_SameSize(const ArrayType &array_one,
                                 const ArrayType &array_two) {
    assert(array_one.size() == array_two.size());
    assert(std::is_sorted(array_one.cbegin(), array_one.cend()));
    assert(std::is_sorted(array_two.cbegin(), array_two.cend()));

    return MedianOfTwoSortedArrays_SameSize(
               array_one.cbegin(), array_two.cbegin(), array_one.size());
}


/** Median of two sorted arrays of different sizes
 *
 * @reference   https://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
 * @reference   Median of two sorted arrays of different sizes | Set 1 (Linear)
 *              https://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes-set-1-linear/
 */
double MedianOfTwoSortedArrays_DiffSize_Merge(const ArrayType &array_one,
                                              const ArrayType &array_two) {
    assert(not(array_one.empty() and array_two.empty()));
    assert(std::is_sorted(array_one.cbegin(), array_one.cend()));
    assert(std::is_sorted(array_two.cbegin(), array_two.cend()));

    auto iter_one = array_one.cbegin();
    auto iter_two = array_two.cbegin();
    ArrayType::value_type before_mid = 0;
    ArrayType::value_type mid = 0;
    const auto total_length = array_one.size() + array_two.size();

    for (ArrayType::size_type i = 0; i <= total_length / 2; ++i) {
        before_mid = mid;
        if (iter_one == array_one.cend()) {
            mid = *(iter_two++);
        } else if (iter_two == array_two.cend()) {
            mid = *(iter_one++);
        } else {
            if (*iter_one < *iter_two) {
                mid = *(iter_one++);
            } else {
                mid = *(iter_two++);
            }
        }
    }

    if (total_length % 2 == 0) {
        return (mid + before_mid) / 2.0;
    }
    return mid;
}


inline constexpr auto
MedianOf3(const ArrayType::value_type x, const ArrayType::value_type smaller,
          const ArrayType::value_type greater) {
    assert(smaller <= greater);
    if (x < smaller) {
        return smaller;
    }
    if (x > greater) {
        return greater;
    }
    return x;
}


double MedianOfTwoSortedArrays_DiffSize_Complex(
    const ArrayType::const_iterator &cbegin_shorter,
    const ArrayType::size_type length_shorter,
    const ArrayType::const_iterator &cbegin_longer,
    const ArrayType::size_type length_longer) {
    if (length_shorter == 0) {
        return Median_Sorted(cbegin_longer, length_longer);
    }

    const auto half_longer = length_longer / 2;
    const auto mid_longer = std::next(cbegin_longer, half_longer);

    if (length_shorter == 1) {
        if (length_longer == 1) {
            return (*cbegin_shorter + *cbegin_longer) / 2.0;
        }

        if (length_longer % 2 == 1) {
            return (*mid_longer +
                    MedianOf3(*cbegin_shorter, *std::prev(mid_longer), *std::next(mid_longer))) / 2.0;
        }

        return MedianOf3(*mid_longer, *std::prev(mid_longer), *cbegin_shorter);

    } else if (length_shorter == 2) {
        if (length_longer == 2) {
            const auto median_pair = MedianOf4(*cbegin_shorter, *std::next(cbegin_shorter),
                                               *cbegin_longer, *std::next(cbegin_longer));
            return (median_pair.first + median_pair.second) / 2.0;
        }

        if (length_longer % 2 == 1) {
            const auto median_pair = MedianOf4(*cbegin_shorter, *std::next(cbegin_shorter),
                                               *std::prev(mid_longer), *std::next(mid_longer));
            if (median_pair.first < median_pair.second) {
                return MedianOf3(*mid_longer, median_pair.first, median_pair.second);
            }
            return MedianOf3(*mid_longer, median_pair.second, median_pair.first);
        }

        auto median_pair = MedianOf4(*cbegin_shorter, *std::next(cbegin_shorter),
                                     *std::prev(mid_longer, 2), *std::next(mid_longer));
        if (median_pair.first < median_pair.second) {
            median_pair = MedianOf4(*std::prev(mid_longer), *mid_longer,
                                    median_pair.first, median_pair.second);
        } else {
            median_pair = MedianOf4(*std::prev(mid_longer), *mid_longer,
                                    median_pair.second, median_pair.first);
        }
        return (median_pair.first + median_pair.second) / 2.0;
    }

    const auto index_shorter = (length_shorter - 1) / 2;
    const auto index_longer = (length_longer - 1) / 2;
    const auto iter_shorter = std::next(cbegin_shorter, index_shorter);
    const auto iter_longer = std::next(cbegin_longer, index_longer);
    const auto half_shorter = length_shorter / 2;

    if (*iter_shorter <= *iter_longer) {
        return MedianOfTwoSortedArrays_DiffSize_Complex(iter_shorter, half_shorter + 1,
                                                        cbegin_longer, length_longer - index_shorter);
    }
    return MedianOfTwoSortedArrays_DiffSize_Complex(cbegin_shorter, half_shorter + 1,
                                                    std::next(cbegin_longer, index_shorter), length_longer - index_shorter);
}

inline auto
MedianOfTwoSortedArrays_DiffSize_Complex(const ArrayType &array_one,
                                         const ArrayType &array_two) {
    assert(std::is_sorted(array_one.cbegin(), array_one.cend()));
    assert(std::is_sorted(array_two.cbegin(), array_two.cend()));

    if (array_one.size() > array_two.size()) {
        return MedianOfTwoSortedArrays_DiffSize_Complex(array_two.cbegin(), array_two.size(),
                                                        array_one.cbegin(), array_one.size());
    }
    return MedianOfTwoSortedArrays_DiffSize_Complex(array_one.cbegin(), array_one.size(),
                                                    array_two.cbegin(), array_two.size());
}


/** Median of two sorted arrays with different sizes in O(log(min(n, m)))
 *
 * @reference   https://www.geeksforgeeks.org/median-two-sorted-arrays-different-sizes-ologminn-m/
 */
double MedianOfTwoSortedArrays_DiffSize_Half(const ArrayType &array_one,
                                             const ArrayType &array_two) {
    assert(std::is_sorted(array_one.cbegin(), array_one.cend()));
    assert(std::is_sorted(array_two.cbegin(), array_two.cend()));

    const int length_one = array_one.size(), length_two = array_two.size();
    int min_index = 0, max_index = length_one, i_one = 0, i_two = 0, median = 0;

    while (min_index <= max_index) {
        i_one = (min_index + max_index) / 2;
        i_two = ((length_one + length_two + 1) / 2) - i_one;

        if (i_one < length_one and i_two > 0 and array_two[i_two - 1] > array_one[i_one]) {
            min_index = i_one + 1;
        } else if (i_one > 0 and i_two < length_two and
                   array_two[i_two] < array_one[i_one - 1]) {
            max_index = i_one - 1;
        } else {
            if (i_one == 0) {
                median = array_two[i_two - 1];
            } else if (i_two == 0) {
                median = array_one[i_one - 1];
            } else {
                median = std::max(array_one[i_one - 1], array_two[i_two - 1]);
            }
            break;
        }
    }

    if ((length_one + length_two) % 2 == 1) {
        return median;
    }

    if (i_one == length_one) {
        return (median + array_two[i_two]) / 2.0;
    }

    if (i_two == length_two) {
        return (median + array_one[i_one]) / 2.0;
    }

    return (median + std::min(array_one[i_one], array_two[i_two])) / 2.0;
}

}//namespace


const ArrayType SAMPLE1_ONE = {1, 12, 15, 26, 38};
const ArrayType SAMPLE1_TWO = {2, 13, 17, 30, 45};
const ArrayType SAMPLE2_ONE = {1, 2, 3, 6};
const ArrayType SAMPLE2_TWO = {4, 6, 8, 10};
const ArrayType SAMPLE3_ONE = {3, 8};
const ArrayType SAMPLE3_TWO = {2, 9};


THE_BENCHMARK(MedianOfTwoSortedArrays_SameSize, SAMPLE1_ONE, SAMPLE1_TWO);

SIMPLE_TEST(MedianOfTwoSortedArrays_SameSize, TestSAMPLE1, 16,
            SAMPLE1_ONE, SAMPLE1_TWO);
SIMPLE_TEST(MedianOfTwoSortedArrays_SameSize, TestSAMPLE2, 5, SAMPLE2_ONE, SAMPLE2_TWO);
SIMPLE_TEST(MedianOfTwoSortedArrays_SameSize, TestSAMPLE3, 5, SAMPLE3_ONE, SAMPLE3_TWO);


const ArrayType SAMPLE4_ONE = {1, 12, 15, 26, 38};
const ArrayType SAMPLE4_TWO = {2, 13, 24};


THE_BENCHMARK(MedianOfTwoSortedArrays_DiffSize_Merge, SAMPLE4_ONE, SAMPLE4_TWO);

SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Merge, TestSAMPLE1, 16,
                   SAMPLE1_ONE, SAMPLE1_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Merge, TestSAMPLE2, 5,
                   SAMPLE2_ONE, SAMPLE2_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Merge, TestSAMPLE3, 5.5,
                   SAMPLE3_ONE, SAMPLE3_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Merge, TestSAMPLE4, 14,
                   SAMPLE4_ONE, SAMPLE4_TWO);


const ArrayType EMPTY = {};
const ArrayType CASE1_ONE = {900};
const ArrayType CASE2_TWO = {5, 10, 12, 15, 20};
const ArrayType CASE3_TWO = {5, 8, 10, 20};


THE_BENCHMARK(MedianOfTwoSortedArrays_DiffSize_Complex, SAMPLE4_ONE, SAMPLE4_TWO);

SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestSAMPLE1, 16,
                   SAMPLE1_ONE, SAMPLE1_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestSAMPLE2, 5,
                   SAMPLE2_ONE, SAMPLE2_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestCase4, 5.5,
                   SAMPLE3_ONE, SAMPLE3_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestSAMPLE4, 14,
                   SAMPLE4_ONE, SAMPLE4_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestSAMPLE4_Reverse, 14,
                   SAMPLE4_TWO, SAMPLE4_ONE);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestCase0, 13,
                   EMPTY, SAMPLE4_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestCase1,
                   CASE1_ONE.front(), CASE1_ONE, CASE1_ONE);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestCase2, 13.5,
                   CASE1_ONE, CASE2_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestCase3, 10,
                   CASE1_ONE, CASE3_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestCase5, 10,
                   SAMPLE3_TWO, CASE2_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Complex, TestCase6, 8.5,
                   SAMPLE3_TWO, CASE3_TWO);


THE_BENCHMARK(MedianOfTwoSortedArrays_DiffSize_Half, SAMPLE4_ONE, SAMPLE4_TWO);

SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestSAMPLE1, 16,
                   SAMPLE1_ONE, SAMPLE1_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestSAMPLE2, 5,
                   SAMPLE2_ONE, SAMPLE2_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestCase4, 5.5,
                   SAMPLE3_ONE, SAMPLE3_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestSAMPLE4, 14,
                   SAMPLE4_ONE, SAMPLE4_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestSAMPLE4_Reverse, 14,
                   SAMPLE4_TWO, SAMPLE4_ONE);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestCase0, 13,
                   EMPTY, SAMPLE4_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestCase1, CASE1_ONE.front(),
                   CASE1_ONE, CASE1_ONE);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestCase2, 13.5,
                   CASE1_ONE, CASE2_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestCase3, 10,
                   CASE1_ONE, CASE3_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestCase5, 10,
                   SAMPLE3_TWO, CASE2_TWO);
SIMPLE_DOUBLE_TEST(MedianOfTwoSortedArrays_DiffSize_Half, TestCase6, 8.5,
                   SAMPLE3_TWO, CASE3_TWO);
