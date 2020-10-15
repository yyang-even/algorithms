#include "common_header.h"


namespace {

/** Given a string, find its first non-repeating character
 *
 * @reference   https://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/
 * @reference   First non-repeating character using one traversal of string | Set 2
 *              https://www.geeksforgeeks.org/first-non-repeating-character-using-one-traversal-of-string-set-2/
 *
 * Given a string, find the first non-repeating character in it. For example, if the
 * input string is “GeeksforGeeks”, then output should be ‘f’ and if input string is
 * “GeeksQuiz”, then output should be ‘G’.
 *
 * @reference   Find the last non repeating character in string
 *              https://www.geeksforgeeks.org/find-the-last-non-repeating-character-in-string/
 */
auto FindFirstNonrepeatingChar(const std::string &input) {
    std::unordered_map<std::string::value_type, std::string::size_type> counters;
    auto first_nonrepeated_index = input.size();

    for (std::string::size_type i = 0ul; i < input.size(); ++i) {
        const auto c = input[i];
        auto iter = counters.find(c);
        if (iter == counters.cend()) {
            counters.emplace(c, i);
        } else {
            iter->second = input.size();
        }
    }
    for (const auto elem : counters) {
        if (elem.second < first_nonrepeated_index) {
            first_nonrepeated_index = elem.second;
        }
    }

    return input[first_nonrepeated_index];
}


/** Find the first non-repeating character from a stream of characters
 *
 * @reference   https://www.geeksforgeeks.org/find-first-non-repeating-character-stream-characters/
 *
 * Given a stream of characters, find the first non-repeating character from stream.
 * You need to tell the first non-repeating character in O(1) time at any moment.
 */
auto FindFirstNonrepeatingCharFromStream(const std::string &input) {
    std::unordered_map<std::string::value_type,
        std::list<std::string::value_type>::const_iterator> char_map;
    std::list<std::string::value_type> nonreapting_chars;
    std::string outputs;

    for (const auto c : input) {
        const auto iter = char_map.find(c);
        if (iter == char_map.cend()) {
            //first occurrence
            nonreapting_chars.emplace_back(c);
            char_map.emplace(c, std::prev(nonreapting_chars.cend()));
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
auto FindFirstNonrepeatingCharFromStream_Queue(const std::string &input) {
    std::unordered_map<std::string::value_type, std::string::size_type> frequency_map;
    std::queue<std::string::value_type> char_queue;
    std::string outputs;

    for (const auto c : input) {
        const auto iter = frequency_map.find(c);
        if (iter == frequency_map.cend()) {
            frequency_map.emplace(c, 1);
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

}//namespace


SIMPLE_BENCHMARK(FindFirstNonrepeatingChar, Sample1, "GeeksforGeeks");

SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE1, 'f', "GeeksforGeeks");
SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE2, 'G', "GeeksQuiz");
SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE3, 'd', "aabbccd");


SIMPLE_BENCHMARK(FindFirstNonrepeatingCharFromStream, Sample1, "GeeksforGeeks");

SIMPLE_TEST(FindFirstNonrepeatingCharFromStream, TestSAMPLE1, "GGGGGGGGkkksf",
            "GeeksforGeeks");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream, TestSAMPLE2, "GGGGGGGGG", "GeeksQuiz");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream, TestSAMPLE3, "abcd", "aabbccd");


SIMPLE_BENCHMARK(FindFirstNonrepeatingCharFromStream_Queue, Sample1, "GeeksforGeeks");

SIMPLE_TEST(FindFirstNonrepeatingCharFromStream_Queue, TestSAMPLE1, "GGGGGGGGkkksf",
            "GeeksforGeeks");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream_Queue, TestSAMPLE2, "GGGGGGGGG",
            "GeeksQuiz");
SIMPLE_TEST(FindFirstNonrepeatingCharFromStream_Queue, TestSAMPLE3, "abcd", "aabbccd");
