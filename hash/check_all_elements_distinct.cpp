#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Check if all array elements are distinct
 *
 * @reference   https://www.geeksforgeeks.org/check-if-all-array-elements-are-distinct/
 *
 * Given an array, check whether all elements in an array are distinct or not.
 *
 * @reference   Contains Duplicate
 *              https://leetcode.com/problems/contains-duplicate/
 *
 * Given an integer array nums, return true if any value appears at least twice in the
 * array, and return false if every element is distinct.
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
 * Implement an algorithm to determine if a string has all unique characters. What if you
 * cannot use additional data structures?
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
 * Given an integer array nums and an integer k, return true if there are two distinct
 * indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
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
 * Given an integer array nums and two integers k and t, return true if there are two
 * distinct indices i and j in the array such that abs(nums[i] - nums[j]) <= t and
 * abs(i - j) <= k.
 *
 * @reference   [LeetCode] Contains Duplicate III
 *              https://www.cnblogs.com/easonliu/p/4544073.html
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
 * Given a string s, find the length of the longest substring without repeating characters.
 * s consists of English letters, digits, symbols and spaces.
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
