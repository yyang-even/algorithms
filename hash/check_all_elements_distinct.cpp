#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Check if all array elements are distinct
 *              https://www.geeksforgeeks.org/check-if-all-array-elements-are-distinct/
 *
 * Given an array, check whether all elements in an array are distinct or not.
 *
 * @reference   Contains Duplicate
 *              https://leetcode.com/problems/contains-duplicate/
 *
 * Given an integer array nums, return true if any value appears at least twice in the array, and return
 * false if every element is distinct.
 *
 * @tags    #hash-table
 */
auto CheckIfAllElementsDistinct(const ArrayType &elements) {
    std::unordered_set<ArrayType::value_type> counters;

    for (const auto elem : elements) {
        if (not counters.insert(elem).second) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.1.
 *
 * Implement an algorithm to determine if a string has all unique characters. What if you cannot use
 * additional data structures?
 *
 * @tags    #sort
 */
auto CheckIfAllElementsDistinct_Sort(ArrayType elements) {
    std::sort(elements.begin(), elements.end());

    for (auto iter = std::next(elements.cbegin()); iter != elements.cend(); ++iter) {
        if (*std::prev(iter) == *iter) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Contains Duplicate II
 *              https://leetcode.com/problems/contains-duplicate-ii/
 *
 * Given an integer array nums and an integer k, return true if there are two distinct indices i and j
 * in the array such that nums[i] == nums[j] and abs(i - j) <= k.
 *
 * @tags    #hash-table
 */
auto ContainDuplicateAtMostKApart(const ArrayType &elements, const std::size_t K) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> last_occurrences;

    for (std::size_t i = 0; i < elements.size(); ++i) {
        const auto elem = elements[i];
        const auto [iter, inserted] = last_occurrences.emplace(elem, i);
        if (not inserted) {
            if (i - iter->second <= K) {
                return true;
            }
            iter->second = i;
        }
    }

    return false;
}


/**
 * @reference   Contains Duplicate III
 *              https://leetcode.com/problems/contains-duplicate-iii/
 *
 * Given an integer array nums and two integers k and t, return true if there are two distinct indices i
 * and j in the array such that abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.
 *
 * @reference   [LeetCode] Contains Duplicate III
 *              https://www.cnblogs.com/easonliu/p/4544073.html
 *
 * @tags    #hash-table
 */
auto ContainAlmostDuplicateAtMostKApart_Set(const ArrayType &elements,
                                            const std::size_t K,
                                            const ArrayType::value_type T) {
    std::multiset<long long> neighbors;

    for (std::size_t i = 0; i < elements.size(); ++i) {
        if (neighbors.size() == K + 1) {
            neighbors.erase(neighbors.find(elements[i - K - 1]));
        }
        const auto a_number = elements[i];
        const auto lower = neighbors.lower_bound(a_number - T);
        if (lower != neighbors.cend() and *lower - a_number <= T) {
            return true;
        }
        neighbors.insert(a_number);
    }

    return false;
}


/**
 * @reference   (LeetCode) Contains Duplicate III
 *              https://stackoverflow.com/questions/31119971/leetcode-contains-duplicate-iii
 */
inline constexpr auto getBucketId(const long number, const long bucket_size) {
    return number < 0 ? (number + 1) / bucket_size - 1 : number / bucket_size;
}

auto ContainAlmostDuplicateAtMostKApart_Bucket(const ArrayType &elements,
                                               const std::size_t K,
                                               const ArrayType::value_type T) {
    if (elements.size() <= 1 or T < 0) {
        return false;
    }

    const auto bucket_size = T + 1;

    std::unordered_map<int, long> buckets;
    for (std::size_t i = 0; i < elements.size(); ++i) {
        const auto the_number = elements[i];
        const int bucket_id = getBucketId(the_number, bucket_size);
        if (buckets.find(bucket_id) != buckets.cend()) {
            return true;
        }

        buckets[bucket_id] = the_number;
        if (const auto prev_bucket = buckets.find(bucket_id - 1);
            prev_bucket != buckets.cend() and std::abs(prev_bucket->second - the_number) <= T) {
            return true;
        }
        if (const auto next_bucket = buckets.find(bucket_id + 1);
            next_bucket != buckets.cend() and std::abs(next_bucket->second - the_number) <= T) {
            return true;
        }

        if (buckets.size() > K) {
            const auto bucket_id_to_remove = getBucketId(elements[i - K], bucket_size);
            buckets.erase(bucket_id_to_remove);
        }
    }

    return false;
}


/**
 * @reference   Longest Substring Without Repeating Characters
 *              https://leetcode.com/problems/longest-substring-without-repeating-characters/
 *
 * Given a string s, find the length of the longest substring without repeating characters. s consists
 * of English letters, digits, symbols and spaces.
 *
 * @tags    #hash-table #sliding-window
 */
constexpr auto LongestSubstrWithoutRepeatingChars_Last(const std::string_view s) {
    std::size_t lasts[256] = {};
    std::size_t result = 0;
    for (std::size_t i = 0, start = 0; i < s.size(); ++i) {
        const int c = s[i];
        if (lasts[c] > start) {
            start = lasts[c];
        }
        lasts[c] = i + 1;
        result = std::max(result, i - start + 1);
    }

    return result;
}


constexpr auto LongestSubstrWithoutRepeatingChars_Count(const std::string_view s) {
    int counts[256] = {};
    std::size_t left = 0;
    std::size_t right = 0;

    std::size_t result = 0;
    while (right < s.size()) {
        const int c = s[right];
        ++counts[c];

        while (counts[c] > 1) {
            const int i = s[left++];
            --counts[i];
        }

        result = std::max(result, ++right - left);
    }

    return result;
}


/**
 * @reference   Maximum Erasure Value
 *              https://leetcode.com/problems/maximum-erasure-value/
 *
 * You are given an array of positive integers nums and want to erase a subarray containing unique
 * elements. The score you get by erasing the subarray is equal to the sum of its elements.
 * Return the maximum score you can get by erasing exactly one subarray.
 * An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it
 * is equal to a[l],a[l+1],...,a[r] for some (l,r).
 *
 * @tags    #hash-table #sliding-window
 */


/**
 * @reference   Maximum Unique Subarray Sum After Deletion
 *              https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/
 *
 * You are given an integer array nums.
 * You are allowed to delete any number of elements from nums without making it empty. After performing
 * the deletions, select a subarray of nums such that:
 *  1. All elements in the subarray are unique.
 *  2. The sum of the elements in the subarray is maximized.
 * Return the maximum sum of such a subarray.
 *
 * @tags    #hash-table
 */


/**
 * @reference   Find the Longest Semi-Repetitive Substring
 *              https://leetcode.com/problems/find-the-longest-semi-repetitive-substring/
 *
 * You are given a 0-indexed string s that consists of digits from 0 to 9.
 * A string t is called a semi-repetitive if there is at most one consecutive pair of the same digits
 * inside t. For example, 0010, 002020, 0123, 2002, and 54944 are semi-repetitive while 00101022, and
 * 1101234883 are not.
 * Return the length of the longest semi-repetitive substring inside s.
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * @tags    #sliding-window
 */


/**
 * @reference   Length of Longest Subarray With at Most K Frequency
 *              https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/
 *
 * You are given an integer array nums and an integer k.
 * The frequency of an element x is the number of times it occurs in an array.
 * An array is called good if the frequency of each element in this array is less than or equal to k.
 * Return the length of the longest good subarray of nums.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * @tags    #hash-table #sliding-window
 */


/**
 * @reference   Count Subarrays Where Max Element Appears at Least K Times
 *              https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/
 *
 * You are given an integer array nums and a positive integer k.
 * Return the number of subarrays where the maximum element of nums appears at least k times in that
 * subarray.
 * A subarray is a contiguous sequence of elements within an array.
 *
 * @tags    #sliding-window
 */
auto CountSubarraysWithAtLeastKMax(const ArrayType &nums, const std::size_t k) {
    const auto maximum = *std::max_element(nums.cbegin(), nums.cend());

    std::vector<int> index;
    long long result = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == maximum) {
            index.push_back(i);
        }

        if (index.size() >= k) {
            const auto j = index[index.size() - k];
            result += (i + 1) - (i - j);
        }
    }

    return result;
}


/**
 * @reference   Smallest Subarrays With Maximum Bitwise OR
 *              https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/
 *
 * You are given a 0-indexed array nums of length n, consisting of non-negative integers. For each index
 * i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of nums
 * starting at i (inclusive) that has the maximum possible bitwise OR.
 *  In other words, let Bij be the bitwise OR of the subarray nums[i...j]. You need to find the smallest
 *  subarray starting at i, such that bitwise OR of this subarray is equal to max(Bik) where i <= k <= n
 *  - 1.
 * The bitwise OR of an array is the bitwise OR of all the numbers in it.
 * Return an integer array answer of size n where answer[i] is the length of the minimum sized subarray
 * starting at i with maximum bitwise OR.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * @tags    #sliding-window #backward-traverse
 */
auto SmallestSubarraysWithMaxBitOr(const ArrayType &nums) {
    const int MAX_BIT_LENGTH = 30;

    ArrayType result(nums.size());
    std::vector<int> last_seen(MAX_BIT_LENGTH, 0);
    for (int i = nums.size() - 1; i >= 0; --i) {
        auto j = i;

        for (int bit = 0; bit < MAX_BIT_LENGTH; ++bit) {
            if (nums[i] & (1 << bit)) {
                last_seen[bit] = i;
            } else {
                j = std::max(j, last_seen[bit]);
            }
        }

        result[i] = j - i + 1;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {12, 10, 9, 45, 2, 10, 10, 45};
const ArrayType SAMPLE2 = {2, 1, 9, 5};


THE_BENCHMARK(CheckIfAllElementsDistinct, SAMPLE1);

SIMPLE_TEST(CheckIfAllElementsDistinct, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(CheckIfAllElementsDistinct, TestSAMPLE2, true, SAMPLE2);


THE_BENCHMARK(CheckIfAllElementsDistinct_Sort, SAMPLE1);

SIMPLE_TEST(CheckIfAllElementsDistinct_Sort, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(CheckIfAllElementsDistinct_Sort, TestSAMPLE2, true, SAMPLE2);


const ArrayType SAMPLE3 = {1, 2, 3, 1};
const ArrayType SAMPLE4 = {1, 0, 1, 1};
const ArrayType SAMPLE5 = {1, 2, 3, 1, 2, 3};


THE_BENCHMARK(ContainDuplicateAtMostKApart, SAMPLE1, 1);

SIMPLE_TEST(ContainDuplicateAtMostKApart, TestSAMPLE1, true, SAMPLE1, 1);
SIMPLE_TEST(ContainDuplicateAtMostKApart, TestSAMPLE2, false, SAMPLE2, SAMPLE2.size());
SIMPLE_TEST(ContainDuplicateAtMostKApart, TestSAMPLE3, true, SAMPLE3, 3);
SIMPLE_TEST(ContainDuplicateAtMostKApart, TestSAMPLE4, true, SAMPLE4, 1);
SIMPLE_TEST(ContainDuplicateAtMostKApart, TestSAMPLE5, false, SAMPLE5, 2);


const ArrayType SAMPLE7 = {1, 5, 9, 1, 5, 9};


THE_BENCHMARK(ContainAlmostDuplicateAtMostKApart_Set, SAMPLE1, 1, 0);

SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Set, TestSAMPLE1, true, SAMPLE1, 1, 0);
SIMPLE_TEST(
    ContainAlmostDuplicateAtMostKApart_Set, TestSAMPLE2, false, SAMPLE2, SAMPLE2.size(), 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Set, TestSAMPLE3, true, SAMPLE3, 3, 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Set, TestSAMPLE4, true, SAMPLE4, 1, 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Set, TestSAMPLE5, false, SAMPLE5, 2, 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Set, TestSAMPLE6, true, SAMPLE4, 1, 2);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Set, TestSAMPLE7, false, SAMPLE7, 2, 3);


THE_BENCHMARK(ContainAlmostDuplicateAtMostKApart_Bucket, SAMPLE1, 1, 0);

SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Bucket, TestSAMPLE1, true, SAMPLE1, 1, 0);
SIMPLE_TEST(
    ContainAlmostDuplicateAtMostKApart_Bucket, TestSAMPLE2, false, SAMPLE2, SAMPLE2.size(), 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Bucket, TestSAMPLE3, true, SAMPLE3, 3, 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Bucket, TestSAMPLE4, true, SAMPLE4, 1, 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Bucket, TestSAMPLE5, false, SAMPLE5, 2, 0);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Bucket, TestSAMPLE6, true, SAMPLE4, 1, 2);
SIMPLE_TEST(ContainAlmostDuplicateAtMostKApart_Bucket, TestSAMPLE7, false, SAMPLE7, 2, 3);


THE_BENCHMARK(LongestSubstrWithoutRepeatingChars_Last, "abcabcbb");

SIMPLE_TEST(LongestSubstrWithoutRepeatingChars_Last, TestSAMPLE1, 3, "abcabcbb");
SIMPLE_TEST(LongestSubstrWithoutRepeatingChars_Last, TestSAMPLE2, 1, "bbbbbb");
SIMPLE_TEST(LongestSubstrWithoutRepeatingChars_Last, TestSAMPLE3, 3, "pwwkew");


THE_BENCHMARK(LongestSubstrWithoutRepeatingChars_Count, "abcabcbb");

SIMPLE_TEST(LongestSubstrWithoutRepeatingChars_Count, TestSAMPLE1, 3, "abcabcbb");
SIMPLE_TEST(LongestSubstrWithoutRepeatingChars_Count, TestSAMPLE2, 1, "bbbbbb");
SIMPLE_TEST(LongestSubstrWithoutRepeatingChars_Count, TestSAMPLE3, 3, "pwwkew");


const ArrayType SAMPLE1M = {1, 3, 2, 3, 3, 3, 2, 1};
const ArrayType SAMPLE2M = {1, 4, 2, 1};


THE_BENCHMARK(CountSubarraysWithAtLeastKMax, SAMPLE1M, 2);

SIMPLE_TEST(CountSubarraysWithAtLeastKMax, TestSAMPLE1, 21, SAMPLE1M, 2);
SIMPLE_TEST(CountSubarraysWithAtLeastKMax, TestSAMPLE2, 0, SAMPLE2M, 3);


const ArrayType SAMPLE1B = {1, 0, 2, 1, 3};
const ArrayType EXPECTED1B = {3, 3, 2, 2, 1};

const ArrayType SAMPLE2B = {1, 2};
const ArrayType EXPECTED2B = {2, 1};

const ArrayType SAMPLE3B = {0};
const ArrayType EXPECTED3B = {1};


THE_BENCHMARK(SmallestSubarraysWithMaxBitOr, SAMPLE1B);

SIMPLE_TEST(SmallestSubarraysWithMaxBitOr, TestSAMPLE1, EXPECTED1B, SAMPLE1B);
SIMPLE_TEST(SmallestSubarraysWithMaxBitOr, TestSAMPLE2, EXPECTED2B, SAMPLE2B);
SIMPLE_TEST(SmallestSubarraysWithMaxBitOr, TestSAMPLE3, EXPECTED3B, SAMPLE3B);
