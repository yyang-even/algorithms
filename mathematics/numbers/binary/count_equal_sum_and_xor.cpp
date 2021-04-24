#include "common_header.h"

#include "count_unset_bits.h"


#ifdef __GNUG__
namespace {

/** Equal Sum and XOR
 *
 * @reference   https://www.geeksforgeeks.org/equal-sum-xor/
 * @reference   Bits manipulation (Important tactics)
 *              https://www.geeksforgeeks.org/bits-manipulation-important-tactics/
 *
 * Given a positive integer n, find count of positive integers i such that 0 <= i <= n
 * and n+i = n^i.
 */
constexpr inline auto CountEqualSumAndXor(const unsigned n) {
    return 1 << CountUnsetBits(n);
}

}//namespace


THE_BENCHMARK(CountEqualSumAndXor, 7);

SIMPLE_TEST(CountEqualSumAndXor, TestSample1, 4, 12);
SIMPLE_TEST(CountEqualSumAndXor, TestSample2, 1, 7);
#endif
