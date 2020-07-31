#include "common_header.h"


namespace {

/** Program to check if all characters have even frequency
 *
 * @reference   https://www.geeksforgeeks.org/program-to-check-if-all-characters-have-even-frequency/
 */
auto AllHaveEvenFrequency(const std::string &characters) {
    return not std::accumulate(characters.cbegin(), characters.cend(), 0,
                               std::bit_xor<std::string::value_type> {});
}

}//namespace


SIMPLE_BENCHMARK(AllHaveEvenFrequency, "abaccaba");

SIMPLE_TEST(AllHaveEvenFrequency, TestSAMPLE1, true, "abaccaba");
SIMPLE_TEST(AllHaveEvenFrequency, TestSAMPLE2, false, "hthth");
