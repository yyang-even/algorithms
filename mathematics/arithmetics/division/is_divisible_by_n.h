#pragma once


/** Check divisibility in a binary stream
 *
 * @reference   https://www.geeksforgeeks.org/check-divisibility-binary-stream/
 * @reference   DFA based division
 *              https://www.geeksforgeeks.org/dfa-based-division/
 *
 * Stream of binary number is coming, the task is to tell the number formed so far is
 * divisible by a given number n. At any given time, you will get 0 or 1 and tell
 * whether the number formed with these bits is divisible by n or not.
 */
static inline auto
isDivisibleByN_DFA(const std::vector<unsigned> &stream, const unsigned N) {
    std::vector<bool> outputs;
    unsigned remainder = 0;

    for (const auto i : stream) {
        switch (i) {
            case 0:
                remainder = remainder * 2 % N;
                break;
            case 1:
                remainder = (remainder * 2 + 1) % N;
                break;
            default:
                assert(false);
        }

        outputs.push_back(not remainder);
    }

    return outputs;
}
