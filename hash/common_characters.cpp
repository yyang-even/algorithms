#include "common_header.h"

#include "hash.h"


namespace {

using ArrayType = std::vector<std::string_view>;
using NumArrayType = std::vector<int>;

/** Check if two strings have a common substring
 *
 * @reference   https://www.geeksforgeeks.org/check-two-strings-common-substring/
 * @reference   Check if there is any common character in two given strings
 *              https://www.geeksforgeeks.org/check-if-there-is-any-common-character-in-two-given-strings/
 */
template <typename Container>
constexpr auto HaveCommonElement(const Container &X, const Container &Y) {
    std::unordered_set one_set_characters(X.cbegin(), X.cend());
    for (const auto c : Y) {
        if (one_set_characters.find(c) != one_set_characters.cend()) {
            return true;
        }
    }

    return false;
}

inline constexpr auto
HaveCommonSubstring(const std::string_view X, const std::string_view Y) {
    return HaveCommonElement(X, Y);
}


/** How to check if two given sets are disjoint?
 *
 * @reference   https://www.geeksforgeeks.org/check-two-given-sets-disjoint/
 */
inline auto AreTwoSetsDisjoint_Hash(const NumArrayType &lhs, const NumArrayType &rhs) {
    return not HaveCommonElement(lhs, rhs);
}


bool AreTwoSetsDisjoint_BinarySearch(const NumArrayType &lhs, const NumArrayType &rhs) {
    if (lhs.size() > rhs.size()) {
        return AreTwoSetsDisjoint_Hash(rhs, lhs);
    }

    auto sorted_lhs = lhs;
    std::sort(sorted_lhs.begin(), sorted_lhs.end());

    for (const auto element : rhs) {
        if (not std::binary_search(sorted_lhs.cbegin(), sorted_lhs.cend(), element)) {
            return false;
        }
    }

    return true;
}


/** Count common characters in two strings
 *
 * @reference   https://www.geeksforgeeks.org/count-common-characters-in-two-strings/
 *
 * Given two strings s1 and s2 consisting of lowercase English alphabets, the task is to
 * count all the pairs of indices (i, j) from the given strings such that s1[i] = s2[j]
 * and all the indices are distinct i.e. if s1[i] pairs with some s2[j] then these two
 * characters will not be paired with any other character.
 *
 * @reference   Intersection of Two Arrays II
 *              https://leetcode.com/problems/intersection-of-two-arrays-ii/
 *
 * Given two integer arrays nums1 and nums2, return an array of their intersection. Each
 * element in the result must appear as many times as it shows in both arrays and you
 * may return the result in any order.
 * 0 <= nums1[i], nums2[i] <= 1000
 * Follow up:
 *  What if the given array is already sorted? How would you optimize your algorithm?
 *  What if nums1's size is small compared to nums2's size? Which algorithm is better?
 *  What if elements of nums2 are stored on disk, and the memory is limited such that
 *      you cannot load all elements into the memory at once?
 */
auto CountCommonChars(const std::string_view X, const std::string_view Y) {
    auto one_set_characters = ToFrequencyHashTable(X);

    unsigned count = 0;
    for (const auto c : Y) {
        if ((one_set_characters[c])-- > 0) {
            ++count;
        }
    }

    return count;
}


/** Print common characters of two Strings in alphabetical order
 *
 * @reference   https://www.geeksforgeeks.org/print-common-characters-two-strings-alphabetical-order-2/
 *
 * Given two strings, print all the common characters in lexicographical order. If there
 * are no common letters, print -1. All letters are lower case.
 */
auto GetCommonChars(const std::string_view X, const std::string_view Y) {
    assert(std::all_of(X.cbegin(), X.cend(), islower));
    assert(std::all_of(Y.cbegin(), Y.cend(), islower));

    auto one_set_characters = ToFrequencyHashTable(X);

    std::vector<unsigned> common_chars(26, 0);
    for (const auto c : Y) {
        if ((one_set_characters[c])-- > 0) {
            ++(common_chars[c - 'a']);
        }
    }

    std::string results;
    for (char i = 0; i < 26; ++i) {
        for (unsigned j = 0; j < common_chars[i]; ++j) {
            results.push_back('a' + i);
        }
    }

    return results;
}


/**
 * @reference   Union and Intersection of two sorted arrays
 *              https://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/
 */
auto Intersection_Sorted(const std::string_view one, const std::string_view another) {
    assert(std::is_sorted(one.cbegin(), one.cend()));
    assert(std::is_sorted(another.cbegin(), another.cend()));

    std::size_t one_i = 0, another_i = 0;
    std::string results;
    while (one_i < one.size() and another_i < another.size()) {
        if (one[one_i] < another[another_i]) {
            ++one_i;
        } else if (one[one_i] > another[another_i]) {
            ++another_i;
        } else {
            results.push_back(one[one_i++]);
            ++another_i;
        }
    }

    return results;
}

inline auto Intersection_Sort(std::string one, std::string another) {
    std::sort(one.begin(), one.end());
    std::sort(another.begin(), another.end());
    return Intersection_Sorted(one, another);
}


/**
 * @reference   Intersection of Two Arrays
 *              https://leetcode.com/problems/intersection-of-two-arrays/
 *
 * Given two integer arrays nums1 and nums2, return an array of their intersection. Each
 * element in the result must be unique and you may return the result in any order.
 *  0 <= nums1[i], nums2[i] <= 1000
 */


/** Common characters in n strings
 *
 * @reference   https://www.geeksforgeeks.org/common-characters-n-strings/
 */
auto CommonCharsOfStrings(const ArrayType &strings) {
    assert(std::all_of(strings.cbegin(), strings.cend(), [](const auto & a_string) {
        return std::all_of(a_string.cbegin(), a_string.cend(), islower);
    }));

    std::vector<int> all_common_chars(26, std::numeric_limits<int>::max());
    for (const auto a_string : strings) {
        std::vector<int> common_chars_of_two(26, 0);
        for (const auto c : a_string) {
            const auto index = c - 'a';
            if ((all_common_chars[index])-- > 0) {
                ++(common_chars_of_two[index]);
            }
        }

        all_common_chars.swap(common_chars_of_two);
    }

    std::string results;
    for (char i = 0; i < 26; ++i) {
        for (int j = 0; j < all_common_chars[i]; ++j) {
            results.push_back('a' + i);
        }
    }

    return results;
}


/**
 * @reference   Find uncommon characters of the two strings
 *              https://www.geeksforgeeks.org/find-uncommon-characters-two-strings/
 *
 * Find and print the uncommon characters of the two given strings in sorted order. Here
 * uncommon character means that either the character is present in one string or it is
 * present in other string but not in both. The strings contain only lowercase characters
 * and can contain duplicates.
 */
auto UncommonChars_Hash(const std::string_view X, const std::string_view Y) {
    assert(std::all_of(X.cbegin(), X.cend(), islower));
    assert(std::all_of(Y.cbegin(), Y.cend(), islower));

    std::unordered_map<char, int> char_map;
    for (const auto c : X) {
        char_map[c] = 1;
    }

    for (const auto c : Y) {
        if (char_map[c] == 1) {
            char_map[c] = -1;
        } else if (char_map[c] != -1) {
            char_map[c] = 2;
        }
    }

    std::string results;
    for (char i = 0; i < 26; ++i) {
        const auto c = 'a' + i;
        if (char_map[c] > 0) {
            results.push_back(c);
        }
    }

    return results;
}


/**
 * @reference   Find uncommon characters of the two strings | Set 2
 *              https://www.geeksforgeeks.org/find-uncommon-characters-of-the-two-strings-set-2/
 */
auto UncommonChars_Bits(const std::string_view X, const std::string_view Y) {
    assert(std::all_of(X.cbegin(), X.cend(), islower));
    assert(std::all_of(Y.cbegin(), Y.cend(), islower));

    unsigned char_set_x = 0;
    for (const auto c : X) {
        char_set_x |= (1 << (c - 'a'));
    }

    unsigned char_set_y = 0;
    for (const auto c : Y) {
        char_set_y |= (1 << (c - 'a'));
    }

    auto uncommon_chars_set = char_set_x ^ char_set_y;
    std::string results;
    for (char i = 0; i < 26; ++i, uncommon_chars_set >>= 1) {
        if ((uncommon_chars_set & 1) == 1) {
            results.push_back('a' + i);
        }
    }

    return results;
}


/** Find the overlapping sum of two arrays
 *
 * @reference   https://www.geeksforgeeks.org/find-the-overlapping-sum-of-two-arrays/
 *
 * Given two arrays A[] and B[] having n unique elements each. The task is to find the
 * overlapping sum of the two arrays. That is the sum of elements which is common in both
 * of the arrays.
 *
 * @complexity  O(n)
 */
auto OverlappingSumOfArrays(const NumArrayType &a1, const NumArrayType &a2) {
    const auto *smaller = &a1;
    const auto *larger = &a2;
    if (smaller->size() > larger->size()) {
        std::swap(smaller, larger);
    }

    const auto counters = ToUnorderedSet(*larger);
    int sum = 0;

    for (const auto elem : *smaller) {
        if (counters.find(elem) != counters.cend()) {
            sum += elem * 2;
        }
    }

    return sum;
}


/**
 * @reference   Find Union and Intersection of two unsorted arrays
 *              https://www.geeksforgeeks.org/find-union-and-intersection-of-two-unsorted-arrays/
 *
 * Given two unsorted arrays that represent two sets (elements in every array are
 * distinct), find the union and intersection of two arrays.
 */
inline auto Union_Unsorted(const NumArrayType &one, const NumArrayType &another) {
    std::unordered_set commons(one.cbegin(), one.cend());
    commons.insert(another.cbegin(), another.cend());
    return commons;
}


auto Union_Sorted(const NumArrayType &one, const NumArrayType &another) {
    assert(std::is_sorted(one.cbegin(), one.cend()));
    assert(std::is_sorted(another.cbegin(), another.cend()));

    std::size_t one_i = 0, another_i = 0;
    std::unordered_set<int> results;
    while (one_i < one.size() and another_i < another.size()) {
        if (one[one_i] < another[another_i]) {
            results.insert(one[one_i++]);
        } else if (one[one_i] > another[another_i]) {
            results.insert(another[another_i++]);
        } else {
            results.insert(one[one_i++]);
            ++another_i;
        }
    }

    while (one_i < one.size()) {
        results.insert(one[one_i++]);
    }

    while (another_i < another.size()) {
        results.insert(another[another_i++]);
    }

    return results;
}

inline auto Union_Unsorted_Sort(NumArrayType one, NumArrayType another) {
    std::sort(one.begin(), one.end());
    std::sort(another.begin(), another.end());

    return Union_Sorted(one, another);
}

}//namespace


