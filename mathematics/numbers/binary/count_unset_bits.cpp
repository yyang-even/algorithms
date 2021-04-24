#include "common_header.h"

#include "count_unset_bits.h"


#ifdef __GNUG__
THE_BENCHMARK(CountUnsetBits, 0);

SIMPLE_TEST(CountUnsetBits, TestSample1, 0, 0);
SIMPLE_TEST(CountUnsetBits, TestSample2, 3, 17);
SIMPLE_TEST(CountUnsetBits, TestSample3, 0, 7);
#endif
