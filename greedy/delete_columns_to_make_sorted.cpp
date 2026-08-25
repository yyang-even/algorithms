#include "common_header.h"


namespace {

using MatrixType = std::vector<std::string_view>;

/**
 * @reference   Delete Columns to Make Sorted II
 *              https://leetcode.com/problems/delete-columns-to-make-sorted-ii/
 *
 * You are given an array of n strings strs, all of the same length.
 * We may choose any deletion indices, and we delete all the characters in those indices for each
 * string.
 * For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final
 * array after deletions is ["bef", "vyz"].
 * Suppose we chose a set of deletion indices answer such that after deletions, the final array has its
 * elements in lexicographic order (i.e., strs[0] <= strs[1] <= strs[2] <= ... <= strs[n - 1]). Return
 * the minimum possible value of answer.length.
 *
 * @tags    #greedy #matrix #queue
 */
auto DeleteColumnsToMakeSorted(const MatrixType &strs) {
    const int N = strs.size();
    const int M = strs.front().size();

    std::vector<bool> resolved(N - 1, false);
    int unresolved = N - 1;
    int result = 0;

    for (int j = 0; j < M; ++j) {
        auto to_delete = false;
        for (int i = 0; i < N - 1; ++i) {
            if (not resolved[i] and strs[i][j] > strs[i + 1][j]) {
                to_delete = true;
                break;
            }
        }

        if (to_delete) {
            ++result;
            continue;
        }

        for (int i = 0; i < N - 1; ++i) {
            if (not resolved[i] and strs[i][j] < strs[i + 1][j]) {
                resolved[i] = true;
                if (unresolved-- == 1) {
                    return result;
                }
            }
        }
    }

    return result;
}


/**
 * @reference   Delete Columns to Make Sorted
 *              https://leetcode.com/problems/delete-columns-to-make-sorted/
 *
 * You are given an array of n strings strs, all of the same length.
 * The strings can be arranged such that there is one on each line, making a grid.
 *  For example, strs = ["abc", "bce", "cae"] can be arranged as follows:
 *      abc
 *      bce
 *      cae
 * You want to delete the columns that are not sorted lexicographically. In the above example
 * (0-indexed), columns 0 ('a', 'b', 'c') and 2 ('c', 'e', 'e') are sorted, while column 1 ('b', 'c',
 * 'a') is not, so you would delete column 1.
 * Return the number of columns that you will delete.
 *
 * @tags    #matrix
 */

} //namespace


// clang-format off
const MatrixType SAMPLE1 = {
    "ca",
    "bb",
    "ac"
};

const MatrixType SAMPLE2 = {
    "xc",
    "yb",
    "za"
};

const MatrixType SAMPLE3 = {
    "zyx",
    "wvu",
    "tsr"
};

const MatrixType SAMPLE4 = {
    "xga",
    "xfb",
    "yfa"
};

const MatrixType SAMPLE5 = {
    "vdy",
    "vei",
    "zvc",
    "zld"
};
// clang-format on


THE_BENCHMARK(DeleteColumnsToMakeSorted, SAMPLE1);

SIMPLE_TEST(DeleteColumnsToMakeSorted, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(DeleteColumnsToMakeSorted, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(DeleteColumnsToMakeSorted, TestSAMPLE3, 3, SAMPLE3);
SIMPLE_TEST(DeleteColumnsToMakeSorted, TestSAMPLE4, 1, SAMPLE4);
SIMPLE_TEST(DeleteColumnsToMakeSorted, TestSAMPLE5, 2, SAMPLE5);
