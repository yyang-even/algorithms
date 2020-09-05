#include "common_header.h"

#include "is_divisible_by_n.h"


namespace {

auto stateTransitionTable(const unsigned N) {
    std::vector<std::vector<unsigned>> table(N, std::vector<unsigned>(2, 0));

    for (unsigned state = 0; state < N; ++state) {
        const auto transition0 = state << 1;
        table[state][0] = (transition0 < N) ? transition0 : transition0 - N;
        const auto transition1 = transition0 + 1;
        table[state][1] = (transition1 < N) ? transition1 : transition1 - N;
    }

    return table;
}

auto isDivisibleByN_DFALookupTable(const std::vector<unsigned> &stream, const unsigned N) {
    const auto state_transition_table = stateTransitionTable(N);
    std::vector<bool> outputs;
    unsigned remainder = 0;

    for (const auto i : stream) {
        remainder = state_transition_table[remainder][i];
        outputs.push_back(not remainder);
    }

    return outputs;
}

}//namespace


const std::vector<unsigned> SAMPLE1 = {1, 0, 1, 0, 1};
const std::vector<bool> EXPECTED1 = {false, false, false, false, true};


SIMPLE_BENCHMARK(isDivisibleByN_DFA, Sample1, SAMPLE1, 3);

SIMPLE_TEST(isDivisibleByN_DFA, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);


SIMPLE_BENCHMARK(isDivisibleByN_DFALookupTable, Sample1, SAMPLE1, 3);

SIMPLE_TEST(isDivisibleByN_DFALookupTable, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);
