#include "common_header.h"

#include "hash/hash.h"
#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Length of the Longest Consecutive 1s in Binary Representation
 *              https://www.geeksforgeeks.org/length-longest-consecutive-1s-binary-representation/
 *
 * The idea is based on the concept that if we AND a bit sequence with a shifted version of itself,
 * we're effectively removing the trailing 1 from every sequence of consecutive 1s.
 *
 * @tags    #bit-tricks
 */
constexpr auto LengthOfLongestConsecutive1s(unsigned number) {
    unsigned length = 0;
    while (number) {
        number &= (number << 1);
        ++length;
    }

    return length;
}


/**
 * @reference   Binary Gap
 *              https://leetcode.com/problems/binary-gap/
 *
 * Given a positive integer n, find and return the longest distance between any two adjacent 1's in the
 * binary representation of n. If there are no two adjacent 1's, return 0.
 * Two 1's are adjacent if there are only 0's separating them (possibly no 0's). The distance between
 * two 1's is the absolute difference between their bit positions. For example, the two 1's in "1001"
 * have a distance of 3.
 */
constexpr auto BinaryGap(const unsigned n) {
    int prev = -1;
    int result = 0;
    for (int i = 0; (1u << i) <= n; ++i) {
        if (n & (1u << i)) {
            if (prev != -1) {
                result = std::max(result, i - prev);
            }
            prev = i;
        }
    }

    return result;
}


/**
 * @reference   Maximum consecutive one’s (or zeros) in a binary array
 *              https://www.geeksforgeeks.org/maximum-consecutive-ones-or-zeros-in-a-binary-array/
 *
 * Given binary array, find count of maximum number of consecutive 1's present in the array.
 *
 * @reference   Max Consecutive Ones
 *              https://leetcode.com/problems/max-consecutive-ones/
 */
auto LengthOfLongestConsecutive1s_Array(const ArrayType &number) {
    int count = 0;
    int max_count = 0;
    for (const auto a_digit : number) {
        if (a_digit) {
            if (++count > max_count) {
                max_count = count;
            }
        } else {
            count = 0;
        }
    }

    return max_count;
}


/**
 * @reference   Longest Subarray With Maximum Bitwise AND
 *              https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/
 *
 * You are given an integer array nums of size n.
 * Consider a non-empty subarray from nums that has the maximum possible bitwise AND.
 * In other words, let k be the maximum value of the bitwise AND of any subarray of nums. Then, only
 * subarrays with a bitwise AND equal to k should be considered.
 * Return the length of the longest such subarray.
 * The bitwise AND of an array is the bitwise AND of all the numbers in it.
 * A subarray is a contiguous sequence of elements within an array.
 *
 * @hint    The bitwise AND of two different numbers will always be strictly less than the maximum of
 *          those two numbers.
 *
 * @tags    #bit-tricks
 */
auto LongestSubarrayWithMaxAnd(const ArrayType &nums) {
    int current = 0;
    int result = 0;
    int length = 0;
    for (const auto n : nums) {
        if (n == current) {
            result = std::max(result, ++length);
        } else if (n > current) {
            current = n;
            length = 1;
            result = 1;
        } else {
            length = 0;
        }
    }

    return result;
}


/**
 * @reference   Three Consecutive Odds
 *              https://leetcode.com/problems/three-consecutive-odds/
 *
 * Given an integer array arr, return true if there are three consecutive odd numbers in the array.
 * Otherwise, return false.
 */
auto ThreeConsecutiveOdds(const ArrayType &nums) {
    int odds = 0;
    for (std::size_t i = 0; i < nums.size() and odds < 3; ++i) {
        if (nums[i] % 2) {
            ++odds;
        } else {
            odds = 0;
        }
    }

    return odds == 3;
}


/**
 * @reference   Detect Pattern of Length M Repeated K or More Times
 *              https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/
 *
 * Given an array of positive integers arr, find a pattern of length m that is repeated k or more times.
 * A pattern is a subarray (consecutive sub-sequence) that consists of one or more values, repeated
 * multiple times consecutively without overlapping. A pattern is defined by its length and the number
 * of repetitions.
 * Return true if there exists a pattern of length m that is repeated k or more times, otherwise return
 * false.
 * 2 <= k <= 100
 */
