#include "common_header.h"

#include <charconv>


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Sequential Digits
 *              https://leetcode.com/problems/sequential-digits/
 *
 * An integer has sequential digits if and only if each digit in the number is one more than the
 * previous digit.
 * Return a sorted list of all the integers in the range [low, high] inclusive that have sequential
 * digits.
 * 10 <= low <= high <= 10^9
 *
 * * @tags    #BFS #modulo #queue #sliding-window
 */
auto SequentialDigits_BFS(const int low, const int high) {
    std::queue<int> q;
    for (auto i = 1; i < 9; ++i) {
        q.push(i);
    }

    ArrayType result;
    while (not q.empty() and q.front() <= high) {
        const auto n = q.front();
        q.pop();

        if (n >= low) {
            result.push_back(n);
        }

        const auto last_digit = n % 10;
        if (last_digit < 9) {
            q.push(n * 10 + last_digit + 1);
        }
    }

    return result;
}

auto SequentialDigits_SlidingWindow(const int low, const int high) {
    const auto *s = "123456789";
    const auto start_length = std::to_string(low).size();
    const auto end_length = std::to_string(high).size();

    ArrayType result;
    for (auto length = start_length; length <= end_length; ++length) {
        for (std::size_t i = 0; i + length <= 9; ++i) {
            int n {};
            std::from_chars(s + i, s + i + length, n);
            if (n >= low and n <= high) {
                result.push_back(n);
            }
        }
    }

    return result;
}

} //namespace


const ArrayType EXPECTED1 = {123, 234};
const ArrayType EXPECTED2 = {1234, 2345, 3456, 4567, 5678, 6789, 12345};


THE_BENCHMARK(SequentialDigits_BFS, 1000, 13000);

SIMPLE_TEST(SequentialDigits_BFS, TestSAMPLE1, EXPECTED1, 100, 300);
SIMPLE_TEST(SequentialDigits_BFS, TestSAMPLE2, EXPECTED2, 1000, 13000);


THE_BENCHMARK(SequentialDigits_SlidingWindow, 1000, 13000);

SIMPLE_TEST(SequentialDigits_SlidingWindow, TestSAMPLE1, EXPECTED1, 100, 300);
SIMPLE_TEST(SequentialDigits_SlidingWindow, TestSAMPLE2, EXPECTED2, 1000, 13000);
