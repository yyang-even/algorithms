#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 *
 * @reference
 */

}//namespace


const ArrayType SAMPLE1 = {};


SIMPLE_BENCHMARK(FunctionName, SAMPLE1);

SIMPLE_TEST(FunctionName, TestSAMPLE1, EXPECTED1, SAMPLE1);
MUTUAL_SIMPLE_TEST(ExpectedFunctionName, FunctionName, TestSample1, SAMPLE1);