THE_BENCHMARK(HaveCommonSubstring, "HELLO", "WORLD");

SIMPLE_TEST(HaveCommonSubstring, TestSAMPLE1, true, "HELLO", "WORLD");
SIMPLE_TEST(HaveCommonSubstring, TestSAMPLE2, false, "HI", "ALL");


THE_BENCHMARK(CountCommonChars, "HELLO", "WORLD");

SIMPLE_TEST(CountCommonChars, TestSAMPLE1, 2, "HELLO", "WORLD");
SIMPLE_TEST(CountCommonChars, TestSAMPLE2, 0, "HI", "ALL");
SIMPLE_TEST(CountCommonChars, TestSAMPLE3, 2, "abcd", "aad");
SIMPLE_TEST(CountCommonChars, TestSAMPLE4, 8, "geeksforgeeks", "platformforgeeks");


THE_BENCHMARK(GetCommonChars, "geeks", "forgeeks");

SIMPLE_TEST(GetCommonChars, TestSAMPLE1, "eegks", "geeks", "forgeeks");
SIMPLE_TEST(GetCommonChars, TestSAMPLE2, "hhh", "hhhhhello", "gfghhmh");


THE_BENCHMARK(Intersection_Sort, "geeks", "forgeeks");

SIMPLE_TEST(Intersection_Sort, TestSAMPLE1, "eegks", "geeks", "forgeeks");
SIMPLE_TEST(Intersection_Sort, TestSAMPLE2, "hhh", "hhhhhello", "gfghhmh");


