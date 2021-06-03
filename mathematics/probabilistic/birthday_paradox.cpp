#include "common_header.h"


namespace {

/** Birthday Paradox
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 5.4.
 * @reference   https://www.geeksforgeeks.org/birthday-paradox/
 *
 * How many people must be there in a room to make the probability p% that two people in
 * the room have same birthday?
 */
constexpr inline unsigned BirthdayParadox(const double probability) {
    return std::ceil(std::sqrt(2 * 365 * std::log(1 / (1 - probability))));
}

}//namespace


THE_BENCHMARK(BirthdayParadox, 0.70);

SIMPLE_TEST(BirthdayParadox, TestSAMPLE, 30, 0.70);
