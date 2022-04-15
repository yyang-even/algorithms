#include "common_header.h"

#include "hash.h"

#include "text/remove_characters.h"


namespace {

using ArrayType = std::vector<int>;

/** Given a string, find its first non-repeating character
 *
 * @reference   https://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/
 * @reference   First non-repeating character using one traversal of string | Set 2
 *              https://www.geeksforgeeks.org/first-non-repeating-character-using-one-traversal-of-string-set-2/
 *
 * Given a string, find the first non-repeating character in it. For example, if the input
 * string is "GeeksforGeeks", then output should be 'f' and if input string is "GeeksQuiz",
 * then output should be 'G'.
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 6.
 *
 * @reference   Find the last non repeating character in string
 *              https://www.geeksforgeeks.org/find-the-last-non-repeating-character-in-string/
 *
 * @reference   First Unique Character in a String
 *              https://leetcode.com/problems/first-unique-character-in-a-string/
 *
 * Given a string s, find the first non-repeating character in it and return its index.
 * If it does not exist, return -1.
 */
auto FindFirstNonrepeatingChar(const std::string_view input) {
    std::unordered_map<char, std::size_t> counters;
    auto first_nonrepeated_index = input.size();

    for (std::string::size_type i = 0; i < input.size(); ++i) {
        const auto c = input[i];
        if (const auto [iter, inserted] = counters.emplace(c, i); not inserted) {
            iter->second = input.size();
        }
    }

    for (const auto [_, index] : counters) {
        if (index < first_nonrepeated_index) {
            first_nonrepeated_index = index;
        }
    }

    return input[first_nonrepeated_index];
}


/** Find the first non-repeating character from a stream of characters
 *
 * @reference   https://www.geeksforgeeks.org/find-first-non-repeating-character-stream-characters/
 *
 * Given a stream of characters, find the first non-repeating character from stream. You
 * need to tell the first non-repeating character in O(1) time at any moment.
 */
auto FindFirstNonrepeatingCharFromStream(const std::string_view input) {
    std::unordered_map<char, std::list<char>::const_iterator> char_map;
    std::list<char> nonreapting_chars;
    std::string outputs;

    for (const auto c : input) {
        const auto [iter, inserted] = char_map.emplace(c, nonreapting_chars.cend());
        if (inserted) {
            //first occurrence
            nonreapting_chars.emplace_back(c);
            iter->second = std::prev(nonreapting_chars.cend());
        } else if (iter->second != nonreapting_chars.cend()) {
            //second occurrence
            nonreapting_chars.erase(iter->second);
            iter->second = nonreapting_chars.cend();
        }

        if (not nonreapting_chars.empty()) {
            outputs.push_back(nonreapting_chars.front());
        }
    }

    return outputs;
}


/**
 * @reference   Queue based approach for first non-repeating character in a stream
 *              https://www.geeksforgeeks.org/queue-based-approach-for-first-non-repeating-character-in-a-stream/
 */
auto FindFirstNonrepeatingCharFromStream_Queue(const std::string_view input) {
    std::unordered_map<char, std::size_t> frequency_map;
    std::queue<char> char_queue;
    std::string outputs;

    for (const auto c : input) {
        if (const auto [iter, inserted] = frequency_map.emplace(c, 1); inserted) {
            char_queue.push(c);
        } else {
            ++(iter->second);
        }

        while (not char_queue.empty()) {
            if (frequency_map[char_queue.front()] > 1) {
                char_queue.pop();
            } else {
                outputs.push_back(char_queue.front());
                break;
            }
        }
    }

    return outputs;
}


/**
 * @reference   Largest Substring Between Two Equal Characters
 *              https://leetcode.com/problems/largest-substring-between-two-equal-characters/
 *
 * Given a string s, return the length of the longest substring between two equal
 * characters, excluding the two characters. If there is no such substring return -1.
 * A substring is a contiguous sequence of characters within a string.
 * s contains only lowercase English letters.
 */
int MaxLengthBetweenEqualChars(const std::string_view s) {
    std::vector first_indices(26, -1);
    const int N = s.size();

    int result = -1;
    for (int i = 0; i < N; ++i) {
        auto &f = first_indices[s[i] - 'a'];
        if (f == -1) {
            f = i;
        } else {
            result = std::max(result, i - f - 1);
        }
    }

    return result;
}


/** K’th Non-repeating Character
 *
 * @reference   https://www.geeksforgeeks.org/kth-non-repeating-character/
 *
 * Given a string and a number k, find the k'th non-repeating character in the string.
 * Consider a large input string with lots of characters and a small character set. How
 * to find the character by only doing only one traversal of input string?
 *
 * @reference   Kth Distinct String in an Array
 *              https://leetcode.com/problems/kth-distinct-string-in-an-array/
 *
 * A distinct string is a string that is present only once in an array.
 * Given an array of strings arr, and an integer k, return the kth distinct string present
 * in arr. If there are fewer than k distinct strings, return an empty string "".
 * Note that the strings are considered in the order in which they appear in the array.
 */
auto FindKthNonrepeatingChar(const std::string_view input, const std::size_t K) {
    std::unordered_map<char, std::size_t> counters;

    for (std::string::size_type i = 0; i < input.size(); ++i) {
        const auto c = input[i];
        if (const auto [iter, inserted] = counters.emplace(c, i); not inserted) {
            iter->second = input.size();
        }
    }

    std::vector<std::size_t> nonrepeating_char_indice;
    for (const auto [_, index] : counters) {
        if (index != input.size()) {
            nonrepeating_char_indice.push_back(index);
        }
    }

    std::nth_element(nonrepeating_char_indice.begin(),
                     nonrepeating_char_indice.begin() + K - 1,
                     nonrepeating_char_indice.end());

    return input[nonrepeating_char_indice[K - 1]];
}


constexpr char FindKthNonrepeatingChar_Count(const std::string_view s, int k) {
    int counts[256] = {};
    for (const int c : s) {
        ++counts[c];
    }

    for (const int c : s) {
        if (counts[c] == 1 and --k == 0) {
            return c;
        }
    }

    return '\0';
}


/** Elements that occurred only once in the array
 *
 * @reference   https://www.geeksforgeeks.org/elements-that-occurred-only-once-in-the-array/
 *
 * Given an array arr that has numbers appearing twice or once. The task is to identify
 * numbers that occurred only once in the array.
 * Note: Duplicates appear side by side every time. Might be few numbers can occur one
 * time and just assume this is a right rotating array (just say an array can rotate k
 * times towards right). Order of the elements in the output doesn't matter.
 */
auto ElementsThatOccurredOnlyOnce(const ArrayType &elements) {
    assert(elements.size() > 1);

    ArrayType::size_type i = 1;
    auto length = elements.size();

    if (elements.front() == elements.back()) {
        ++i;
        --length;
    }

    ArrayType output;
    for (; i < length; ++i) {
        const auto previous = elements[i - 1];
        if (elements[i] == previous) {
            ++i;
        } else {
            output.push_back(previous);
        }
    }

    if (elements[length - 1] != elements[length - 2]) {
        output.push_back(elements[length - 1]);
    }

    return output;
}


/** Print all distinct characters of a string in order (3 Methods)
 *
 * @reference   https://www.geeksforgeeks.org/print-all-distinct-characters-of-a-string-in-order-3-methods/
 *
 * Given a string, find the all distinct (or non-repeating characters) in it. For example,
 * if the input string is "Geeks for Geeks", then output should be 'for' and if input
 * string is "Geeks Quiz", then output should be 'GksQuiz'.
 */
inline auto GetAllElementsOccurredOnlyOnce(std::string input) {
    const auto counter = ToFrequencyHashTable(input);

    return RemoveCharacters_TwoPointers(std::move(input), [&counter](const auto c) {
        return c != ' ' and counter.at(c) == 1;
    });
}


auto GetAllElementsOccurredOnlyOnce_Linear(const std::string_view input) {
    std::unordered_set<char> counter;
    std::unordered_map<char, std::size_t> index_map;
    for (std::size_t i = 0; i < input.size(); ++i) {
        const auto c = input[i];
        if (counter.emplace(c).second) {
            if (c != ' ') {
                index_map.emplace(c, i);
            }
        } else {
            index_map.erase(c);
        }
    }

    std::vector<std::size_t> unique_index;
    for (const auto [value, index] : index_map) {
        unique_index.emplace_back(index);
    }

    std::sort(unique_index.begin(), unique_index.end());

    std::string output(unique_index.size(), 0);
    std::transform(unique_index.cbegin(), unique_index.cend(),
    output.begin(), [&input](const auto i) {
        return input[i];
    });

    return output;
}


/**
 * @reference   Largest Unique Number
 *              https://github.com/angelsophia1/LeetCode-Locked/blob/master/1133%09%20Largest%20Unique%20Number
 *
 * Given an array of integers A, return the largest integer that only occurs once. If no
 * integer occurs once, return -1.
 * 0 <= A[i] <= 1000
 */


/**
 * @reference   Sum of Unique Elements
 *              https://leetcode.com/problems/sum-of-unique-elements/
 *
 * You are given an integer array nums. The unique elements of an array are the elements
 * that appear exactly once in the array.
 * Return the sum of all the unique elements of nums.
 * 1 <= nums[i] <= 100
 */

}//namespace