const ArrayType SAMPLE1 = {"geeksforgeeks", "gemkstones", "acknowledges", "aguelikes"};
const ArrayType SAMPLE2 = {"apple", "orange"};


THE_BENCHMARK(CommonCharsOfStrings, SAMPLE1);

SIMPLE_TEST(CommonCharsOfStrings, TestSAMPLE1, "eegks", SAMPLE1);
SIMPLE_TEST(CommonCharsOfStrings, TestSAMPLE2, "ae", SAMPLE2);


THE_BENCHMARK(UncommonChars_Hash, "characters", "alphabets");

SIMPLE_TEST(UncommonChars_Hash, TestSAMPLE1, "bclpr", "characters", "alphabets");
SIMPLE_TEST(UncommonChars_Hash, TestSAMPLE2, "fioqruz", "geeksforgeeks", "geeksquiz");


THE_BENCHMARK(UncommonChars_Bits, "characters", "alphabets");

SIMPLE_TEST(UncommonChars_Bits, TestSAMPLE1, "bclpr", "characters", "alphabets");
SIMPLE_TEST(UncommonChars_Bits, TestSAMPLE2, "fioqruz", "geeksforgeeks", "geeksquiz");


const NumArrayType SAMPLE1_X = {12, 34, 11, 9, 3};
const NumArrayType SAMPLE1_Y = {2, 1, 3, 5};

const NumArrayType SAMPLE2_Y = {7, 2, 1, 5};

const NumArrayType SAMPLE3_X = {10, 5, 3, 4, 6};
const NumArrayType SAMPLE3_Y = {8, 7, 9, 3};


THE_BENCHMARK(AreTwoSetsDisjoint_Hash, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(AreTwoSetsDisjoint_Hash, TestSAMPLE1, false, SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_Hash, TestSAMPLE2, true, SAMPLE1_X, SAMPLE2_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_Hash, TestSAMPLE3, false, SAMPLE3_X, SAMPLE3_Y);


THE_BENCHMARK(AreTwoSetsDisjoint_BinarySearch, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(AreTwoSetsDisjoint_BinarySearch, TestSAMPLE1, false, SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_BinarySearch, TestSAMPLE2, true, SAMPLE1_X, SAMPLE2_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_BinarySearch, TestSAMPLE3, false, SAMPLE3_X, SAMPLE3_Y);


const NumArrayType SAMPLE1L = {1, 5, 3, 8};
const NumArrayType SAMPLE1R = {5, 4, 6, 7};


THE_BENCHMARK(OverlappingSumOfArrays, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(OverlappingSumOfArrays, TestSAMPLE1, 10, SAMPLE1L, SAMPLE1R);


const std::unordered_set EXPECTED1 = {1, 3, 4, 5, 6, 7, 8};


THE_BENCHMARK(Union_Unsorted, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(Union_Unsorted, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);


THE_BENCHMARK(Union_Unsorted_Sort, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(Union_Unsorted_Sort, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
