#include "common_header.h"


namespace {

/**Is divisible by 11
 *
 * @reference   Grade 7:  The Learning Equation Math
 *              11.04 Divisibility Rules
 *              http://staff.argyll.epsb.ca/jreed/math7/strand1/1104.htm
 *
 * The (sum of the odd numbered digits) - (sum of the even numbered digits) is divisible
 * by 11.
 */
constexpr auto isDivisibleBy11(int num) {
    if (num < 0) {
        num = -num;
    }
    if (num == 0 or num == 11) {
        return true;
    }
    if (num < 22) {
        return false;
    }

    bool positive = true;
    int last_digit{}, next_n{};
    int even_odd_diff = 0;
    while (num) {
        next_n = num / 10;
        last_digit = num - next_n * 10;
        if (positive) {
            even_odd_diff += last_digit;
        } else {
            even_odd_diff -= last_digit;
        }
        positive = !positive;
        num = next_n;
    }

    return isDivisibleBy11(even_odd_diff);
}


/**
 * @reference   Sub-string Divisibility by 11 Queries
 *              https://www.geeksforgeeks.org/sub-string-divisibility-11-queries/
 *
 * Given a large number, n (having number digits up to 10^6) and various queries of the
 * below form :
 *  Query(l, r) : find if the sub-string between the indices l and r (Both inclusive)
 *                are divisible by 11.
 *
 * @highlight   The use of inline keyword to silence the -Wunused-function warning.
 */
struct Query {
    std::size_t l;
    std::size_t r;
};

inline std::ostream &operator <<(std::ostream &out, const Query &q) {
    return out << "(" << q.l << ", " << q.r << ")";
}

auto SubstringDivisibilityBy11(const std::string_view test_string,
                               const std::vector<Query> &queries) {
    //Pre-compute diff of even and odd placed digits before this index
    std::vector<int> diffs(test_string.size() + 1);

    bool isEven = true;
    for (std::size_t i = 0; i < test_string.size(); ++i, isEven = !isEven) {
        diffs[i + 1] = diffs[i] + ((isEven ? 1 : -1) * (test_string[i] - '0'));
    }

    //Handle queries
    std::vector<bool> results;
    for (const auto &a_query : queries) {
        results.push_back(((diffs[a_query.r + 1] - diffs[a_query.l]) % 11) == 0);
    }
    return results;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();
constexpr int SAMPLE1 = -120;
constexpr int SAMPLE2 = -121;
constexpr int SAMPLE3 = 60;
constexpr int SAMPLE4 = 6600;


SIMPLE_BENCHMARK(isDivisibleBy11, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy11, Sample2, UPPER);
SIMPLE_BENCHMARK(isDivisibleBy11, Sample3, SAMPLE3);
SIMPLE_BENCHMARK(isDivisibleBy11, Sample4, SAMPLE4);

SIMPLE_TEST(isDivisibleBy11, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy11, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isDivisibleBy11, TestSAMPLE5, true, 0);


const std::vector<bool> EXPECTED_RESULTS = {true, true, false, true};


THE_BENCHMARK(SubstringDivisibilityBy11,
"122164154695", std::vector<Query> {{0, 3}, {1, 2}, {5, 9}, {0, 11}});

SIMPLE_TEST(SubstringDivisibilityBy11, TestLOWER, EXPECTED_RESULTS,
"122164154695", std::vector<Query> {{0, 3}, {1, 2}, {5, 9}, {0, 11}});
