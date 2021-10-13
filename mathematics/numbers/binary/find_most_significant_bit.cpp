#include "common_header.h"

#include "find_most_significant_bit.h"


namespace {

inline constexpr unsigned FindMSB_Float(const unsigned num) {
    return std::pow(2, static_cast<unsigned>(std::log2(num)));
}

}//namespace


constexpr auto LOWER = 1u;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


THE_BENCHMARK(FindMSB, 4);

SIMPLE_TEST(FindMSB, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindMSB, TestUPPER, 1 << (BitsNumber<decltype(UPPER)> - 1), UPPER);
SIMPLE_TEST(FindMSB, TestSample1, 0b100, 0b101);
SIMPLE_TEST(FindMSB, TestSample2, 256, 273);
SIMPLE_TEST(FindMSB, TestSample3, 8, 10);


THE_BENCHMARK(FindMSB_Float, 4);

SIMPLE_TEST(FindMSB_Float, TestLOWER, 1, LOWER);
SIMPLE_TEST(FindMSB_Float, TestUPPER, 1 << (BitsNumber<decltype(UPPER)> - 1), UPPER);
SIMPLE_TEST(FindMSB_Float, TestSample1, 0b100, 0b101);
SIMPLE_TEST(FindMSB_Float, TestSample2, 256, 273);

MUTUAL_RANDOM_TEST(FindMSB, FindMSB_Float, LOWER, UPPER);