THE_BENCHMARK(FindFirstNonrepeatingChar, "GeeksforGeeks");

SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE1, 'f', "GeeksforGeeks");
SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE2, 'G', "GeeksQuiz");
SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE3, 'd', "aabbccd");


THE_BENCHMARK(FindFirstNonrepeatingCharFromStream, "GeeksforGeeks");

SIMPLE_TEST(FindFirstNonrepeatingCharFromStream, TestSAMPLE1, "GGGGGGGGkkksf",
            "GeeksforGeeks");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream, TestSAMPLE2, "GGGGGGGGG", "GeeksQuiz");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream, TestSAMPLE3, "abcd", "aabbccd");


THE_BENCHMARK(FindFirstNonrepeatingCharFromStream_Queue, "GeeksforGeeks");

SIMPLE_TEST(FindFirstNonrepeatingCharFromStream_Queue, TestSAMPLE1, "GGGGGGGGkkksf",
            "GeeksforGeeks");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream_Queue, TestSAMPLE2, "GGGGGGGGG",
            "GeeksQuiz");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream_Queue, TestSAMPLE3, "abcd", "aabbccd");


THE_BENCHMARK(MaxLengthBetweenEqualChars, "aa");

SIMPLE_TEST(MaxLengthBetweenEqualChars, TestSAMPLE1, 0, "aa");
SIMPLE_TEST(MaxLengthBetweenEqualChars, TestSAMPLE2, 2, "abca");
SIMPLE_TEST(MaxLengthBetweenEqualChars, TestSAMPLE3, -1, "cbzxy");


