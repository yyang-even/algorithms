#include "common_header.h"

#include "longest_common_subsequence.h"


namespace {

using ArrayType = std::vector<int>;

/** Longest Increasing Subsequence
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-5.
 * @reference   Longest Increasing Subsequence | DP-3
 *              https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/
 * @reference   C/C++ Program for Longest Increasing Subsequence
 *              https://www.geeksforgeeks.org/c-c-program-for-longest-increasing-subsequence/
 * @reference   C++ Program for Longest Increasing Subsequence
 *              https://www.geeksforgeeks.org/c-program-for-longest-increasing-subsequence/
 *
 * The Longest Increasing Subsequence (LIS) problem is to find the length of the longest
 * subsequence of a given sequence such that all elements of the subsequence are sorted
 * in increasing order. For example, the length of LIS for
 * {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is {10, 22, 33, 50, 60, 80}.
 */
auto LongestIncreasingSubsequence_DP(const ArrayType &elements) {
    assert(not elements.empty());

    ArrayType LISs(elements.size(), 1);
    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        for (ArrayType::size_type j = 0; j < i; ++j) {
            if (elements[i] > elements[j] and
                LISs[i] <= LISs[j]) {
                LISs[i] = LISs[j] + 1;
            }
        }
    }

    return *std::max_element(LISs.cbegin(), LISs.cend());
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-6.
 * @reference   Longest Increasing Subsequence Size (N log N)
 *              https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
 * @reference   Longest Monotonically Increasing Subsequence Size (N log N): Simple implementation
 *              https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n-simple-implementation/
 */
auto LongestIncreasingSubsequence_NLogN(const ArrayType &elements) {
    assert(not elements.empty());

    ArrayType tails(elements.size(), 0);
    int length = 1;
    tails[0] = elements.front();

    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        const auto end = std::next(tails.begin(), length);
        const auto lower = std::lower_bound(tails.begin(), end, elements[i]);
        if (lower == end) {
            tails[length++] = elements[i];
        } else {
            *lower = elements[i];
        }
    }

    return length;
}


/**
 * @reference   Longest Increasing Subsequence using Longest Common Subsequence Algorithm
 *              https://www.geeksforgeeks.org/longest-increasing-subsequence-using-longest-common-subsequence-algorithm/
 */
inline auto
LongestIncreasingSubsequence_Sort(const ArrayType &elements) {
    auto sorted_elements = elements;
    std::sort(sorted_elements.begin(), sorted_elements.end());
    return LongestCommonSubsequence(elements, sorted_elements);
}


/**
 * @reference   Construction of Longest Increasing Subsequence(LIS) and printing LIS sequence
 *              https://www.geeksforgeeks.org/construction-of-longest-increasing-subsequence-using-dynamic-programming/
 */
auto OneLongestIncreasingSubsequence_DP(const ArrayType &elements) {
    assert(not elements.empty());

    std::vector<ArrayType> LISs(elements.size());
    LISs[0].push_back(elements.front());
    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        for (ArrayType::size_type j = 0; j < i; ++j) {
            if (elements[i] > elements[j] and
                LISs[i].size() <= LISs[j].size()) {
                LISs[i] = LISs[j];
            }
        }
        LISs[i].push_back(elements[i]);
    }

    return *std::max_element(LISs.cbegin(), LISs.cend(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.size() < rhs.size();
    });
}


/**
 * @reference   Construction of Longest Increasing Subsequence (N log N)
 *              https://www.geeksforgeeks.org/construction-of-longest-monotonically-increasing-subsequence-n-log-n/
 */
