#include "common_header.h"

#include "longest_common_subsequence.h"


namespace {

using ArrayType = std::vector<int>;
using HeightWeightPair = std::pair<int, int>;
using HeightWeightArray = std::vector<HeightWeightPair>;


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
 * The Longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of
 * a given sequence such that all elements of the subsequence are sorted in increasing order.
 * For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is
 * {10, 22, 33, 50, 60, 80}.
 *
 * @reference   Longest Increasing Subsequence
 *              https://leetcode.com/problems/longest-increasing-subsequence/
 *
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * A subsequence is a sequence that can be derived from an array by deleting some or no elements without
 * changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence
 * of the array [0,3,1,6,2,2,7].
 * Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
 */
auto LongestIncreasingSubsequence_DP(const ArrayType &elements) {
    assert(not elements.empty());

    ArrayType LISs(elements.size(), 1);
    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        for (ArrayType::size_type j = 0; j < i; ++j) {
            if (elements[i] > elements[j] and LISs[i] <= LISs[j]) {
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

    std::vector tails {elements.front()};

    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        if (elements[i] > tails.back()) {
            tails.push_back(elements[i]);
        } else {
            const auto lower = std::lower_bound(tails.begin(), tails.end(), elements[i]);
            *lower = elements[i];
        }
    }

    return tails.size();
}


/**
 * @reference   Longest Increasing Subsequence using Longest Common Subsequence Algorithm
 *              https://www.geeksforgeeks.org/longest-increasing-subsequence-using-longest-common-subsequence-algorithm/
 */
inline auto LongestIncreasingSubsequence_Sort(const ArrayType &elements) {
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
            if (elements[i] > elements[j] and LISs[i].size() <= LISs[j].size()) {
                LISs[i] = LISs[j];
            }
        }
        LISs[i].push_back(elements[i]);
    }

    return *std::max_element(LISs.cbegin(), LISs.cend(), [](const auto &lhs, const auto &rhs) {
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
        const auto lower =
            std::lower_bound(tail_indices.begin(),
                             end,
                             elements[i],
                             [&elements](const auto &index, const auto &the_element) {
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


/**
 * @reference   Longest Continuous Increasing Subsequence
 *              https://leetcode.com/problems/longest-continuous-increasing-subsequence/
 *
 * Given an unsorted array of integers nums, return the length of the longest continuous increasing
 * subsequence (i.e. subarray). The subsequence must be strictly increasing.
 * A continuous increasing subsequence is defined by two indices l and r (l < r) such that it is
 * [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] and for each l <= i < r, nums[i] < nums[i + 1].
 */
auto LongestContinuousIncreasingSubsequence(const ArrayType &nums) {
    int longest = 1;
    int count = 1;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] < nums[i]) {
            longest = std::max(longest, ++count);
        } else {
            count = 1;
        }
    }

    return longest;
}


/**
 * @reference   Number of Longest Increasing Subsequence
 *              https://leetcode.com/problems/number-of-longest-increasing-subsequence/
 *
 * Given an integer array nums, return the number of longest increasing subsequences.
 * Notice that the sequence has to be strictly increasing.
 */
auto NumLongestIncreasingSubsequence(const ArrayType &nums) {
    const int N = nums.size();
    std::vector length(N, 1);
    std::vector count(N, 1);

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {

            if (nums[j] < nums[i]) {
                if (length[j] + 1 > length[i]) {
                    length[i] = length[j] + 1;
                    count[i] = 0;
                }

                if (length[j] + 1 == length[i]) {
                    count[i] += count[j];
                }
            }
        }
    }

    const auto max_length = *std::max_element(length.cbegin(), length.cend());

    int result = 0;
    for (int i = 0; i < N; ++i) {
        if (length[i] == max_length) {
            result += count[i];
        }
    }

    return result;
}


/**
 * @reference   Maximum Ascending Subarray Sum
 *              https://leetcode.com/problems/maximum-ascending-subarray-sum/
 *
 * Given an array of positive integers nums, return the maximum possible sum of an ascending subarray in
 * nums.
 * A subarray is defined as a contiguous sequence of numbers in an array.
 * A subarray [numsl, numsl+1, ..., numsr-1, numsr] is ascending if for all i where l <= i < r,
 * numsi < numsi+1. Note that a subarray of size 1 is ascending.
 */


/**
 * @reference   Consecutive Characters
 *              https://leetcode.com/problems/consecutive-characters/
 *
 * The power of the string is the maximum length of a non-empty substring that contains only one unique
 * character.
 * Given a string s, return the power of s.
 */


/**
 * @reference   Largest Divisible Subset
 *              https://leetcode.com/problems/largest-divisible-subset/
 *
 * Given a set of distinct positive integers nums, return the largest subset answer such that every pair
 * (answer[i], answer[j]) of elements in this subset satisfies:
 *  answer[i] % answer[j] == 0, or
 *  answer[j] % answer[i] == 0
 * If there are multiple solutions, return any of them.
 */
auto LargestDivisibleSubset(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const auto N = nums.size();
    int max_i = 0;
    ArrayType dp(N, 1), predecessors(N, -1);
    for (std::size_t i = 1; i < N; ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            if (nums[i] % nums[j] == 0 and dp[i] <= dp[j]) {
                dp[i] = dp[j] + 1;
                predecessors[i] = j;
            }
        }
        if (dp[i] > dp[max_i]) {
            max_i = i;
        }
    }