THE_BENCHMARK(FindKthNonrepeatingChar, "GeeksforGeeks", 3);

SIMPLE_TEST(FindKthNonrepeatingChar, TestSAMPLE1, 'r', "GeeksforGeeks", 3);
SIMPLE_TEST(FindKthNonrepeatingChar, TestSAMPLE2, 'o', "GeeksforGeeks", 2);


THE_BENCHMARK(FindKthNonrepeatingChar_Count, "GeeksforGeeks", 3);

SIMPLE_TEST(FindKthNonrepeatingChar_Count, TestSAMPLE1, 'r', "GeeksforGeeks", 3);
SIMPLE_TEST(FindKthNonrepeatingChar_Count, TestSAMPLE2, 'o', "GeeksforGeeks", 2);


const ArrayType SAMPLE1 = {7, 7, 8, 8, 9, 1, 1, 4, 2, 2};
const ArrayType EXPECTED1 = {9, 4};
const ArrayType SAMPLE2 = { -9, -8, 4, 4, 5, 5, -1};
const ArrayType EXPECTED2 = { -9, -8, -1};
const ArrayType SAMPLE3 = {3, 7, 7, 8, 8, 9, 1, 1, 4, 2, 2, 3};
const ArrayType SAMPLE4 = {1, -9, -8, 4, 4, 5, 5, -1, 1};


THE_BENCHMARK(ElementsThatOccurredOnlyOnce, SAMPLE1);

SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE3, EXPECTED1, SAMPLE3);
SIMPLE_TEST(ElementsThatOccurredOnlyOnce, TestSAMPLE4, EXPECTED2, SAMPLE4);


THE_BENCHMARK(GetAllElementsOccurredOnlyOnce, "Geeks for Geeks");

SIMPLE_TEST(GetAllElementsOccurredOnlyOnce, TestSAMPLE1, "for", "Geeks for Geeks");
SIMPLE_TEST(GetAllElementsOccurredOnlyOnce, TestSAMPLE2, "HoGks", "Hello Geeks");


THE_BENCHMARK(GetAllElementsOccurredOnlyOnce_Linear, "Geeks for Geeks");

SIMPLE_TEST(GetAllElementsOccurredOnlyOnce_Linear, TestSAMPLE1, "for",
            "Geeks for Geeks");
SIMPLE_TEST(GetAllElementsOccurredOnlyOnce_Linear, TestSAMPLE2, "HoGks", "Hello Geeks");
