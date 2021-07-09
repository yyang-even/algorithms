#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<std::string>;

/** Missing Ranges
 *
 * @reference   https://medium.com/@rebeccahezhang/leetcode-163-missing-ranges-6ac21b477e96
 *
 * Given a sorted integer array nums, where the range of elements are in the inclusive
 * range [lower, upper], return its missing ranges.
 */
auto toString(const ArrayType::value_type lower,
              const ArrayType::value_type upper) {
    auto result = std::to_string(lower);
    if (lower < upper) {
        result.append("->");
        result.append(std::to_string(upper));
    }

    return result;
}

auto MissingRanges(const ArrayType &elements,
                   const ArrayType::value_type lower, const ArrayType::value_type upper) {
    OutputType results;
    auto prev = lower - 1;
    for (const auto a_number : elements) {
        const auto expected = prev + 1;
        if (expected != a_number) {
            results.push_back(toString(expected, a_number - 1));
        }
        prev = a_number;
    }

    if (prev != upper) {
        results.push_back(toString(prev + 1, upper));
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {0, 1, 3, 50, 75};
const OutputType EXPECTED1 = {"2", "4->49", "51->74", "76->99"};

const ArrayType SAMPLE2 = {3, 50, 75, 99};
const OutputType EXPECTED2 = {"0->2", "4->49", "51->74", "76->98"};

const ArrayType SAMPLE3 = {1, 3, 50, 75, 98};
const OutputType EXPECTED3 = {"0", "2", "4->49", "51->74", "76->97", "99"};


THE_BENCHMARK(MissingRanges, SAMPLE1, 0, 99);

SIMPLE_TEST(MissingRanges, TestSAMPLE1, EXPECTED1, SAMPLE1, 0, 99);
SIMPLE_TEST(MissingRanges, TestSAMPLE2, EXPECTED2, SAMPLE2, 0, 99);
SIMPLE_TEST(MissingRanges, TestSAMPLE3, EXPECTED3, SAMPLE3, 0, 99);
