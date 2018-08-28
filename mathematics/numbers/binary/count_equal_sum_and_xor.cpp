#include "common_header.h"

#include "count_unset_bits.h"

using InputType = unsigned;

/** Equal Sum and XOR
 *
 * @reference   https://www.geeksforgeeks.org/equal-sum-xor/
 *
 * Given a positive integer n, find count of positive integers i such that 0 <= i <= n and n+i = n^i.
 */
#ifdef __GNUG__
auto CountEqualSumAndXor(const InputType n) {
    return 1 << CountUnsetBits(n);
}


SIMPLE_BENCHMARK(CountEqualSumAndXor, 7);

SIMPLE_TEST(CountEqualSumAndXor, TestSample1, 4, 12);
SIMPLE_TEST(CountEqualSumAndXor, TestSample2, 1, 7);
#endif