auto ContainPattern(const ArrayType &nums, const int m, const int k) {
    int length = 0;
    for (std::size_t i = 0; i + m < nums.size(); ++i) {
        if (nums[i] == nums[i + m]) {
            if (++length == (k - 1) * m) {
                return true;
            }
        } else {
            length = 0;
        }
    }

    return false;
}


/**
 * @reference   Max Consecutive Ones II
 *              https://www.lintcode.com/problem/883/
 *
 * Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most
 * one 0.
 *
 * @reference   Longest Subarray of 1's After Deleting One Element
 *              https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/
 *
 * Given a binary array nums, you should delete one element from it.
 * Return the size of the longest non-empty subarray containing only 1's in the resulting array. Return
 * 0 if there is no such subarray.
 */
auto LengthOfLongestConsecutive1s_1Flip_Array(const ArrayType &number) {
    unsigned current_count = 0;
    unsigned prev_count = 0;
    unsigned max_count = 0;

    for (const auto digit : number) {
        if (digit == 0) {
            prev_count = current_count;
            current_count = 0;
        } else {
            ++current_count;
        }

        const auto total = current_count + prev_count + 1;
        if (total > max_count) {
            max_count = total;
        }
    }

    return std::min(max_count, static_cast<unsigned>(number.size()));
}


/**
 * @reference   Max Consecutive Ones III
 *              https://leetcode.com/problems/max-consecutive-ones-iii/
 *
 * Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array
 * if you can flip at most k 0's.
 */
auto LengthOfLongestConsecutive1s_KFlip_Array(const ArrayType &number, const int K) {
    ArrayType::size_type left = 0;
    int flipped_zeros = 0;
    ArrayType::size_type max_count = 0;

    for (ArrayType::size_type right = 0; right < number.size(); ++right) {
        if (number[right] == 0) {
            ++flipped_zeros;
        }

        while (flipped_zeros > K) {
            if (number[left++] == 0) {
                --flipped_zeros;
            }
        }

        const auto total = right - left + 1;
        if (total > max_count) {
            max_count = total;
        }
    }

    return max_count;
}


/**
 * @reference   Frequency of the Most Frequent Element
 *              https://leetcode.com/problems/frequency-of-the-most-frequent-element/
 *
 * The frequency of an element is the number of times it occurs in an array.
 * You are given an integer array nums and an integer k. In one operation, you can choose an index of
 * nums and increment the element at that index by 1.
 * Return the maximum possible frequency of an element after performing at most k operations.
 */
auto MaxFrequency_NonShrinkableSlidingWindow(ArrayType nums, long k) {
    std::sort(nums.begin(), nums.end());

    long left = 0;
    long right = 0;
    const long size = nums.size();
    for (; right < size; ++right) {
        k += nums[right];
        if (k < nums[right] * (right - left + 1)) {
            k -= nums[left++];
        }
    }

    return right - left;
}


/**
 * @reference   Maximize the Confusion of an Exam
 *              https://leetcode.com/problems/maximize-the-confusion-of-an-exam/
 *
 * A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting
 * false. He wants to confuse the students by maximizing the number of consecutive questions with the
 * same answer (multiple trues or multiple falses in a row).
 * You are given a string answerKey, where answerKey[i] is the original answer to the ith question. In
 * addition, you are given an integer k, the maximum number of times you may perform the following
 * operation:
 *  Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').
 * Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the
 * operation at most k times.
 */
auto MaxConsecutiveAnswers_KFlip(const std::string_view answer_key, const int k) {
    std::size_t result = k;
    int left = 0;
    std::unordered_map<char, int> count;

    for (std::size_t right = 0; right < answer_key.size(); ++right) {
        ++(count[answer_key[right]]);

        while (std::min(count['T'], count['F']) > k) {
            --(count[answer_key[left++]]);
        }

        result = std::max(result, right - left + 1);
    }

    return result;
}


auto MaxConsecutiveAnswers_KFlip_NonshrinkableSlidingWindow(const std::string_view answer_key,
                                                            const int k) {
    int result = 0;
    std::unordered_map<char, int> count;

    for (std::size_t right = 0; right < answer_key.length(); ++right) {
        ++(count[answer_key[right]]);

        if (std::min(count['T'], count['F']) <= k) {
            ++result;
        } else {
            --(count[answer_key[right - result]]);
        }
    }

    return result;
}


