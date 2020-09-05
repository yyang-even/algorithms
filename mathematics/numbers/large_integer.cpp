#include "common_header.h"

#include "large_integer.h"


namespace {

LargeInteger AddLargeIntegers(const LargeInteger &a, const LargeInteger &b) {
    return a + b;
}


LargeInteger MultiplyLargeIntegers(const LargeInteger &a, const LargeInteger &b) {
    return a * b;
}

}//namespace


SIMPLE_BENCHMARK(AddLargeIntegers, Sample1, LargeInteger("0"), LargeInteger("0"));
SIMPLE_BENCHMARK(AddLargeIntegers, Sample2, LargeInteger("0"), LargeInteger("10000000"));

SIMPLE_TEST(AddLargeIntegers, TestSAMPLE1, LargeInteger("0"), LargeInteger("0"), LargeInteger("0"));
SIMPLE_TEST(AddLargeIntegers, TestSAMPLE2, LargeInteger("17"), LargeInteger("8"),
            LargeInteger("9"));
SIMPLE_TEST(AddLargeIntegers, TestSAMPLE3, LargeInteger("210"), LargeInteger("10"),
            LargeInteger("200"));
SIMPLE_TEST(AddLargeIntegers, TestSAMPLE4, LargeInteger("1000000000000000"),
            LargeInteger("999999999999999"), LargeInteger("1"));


SIMPLE_BENCHMARK(MultiplyLargeIntegers, Sample1, LargeInteger("0"), LargeInteger("0"));
SIMPLE_BENCHMARK(MultiplyLargeIntegers, Sample2, LargeInteger("1"), LargeInteger("10000000"));
SIMPLE_BENCHMARK(MultiplyLargeIntegers, Sample3, LargeInteger("18"), LargeInteger("10000000"));

SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE1, LargeInteger("0"), LargeInteger("0"),
            LargeInteger("0"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE2, LargeInteger("72"), LargeInteger("8"),
            LargeInteger("9"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE3, LargeInteger("2000"), LargeInteger("10"),
            LargeInteger("200"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE4, LargeInteger("999999999999999"),
            LargeInteger("999999999999999"), LargeInteger("1"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE5, LargeInteger("216"), LargeInteger("18"),
            LargeInteger("12"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE6, LargeInteger("134959936636921125"),
            LargeInteger("521694835"), LargeInteger("258695175"));
