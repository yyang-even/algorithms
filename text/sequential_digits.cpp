#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Sequential Digits
 *
 * @reference   https://leetcode.com/problems/sequential-digits/
 *
 * An integer has sequential digits if and only if each digit in the number is one more
 * than the previous digit.
 * Return a sorted list of all the integers in the range [low, high] inclusive that have
 * sequential digits.
 * 10 <= low <= high <= 10^9
 */
auto SequentialDigits_BFS(const int low, const int high) {
    std::queue<int> q;
    for (auto i = 1; i <= 9; ++i) {
        q.push(i);
    }

    ArrayType result;
    while (!q.empty()) {
        const auto n = q.front();
        q.pop();

        if (n > high) {
            break;
        }
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

}//namespace


const ArrayType EXPECTED1 = {123, 234};
const ArrayType EXPECTED2 = {1234, 2345, 3456, 4567, 5678, 6789, 12345};


THE_BENCHMARK(SequentialDigits_BFS, 1000, 13000);

SIMPLE_TEST(SequentialDigits_BFS, TestSAMPLE1, EXPECTED1, 100, 300);
SIMPLE_TEST(SequentialDigits_BFS, TestSAMPLE2, EXPECTED2, 1000, 13000);