/**
 * @reference   Max Area of Island
 *              https://leetcode.com/problems/max-area-of-island/
 *
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected
 * 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by
 * water.
 * The area of an island is the number of cells with a value 1 in the island.
 * Return the maximum area of an island in grid. If there is no island, return 0.
 */


/**
 * @reference   Making A Large Island
 *              https://leetcode.com/problems/making-a-large-island/
 *
 * You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
 * Return the size of the largest island in grid after applying this operation.
 * An island is a 4-directionally connected group of 1s.
 */
int checkIslandSize_Iterative(const MatrixType &grid, const std::pair<int, int> start_point) {
    const int N = grid.size();
    std::stack<std::pair<int, int>> s;
    s.push(start_point);
    std::unordered_set<std::pair<int, int>, PairHash> visited;
    visited.insert(start_point);

    while (not s.empty()) {
        const auto [row, column] = s.top();
        s.pop();

        ForEachDirection(N, N, row, column, [&grid, &visited, &s](const auto i, const auto j) {
            if (grid[i][j] == 1) {
                if (visited.emplace(i, j).second) {
                    s.emplace(i, j);
                }
            }
        });
    }

    return visited.size();
}

int MakeLargeIsland_Naive(MatrixType grid) {
    const auto N = grid.size();
    assert(N == grid.front().size());

    int result = 0;
    bool has_zero = false;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                has_zero = true;
                grid[i][j] = 1;
                result =
                    std::max(result, checkIslandSize_Iterative(grid, std::pair<int, int>(i, j)));
                grid[i][j] = 0;
            }
        }
    }

    return has_zero ? result : N * N;
}


int checkIslandSize_Recursive(MatrixType &grid,
                              const int row,
                              const int column,
                              const int island_index) {
    const int N = grid.size();
    grid[row][column] = island_index;

    int result = 1;
    ForEachDirection(
        N, N, row, column, [&grid, &result, island_index](const auto i, const auto j) {
            if (grid[i][j] == 1) {
                result += checkIslandSize_Recursive(grid, i, j, island_index);
            }
        });

    return result;
}

int findTotalArea(const MatrixType &grid,
                  const int row,
                  const int column,
                  const std::unordered_map<int, int> &areas) {
    const int N = grid.size();

    int result = 1;
    std::unordered_set<int> visited_island;
    ForEachDirection(
        N, N, row, column, [&grid, &visited_island, &result, &areas](const auto i, const auto j) {
            if (grid[i][j] != 0) {
                if (visited_island.insert(grid[i][j]).second) {
                    result += areas.at(grid[i][j]);
                }
            }
        });

    return result;
}

int MakeLargeIsland_UnionFind(MatrixType grid) {
    const auto N = grid.size();
    assert(N == grid.front().size());

    std::unordered_map<int, int> areas;
    int island_index = 2;
    int result = 0;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == 1) {
                ++island_index;
                areas[island_index] = checkIslandSize_Recursive(grid, i, j, island_index);
                result = std::max(result, areas[island_index]);
            }
        }
    }

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                result = std::max(result, findTotalArea(grid, i, j, areas));
            }
        }
    }

    return result;
}


/**
 * @reference   Maximum 69 Number
 *              https://leetcode.com/problems/maximum-69-number/
 *
 * Given a positive integer num consisting only of digits 6 and 9.
 * Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes 6).
 * 1 <= num <= 10^4
 */


/**
 * @reference   Check if Binary String Has at Most One Segment of Ones
 *              https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/
 *
 * Given a binary string s without leading zeros, return true if s contains at most one contiguous
 * segment of ones. Otherwise, return false.
 * s[0] is '1'.
 */
inline constexpr auto HasMostOneSegmentOf1s(const std::string_view s) {
    return s.find("01") == std::string_view::npos;
}


/**
 * @reference   Longer Contiguous Segments of Ones than Zeros
 *              https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/
 *
 * Given a binary string s, return true if the longest contiguous segment of 1's is strictly longer than
 * the longest contiguous segment of 0's in s, or return false otherwise.
 * For example, in s = "110100010" the longest continuous segment of 1s has length 2, and the longest
 * continuous segment of 0s has length 3.
 * Note that if there are no 0's, then the longest continuous segment of 0's is considered to have a
 * length 0. The same applies if there is no 1's.
 */
