#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = std::unordered_map<int, ArrayType>;

/** Beautiful Array
 *
 * @reference   https://leetcode.com/problems/beautiful-array/
 *
 * For some fixed n, an array nums is beautiful if it is a permutation of the integers
 * 1, 2, ..., n, such that: For every i < j, there is no k with i < k < j such that
 * nums[k] * 2 = nums[i] + nums[j]. Given n, return any beautiful array nums. (It is
 * guaranteed that one exists.)
 */
auto BeautifulArray_Recursive(const int N, MemoType &memo) {
    const auto iter = memo.find(N);
    if (iter != memo.cend()) {
        return iter->second;
    }

    ArrayType results;
    if (N == 1) {
        results.push_back(1);
    } else {
        for (const auto x : BeautifulArray_Recursive((N + 1) / 2, memo)) {
            results.push_back(2 * x - 1);
        }
        for (const auto x : BeautifulArray_Recursive(N / 2, memo)) {
            results.push_back(2 * x);
        }
    }

    memo.emplace(N, results);
    return results;
}

inline auto BeautifulArray_Recursive(const int N) {
    MemoType memo;
    return BeautifulArray_Recursive(N, memo);
}


auto BeautifulArray_Iterative(const std::size_t N) {
    ArrayType results = {1};
    while (results.size() < N) {
        ArrayType tmp;
        for (const std::size_t i : results) {
            if (i * 2 - 1 <= N) {
                tmp.push_back(i * 2 - 1);
            }
        }
        for (const std::size_t i : results) {
            if (i * 2 <= N) {
                tmp.push_back(i * 2);
            }
        }
        results.swap(tmp);
    }
    return results;
}

}//namespace


const ArrayType EXPECTED1 = {1, 3, 2, 4};
const ArrayType EXPECTED2 = {1, 5, 3, 2, 4};


THE_BENCHMARK(BeautifulArray_Recursive, 5);

SIMPLE_TEST(BeautifulArray_Recursive, TestSAMPLE1, EXPECTED1, 4);
SIMPLE_TEST(BeautifulArray_Recursive, TestSAMPLE2, EXPECTED2, 5);


THE_BENCHMARK(BeautifulArray_Iterative, 5);

SIMPLE_TEST(BeautifulArray_Iterative, TestSAMPLE1, EXPECTED1, 4);
SIMPLE_TEST(BeautifulArray_Iterative, TestSAMPLE2, EXPECTED2, 5);
