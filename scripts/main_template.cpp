#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 *
 * @reference
 */
auto FunctionName(const ArrayType &nums) {
}

} //namespace


const ArrayType SAMPLE1 = {};


THE_BENCHMARK(FunctionName, SAMPLE1);

SIMPLE_TEST(FunctionName, TestSAMPLE1, EXPECTED1, SAMPLE1);
