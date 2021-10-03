#include "common_header.h"

#include "hash.h"

#include "text/remove_characters.h"


namespace {

using ArrayType = std::vector<int>;

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

    std::vector<std::pair<std::size_t, char>> index_char_array;
    for (const auto [value, index] : index_map) {
        index_char_array.emplace_back(index, value);
    }

    std::sort(index_char_array.begin(), index_char_array.end());

    std::string output(index_map.size(), ' ');
    std::transform(index_char_array.cbegin(), index_char_array.cend(),
    output.begin(), [](const auto & index_char_pair) {
        return index_char_pair.second;
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

}//namespace


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
