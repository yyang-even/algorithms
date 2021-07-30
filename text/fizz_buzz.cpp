#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Fizz Buzz
 *
 * @reference   https://leetcode.com/problems/fizz-buzz/
 *
 * Given an integer n, return a string array answer (1-indexed) where:
 *  answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
 *  answer[i] == "Fizz" if i is divisible by 3.
 *  answer[i] == "Buzz" if i is divisible by 5.
 *  answer[i] == i if non of the above conditions are true.
 */
auto FizzBuzz(const int n) {
    ArrayType results;

    for (int i = 1; i <= n; ++i) {
        results.emplace_back();
        auto &str = results.back();

        if (i % 3 == 0) {
            str = "Fizz";
        }

        if (i % 5 == 0) {
            str += "Buzz";
        }

        if (str.empty()) {
            str = std::to_string(i);
        }
    }

    return results;
}


auto FizzBuzz_Hash(const int n) {
    const std::map<int, std::string> fizz_buzz_map = {
        {3, "Fizz"},
        {5, "Buzz"}
    };

    ArrayType results;

    for (int i = 1; i <= n; ++i) {
        results.emplace_back();
        auto &str = results.back();

        for (const auto &[key, word] : fizz_buzz_map) {
            if (i % key == 0) {
                str += word;
            }
        }

        if (str.empty()) {
            str = std::to_string(i);
        }
    }

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz"};


THE_BENCHMARK(FizzBuzz, 15);

SIMPLE_TEST(FizzBuzz, TestSAMPLE1, EXPECTED1, 15);


THE_BENCHMARK(FizzBuzz_Hash, 15);

SIMPLE_TEST(FizzBuzz_Hash, TestSAMPLE1, EXPECTED1, 15);
