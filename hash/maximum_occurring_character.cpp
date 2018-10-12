#include "common_header.h"

#include "repeated_elements.h"

/** Return maximum occurring character in an input string
 *
 * @reference   https://www.geeksforgeeks.org/return-maximum-occurring-character-in-the-input-string/
 *
 * Write an efficient function to return maximum occurring character in the input
 * string e.g., if input string is “test” then function should return ‘t’.
 */
auto MaximumOccurringChar(const std::string &input) {
    std::unordered_map<std::string::value_type, std::string::size_type> counters;

    for (const auto c : input) {
        ++counters[c];
    }

    std::string::size_type max = 0ul;
    std::string::value_type max_char = input.front();

    for (const auto count : counters) {
        if (count.second > max) {
            max_char = count.first;
            max = count.second;
        }
    }

    return max_char;
}


/** Find the maximum repeating number in O(n) time and O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/find-the-maximum-repeating-number-in-ok-time/
 *
 * Given an array of size n, the array contains numbers in range from 0 to k-1 where k
 * is a positive integer and k <= n. Find the maximum repeating number in this array.
 * For example, let k be 10 the given array be
 * arr[] = {1, 2, 2, 2, 0, 2, 0, 2, 3, 8, 0, 9, 2, 3}, the maximum repeating number
 * would be 2. Expected time complexity is O(n) and extra space allowed is O(1).
 * Modifications to array are allowed.
 */
using ArrayType = std::vector<int>;

auto MaximumRepeatingNumberInplace(ArrayType numbers, const ArrayType::value_type K) {
    assert(K <= numbers.size());

    TransformToInplaceCounterArray(numbers, K);

    return std::max_element(numbers.cbegin(), numbers.cend()) - numbers.cbegin();
}


SIMPLE_BENCHMARK(MaximumOccurringChar, std::string("sample string"));

SIMPLE_TEST(MaximumOccurringChar, TestSAMPLE1, 's', std::string("sample string"));
SIMPLE_TEST(MaximumOccurringChar, TestSAMPLE2, 't', std::string("test"));


const ArrayType SAMPLE1 = {1, 2, 2, 2, 0, 2, 0, 2, 3, 8, 0, 9, 2, 3};
const ArrayType SAMPLE2 = {2, 3, 3, 5, 3, 4, 1, 7};

SIMPLE_BENCHMARK(MaximumRepeatingNumberInplace, SAMPLE1, 10);

SIMPLE_TEST(MaximumRepeatingNumberInplace, TestSAMPLE1, 2, SAMPLE1, 10);
SIMPLE_TEST(MaximumRepeatingNumberInplace, TestSAMPLE2, 3, SAMPLE2, 8);