constexpr auto Longer1sThan0s(const std::string_view s) {
    auto curr = s.front();
    int count = 0;
    int maximum[2] = {};

    for (const auto c : s) {
        if (curr != c) {
            count = 0;
            curr = c;
        }

        const int i = c - '0';
        maximum[i] = std::max(maximum[i], ++count);
    }

    return maximum[1] > maximum[0];
}

} //namespace


const ArrayType SAMPLE1 = {1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1};
const ArrayType SAMPLE2 = {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
const ArrayType SAMPLE3 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


THE_BENCHMARK(LengthOfLongestConsecutive1s, 14);

SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE1, 3, 14);
SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE2, 4, 222);
SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE3, 4, 0b110010101111);
SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE4, 1, 0b00101010101);


THE_BENCHMARK(LengthOfLongestConsecutive1s_Array, SAMPLE1);

SIMPLE_TEST(LengthOfLongestConsecutive1s_Array, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_Array, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_Array, TestSAMPLE3, SAMPLE3.size(), SAMPLE3);


const ArrayType SAMPLE4 = {1, 0, 1, 1, 0};


THE_BENCHMARK(LengthOfLongestConsecutive1s_1Flip_Array, SAMPLE1);

SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE3, SAMPLE3.size(), SAMPLE3);
SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE4, 4, SAMPLE4);


const ArrayType SAMPLE6 = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
const ArrayType SAMPLE7 = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};


THE_BENCHMARK(LengthOfLongestConsecutive1s_KFlip_Array, SAMPLE1, 1);

SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE1, 6, SAMPLE1, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE2, 3, SAMPLE2, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE3, SAMPLE3.size(), SAMPLE3, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE4, 4, SAMPLE4, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE5, SAMPLE4.size(), SAMPLE4, 2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE6, 6, SAMPLE6, 2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE7, 10, SAMPLE7, 3);


// clang-format off
const MatrixType SAMPLE1M = {
    {1, 0},
    {0, 1}
};

const MatrixType SAMPLE2M = {
    {1, 1},
    {0, 1}
};

const MatrixType SAMPLE3M = {
    {1, 1},
    {1, 1}
};
// clang-format on


THE_BENCHMARK(MakeLargeIsland_Naive, SAMPLE1M);

SIMPLE_TEST(MakeLargeIsland_Naive, TestSAMPLE1, 3, SAMPLE1M);
SIMPLE_TEST(MakeLargeIsland_Naive, TestSAMPLE2, 4, SAMPLE2M);
SIMPLE_TEST(MakeLargeIsland_Naive, TestSAMPLE3, 4, SAMPLE3M);


THE_BENCHMARK(MakeLargeIsland_UnionFind, SAMPLE1M);

SIMPLE_TEST(MakeLargeIsland_UnionFind, TestSAMPLE1, 3, SAMPLE1M);
SIMPLE_TEST(MakeLargeIsland_UnionFind, TestSAMPLE2, 4, SAMPLE2M);
SIMPLE_TEST(MakeLargeIsland_UnionFind, TestSAMPLE3, 4, SAMPLE3M);


const ArrayType SAMPLE1T = {2, 6, 4, 1};
const ArrayType SAMPLE2T = {1, 2, 34, 3, 4, 5, 7, 23, 12};


THE_BENCHMARK(ThreeConsecutiveOdds, SAMPLE1T);

SIMPLE_TEST(ThreeConsecutiveOdds, TestSAMPLE1, false, SAMPLE1T);
SIMPLE_TEST(ThreeConsecutiveOdds, TestSAMPLE2, true, SAMPLE2T);


THE_BENCHMARK(BinaryGap, 22);

SIMPLE_TEST(BinaryGap, TestSAMPLE1, 2, 22);
SIMPLE_TEST(BinaryGap, TestSAMPLE2, 2, 5);
SIMPLE_TEST(BinaryGap, TestSAMPLE3, 1, 6);
SIMPLE_TEST(BinaryGap, TestSAMPLE4, 0, 8);
SIMPLE_TEST(BinaryGap, TestSAMPLE5, 0, 1);


const ArrayType SAMPLE1P = {1, 2, 4, 4, 4, 4};
const ArrayType SAMPLE2P = {1, 2, 1, 2, 1, 1, 1, 3};
const ArrayType SAMPLE3P = {1, 2, 1, 2, 1, 3};


THE_BENCHMARK(ContainPattern, SAMPLE1P, 1, 3);