auto OneLongestIncreasingSubsequence_NLogN(const ArrayType &elements) {
    assert(not elements.empty());

    ArrayType tail_indices(elements.size(), 0);
    ArrayType prev_indices(elements.size(), -1);
    int length = 1;

    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        const auto end = std::next(tail_indices.begin(), length);
        const auto lower = std::lower_bound(tail_indices.begin(), end, elements[i],
        [&elements](const auto & index, const auto & the_element) {
            return elements[index] < the_element;
        });

        if (lower != tail_indices.begin()) {
            prev_indices[i] = *std::prev(lower);
        }

        if (lower == end) {
            tail_indices[length++] = i;
        } else {
            *lower = i;
        }
    }

    ArrayType one_lis;
    for (auto i = tail_indices[length - 1]; i >= 0; i = prev_indices[i]) {
        one_lis.push_back(elements[i]);
    }
    std::reverse(one_lis.begin(), one_lis.end());
    return one_lis;
}

}//namespace


const ArrayType SAMPLE1 = {10, 22, 9, 33, 21, 50, 41, 60, 80};
const ArrayType EXPECTED1 = {10, 22, 33, 41, 60, 80};

const ArrayType SAMPLE2 = {3, 10, 2, 1, 20};
const ArrayType EXPECTED2 = {3, 10, 20};

const ArrayType SAMPLE3 = {3, 2};
const ArrayType EXPECTED3 = {3};

const ArrayType SAMPLE4 = {50, 3, 10, 7, 40, 80};
const ArrayType EXPECTED4 = {3, 7, 40, 80};


THE_BENCHMARK(LongestIncreasingSubsequence_DP, SAMPLE1);

SIMPLE_TEST(LongestIncreasingSubsequence_DP, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(LongestIncreasingSubsequence_DP, TestSAMPLE2, EXPECTED2.size(), SAMPLE2);
SIMPLE_TEST(LongestIncreasingSubsequence_DP, TestSAMPLE3, EXPECTED3.size(), SAMPLE3);
SIMPLE_TEST(LongestIncreasingSubsequence_DP, TestSAMPLE4, EXPECTED4.size(), SAMPLE4);


THE_BENCHMARK(LongestIncreasingSubsequence_NLogN, SAMPLE1);

SIMPLE_TEST(LongestIncreasingSubsequence_NLogN, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(LongestIncreasingSubsequence_NLogN, TestSAMPLE2, EXPECTED2.size(), SAMPLE2);
SIMPLE_TEST(LongestIncreasingSubsequence_NLogN, TestSAMPLE3, EXPECTED3.size(), SAMPLE3);
SIMPLE_TEST(LongestIncreasingSubsequence_NLogN, TestSAMPLE4, EXPECTED4.size(), SAMPLE4);


THE_BENCHMARK(LongestIncreasingSubsequence_Sort, SAMPLE1);

SIMPLE_TEST(LongestIncreasingSubsequence_Sort, TestSAMPLE1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(LongestIncreasingSubsequence_Sort, TestSAMPLE2, EXPECTED2.size(), SAMPLE2);
SIMPLE_TEST(LongestIncreasingSubsequence_Sort, TestSAMPLE3, EXPECTED3.size(), SAMPLE3);
SIMPLE_TEST(LongestIncreasingSubsequence_Sort, TestSAMPLE4, EXPECTED4.size(), SAMPLE4);


THE_BENCHMARK(OneLongestIncreasingSubsequence_DP, SAMPLE1);

SIMPLE_TEST(OneLongestIncreasingSubsequence_DP, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(OneLongestIncreasingSubsequence_DP, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(OneLongestIncreasingSubsequence_DP, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(OneLongestIncreasingSubsequence_DP, TestSAMPLE4, EXPECTED4, SAMPLE4);


THE_BENCHMARK(OneLongestIncreasingSubsequence_NLogN, SAMPLE1);

SIMPLE_TEST(OneLongestIncreasingSubsequence_NLogN, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(OneLongestIncreasingSubsequence_NLogN, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(OneLongestIncreasingSubsequence_NLogN, TestSAMPLE3, {2}, SAMPLE3);
SIMPLE_TEST(OneLongestIncreasingSubsequence_NLogN, TestSAMPLE4, EXPECTED4, SAMPLE4);