    ArrayType result;
    for (; max_i >= 0; max_i = predecessors[max_i]) {
        result.push_back(nums[max_i]);
    }

    std::reverse(result.begin(), result.end());
    return result;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.7.
 *
 * A circus is designing a tower routine consisting of people standing atop one another's shoulders. For
 * practical and aesthetic reasons, each person must be both shorter and lighter than the person below
 * him or her. Given the heights and weights of each person in the circus, write a method to compute the
 * largest possible number of people in such a tower.
 */
auto CircusTower(HeightWeightArray people) {
    assert(not people.empty());

    std::sort(people.begin(), people.end());

    const auto N = people.size();
    std::vector LISs(N, 1);
    for (ArrayType::size_type i = 1; i < N; ++i) {
        for (ArrayType::size_type j = 0; j < i; ++j) {
            if (people[i].first > people[j].first and people[i].second > people[j].second and
                LISs[i] <= LISs[j]) {
                LISs[i] = LISs[j] + 1;
            }
        }
    }

    return *std::max_element(LISs.cbegin(), LISs.cend());
}


/**
 * @reference   Russian Doll Envelopes
 *              https://leetcode.com/problems/russian-doll-envelopes/
 *
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and
 * the height of an envelope.
 * One envelope can fit into another if and only if both the width and height of one envelope are
 * greater than the other envelope's width and height.
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 * Note: You cannot rotate an envelope.
 */
auto CircusTower_NLogN(HeightWeightArray people) {
    assert(not people.empty());

    std::sort(people.begin(), people.end(), [](const auto &one, const auto &another) {
        if (one.first == another.first)
            return one.second > another.second;
        return one.first < another.first;
    });

    std::vector dp {people.front().second};
    for (const auto &[height, weight] : people) {
        if (weight > dp.back()) {
            dp.push_back(weight);
        } else {
            const auto lower = std::lower_bound(dp.begin(), dp.end(), weight);
            *lower = weight;
        }
    }

    return dp.size();
}


/**
 * @reference   The Number of Weak Characters in the Game
 *              https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
 *
 * You are playing a game that contains multiple characters, and each of the characters has two main
 * properties: attack and defense. You are given a 2D integer array properties where properties[i] =
 * [attacki, defensei] represents the properties of the ith character in the game.
 * A character is said to be weak if any other character has both attack and defense levels strictly
 * greater than this character's attack and defense levels. More formally, a character i is said to be
 * weak if there exists another character j where attackj > attacki and defensej > defensei.
 * Return the number of weak characters.
 */
auto NumberOfWeakCharacters(HeightWeightArray properties) {
    std::sort(properties.begin(), properties.end(), [](const auto &one, const auto &another) {
        if (one.first == another.first) {
            return one.second > another.second;
        }
        return one.first < another.first;
    });

    int result = 0;
    int maximum = INT_MIN;
    for (int i = properties.size() - 1; i >= 0; --i) {
        if (properties[i].second < maximum) {
            ++result;
        } else {
            maximum = properties[i].second;
        }
    }

    return result;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.10.
 *
 * You have a stack of n boxes, with widths w, heights h, and depths d. The boxes cannot be rotated and
 * can only be stacked on top of one another if each box in the stack is strictly larger than the box
 * above it in width, height, and depth. Implement a method to build the tallest stack possible, where
 * the height of a stack is the sum of the heights of each box.
 */


/** Box Stacking Problem | DP-22
 *
 * @reference   https://www.geeksforgeeks.org/box-stacking-problem-dp-22/
 *
 * You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i), width
 * w(i) and depth d(i) (all real numbers). You want to create a stack of boxes which is as tall as
 * possible, but you can only stack a box on top of another box if the dimensions of the 2-D base of the
 * lower box are each strictly larger than those of the 2-D base of the higher box. Of course, you can
 * rotate a box so that any side functions as its base. It is also allowable to use multiple instances
 * of the same type of box.
 */
struct Box {
    int height = 0;
    int width = 0;
    int depth = 0;
};

using BoxArray = std::vector<Box>;

static inline auto &operator<<(std::ostream &out, const Box &a_box) {
    return out << "(" << a_box.height << ", " << a_box.width << ", " << a_box.depth << ")";
}

auto MaxStackHeight(const BoxArray &boxes) {
    BoxArray rotated_boxes;
    for (const auto &[height, width, depth] : boxes) {
        rotated_boxes.push_back({height, std::min(width, depth), std::max(width, depth)});
        rotated_boxes.push_back({width, std::min(height, depth), std::max(height, depth)});
        rotated_boxes.push_back({depth, std::min(width, height), std::max(width, height)});
    }

    std::sort(rotated_boxes.begin(), rotated_boxes.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.width * lhs.depth > rhs.width * rhs.depth;
    });

    std::vector<int> max_stack_heights;
    for (const auto &a_box : rotated_boxes) {
        max_stack_heights.push_back(a_box.height);
    }

    const auto N = rotated_boxes.size();
    for (std::size_t i = 1; i < N; ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            if (rotated_boxes[i].width < rotated_boxes[j].width and
                rotated_boxes[i].depth < rotated_boxes[j].depth) {
                if (const auto new_max_height = max_stack_heights[j] + rotated_boxes[i].height;
                    max_stack_heights[i] < new_max_height) {
                    max_stack_heights[i] = new_max_height;
                }
            }
        }
    }

