#include "common_header.h"


namespace {

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
