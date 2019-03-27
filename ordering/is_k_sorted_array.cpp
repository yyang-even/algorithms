#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

#include "is_k_sorted_array.h"
}//namespace


const ArrayType SampleArray1 = {3, 2, 1, 5, 6, 4};
const ArrayType SampleArray2 = {13, 8, 10, 7, 15, 14, 12};

SIMPLE_BENCHMARK(IsKSorted, SampleArray1, 2);

SIMPLE_TEST(IsKSorted, TestSample1, true, SampleArray1, 2);
SIMPLE_TEST(IsKSorted, TestSample2, false, SampleArray2, 3);