    return *std::max_element(max_stack_heights.cbegin(), max_stack_heights.cend());
}

} //namespace


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


const ArrayType SAMPLE5 = {1, 3, 5, 4, 7};
const ArrayType SAMPLE6 = {2, 2, 2, 2, 2};


THE_BENCHMARK(LongestContinuousIncreasingSubsequence, SAMPLE5);

SIMPLE_TEST(LongestContinuousIncreasingSubsequence, TestSAMPLE5, 3, SAMPLE5);
SIMPLE_TEST(LongestContinuousIncreasingSubsequence, TestSAMPLE6, 1, SAMPLE6);


THE_BENCHMARK(NumLongestIncreasingSubsequence, SAMPLE5);

SIMPLE_TEST(NumLongestIncreasingSubsequence, TestSAMPLE5, 2, SAMPLE5);
SIMPLE_TEST(NumLongestIncreasingSubsequence, TestSAMPLE6, 5, SAMPLE6);


const ArrayType SAMPLE1D = {1, 2, 3};
const ArrayType EXPECTED1D = {1, 2};

const ArrayType SAMPLE2D = {1, 2, 4, 8};


THE_BENCHMARK(LargestDivisibleSubset, SAMPLE1D);

SIMPLE_TEST(LargestDivisibleSubset, TestSAMPLE1, EXPECTED1D, SAMPLE1D);
SIMPLE_TEST(LargestDivisibleSubset, TestSAMPLE2, SAMPLE2D, SAMPLE2D);


const HeightWeightArray SAMPLE1H = {
    {65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};
const HeightWeightArray SAMPLE2H = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
const HeightWeightArray SAMPLE3H = {{1, 1}, {1, 1}, {1, 1}};
const HeightWeightArray SAMPLE4H = {{4, 5}, {4, 6}, {6, 7}, {2, 3}, {1, 1}};


THE_BENCHMARK(CircusTower, SAMPLE1H);

SIMPLE_TEST(CircusTower, TestSAMPLE1, 6, SAMPLE1H);
SIMPLE_TEST(CircusTower, TestSAMPLE2, 3, SAMPLE2H);
SIMPLE_TEST(CircusTower, TestSAMPLE3, 1, SAMPLE3H);
SIMPLE_TEST(CircusTower, TestSAMPLE4, 4, SAMPLE4H);


THE_BENCHMARK(CircusTower_NLogN, SAMPLE1H);

SIMPLE_TEST(CircusTower_NLogN, TestSAMPLE1, 6, SAMPLE1H);
SIMPLE_TEST(CircusTower_NLogN, TestSAMPLE2, 3, SAMPLE2H);
SIMPLE_TEST(CircusTower_NLogN, TestSAMPLE3, 1, SAMPLE3H);
SIMPLE_TEST(CircusTower_NLogN, TestSAMPLE4, 4, SAMPLE4H);


const BoxArray SAMPLE1B = {{4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32}};


THE_BENCHMARK(MaxStackHeight, SAMPLE1B);

SIMPLE_TEST(MaxStackHeight, TestSAMPLE1, 60, SAMPLE1B);


const HeightWeightArray SAMPLE1C = {{5, 5}, {6, 3}, {3, 6}};
const HeightWeightArray SAMPLE2C = {{2, 2}, {3, 3}};
const HeightWeightArray SAMPLE3C = {{1, 5}, {10, 4}, {4, 3}};


THE_BENCHMARK(NumberOfWeakCharacters, SAMPLE1C);

SIMPLE_TEST(NumberOfWeakCharacters, TestSAMPLE1, 0, SAMPLE1C);
SIMPLE_TEST(NumberOfWeakCharacters, TestSAMPLE2, 1, SAMPLE2C);
SIMPLE_TEST(NumberOfWeakCharacters, TestSAMPLE3, 1, SAMPLE3C);