SIMPLE_TEST(ContainPattern, TestSAMPLE1, true, SAMPLE1P, 1, 3);
SIMPLE_TEST(ContainPattern, TestSAMPLE2, true, SAMPLE2P, 2, 2);
SIMPLE_TEST(ContainPattern, TestSAMPLE3, false, SAMPLE3P, 2, 3);


THE_BENCHMARK(HasMostOneSegmentOf1s, "1001");

SIMPLE_TEST(HasMostOneSegmentOf1s, TestSAMPLE1, false, "1001");
SIMPLE_TEST(HasMostOneSegmentOf1s, TestSAMPLE2, true, "110");


THE_BENCHMARK(Longer1sThan0s, "1101");

SIMPLE_TEST(Longer1sThan0s, TestSAMPLE1, true, "1101");
SIMPLE_TEST(Longer1sThan0s, TestSAMPLE2, false, "111000");
SIMPLE_TEST(Longer1sThan0s, TestSAMPLE3, false, "110100010");


THE_BENCHMARK(MaxConsecutiveAnswers_KFlip, "TTFF", 2);

SIMPLE_TEST(MaxConsecutiveAnswers_KFlip, TestSAMPLE1, 4, "TTFF", 2);
SIMPLE_TEST(MaxConsecutiveAnswers_KFlip, TestSAMPLE2, 3, "TFFT", 1);
SIMPLE_TEST(MaxConsecutiveAnswers_KFlip, TestSAMPLE3, 5, "TTFTTFTT", 1);


THE_BENCHMARK(MaxConsecutiveAnswers_KFlip_NonshrinkableSlidingWindow, "TTFF", 2);

SIMPLE_TEST(MaxConsecutiveAnswers_KFlip_NonshrinkableSlidingWindow, TestSAMPLE1, 4, "TTFF", 2);
SIMPLE_TEST(MaxConsecutiveAnswers_KFlip_NonshrinkableSlidingWindow, TestSAMPLE2, 3, "TFFT", 1);
SIMPLE_TEST(
    MaxConsecutiveAnswers_KFlip_NonshrinkableSlidingWindow, TestSAMPLE3, 5, "TTFTTFTT", 1);


const ArrayType SAMPLE1A = {1, 2, 3, 3, 2, 2};
const ArrayType SAMPLE2A = {1, 2, 3, 4};
const ArrayType SAMPLE3A = {
    395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808,
    395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808,
    395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808,
    395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808, 395808,
    395808, 470030, 470030, 470030, 470030, 470030, 470030, 470030, 470030, 470030, 470030,
    470030, 470030, 470030, 470030, 470030, 470030, 470030, 470030, 470030, 470030, 470030,
    470030, 470030, 470030, 153490, 330001, 330001, 330001, 330001, 330001, 330001, 330001,
    37284,  470030, 470030, 470030, 470030, 470030, 470030, 156542, 226743};
const ArrayType SAMPLE4A = {
    96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 96317, 279979};


THE_BENCHMARK(LongestSubarrayWithMaxAnd, SAMPLE1A);

SIMPLE_TEST(LongestSubarrayWithMaxAnd, TestSAMPLE1, 2, SAMPLE1A);
SIMPLE_TEST(LongestSubarrayWithMaxAnd, TestSAMPLE2, 1, SAMPLE2A);
SIMPLE_TEST(LongestSubarrayWithMaxAnd, TestSAMPLE3, 24, SAMPLE3A);
SIMPLE_TEST(LongestSubarrayWithMaxAnd, TestSAMPLE4, 1, SAMPLE4A);


const ArrayType SAMPLE1F = {1, 2, 4};
const ArrayType SAMPLE2F = {1, 4, 8, 13};
const ArrayType SAMPLE3F = {3, 9, 6};


THE_BENCHMARK(MaxFrequency_NonShrinkableSlidingWindow, SAMPLE1F, 5);

SIMPLE_TEST(MaxFrequency_NonShrinkableSlidingWindow, TestSAMPLE1, 3, SAMPLE1F, 5);
SIMPLE_TEST(MaxFrequency_NonShrinkableSlidingWindow, TestSAMPLE2, 2, SAMPLE2F, 5);
SIMPLE_TEST(MaxFrequency_NonShrinkableSlidingWindow, TestSAMPLE3, 1, SAMPLE3F, 2);
