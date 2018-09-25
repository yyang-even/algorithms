#include "common_header.h"

/** Find k’th character of decrypted string
 *
 * @reference   https://www.geeksforgeeks.org/find-kth-character-of-decrypted-string/
 *
 * Given an encoded string where repetitions of substrings are represented as substring
 * followed by count of substrings. For example, if encrypted string is “ab2cd2” and k=4,
 * so output will be ‘b’ because decrypted string is “ababcdcd” and 4th character is ‘b’.
 * Note: Frequency of encrypted substring can be of more than one digit. For example,
 * in “ab12c3”, ab is repeated 12 times. No leading 0 is present in frequency of substring.
 */
auto FindKthCharOfDecryptedString(const std::string &encoded, const std::string::size_type K) {
    std::string decrypted;

    for (std::string::size_type i = 0ul; decrypted.size() < K and i < encoded.size();) {
        const auto frequency_start = encoded.find_first_of(DIGIT_CHARS, i);
        const auto substring = encoded.substr(i, frequency_start - i);

        i = encoded.find_first_of(LOWERCASE_CHARS, frequency_start);
        if (i == std::string::npos) {
            i = encoded.size();
        }
        const auto frequency = std::stoi(encoded.substr(frequency_start, i - frequency_start));
        for (auto j = 0; j < frequency; ++j) {
            decrypted.append(substring);
        }
    }

    return decrypted[K - 1ul];
}


SIMPLE_BENCHMARK(FindKthCharOfDecryptedString, std::string("ab4c12ed3"), 21ul);

SIMPLE_TEST(FindKthCharOfDecryptedString, TestSAMPLE1, 'c', std::string("a2b2c3"), 5ul);
SIMPLE_TEST(FindKthCharOfDecryptedString, TestSAMPLE2, 'c', std::string("ab4c2ed3"), 9ul);
SIMPLE_TEST(FindKthCharOfDecryptedString, TestSAMPLE3, 'e', std::string("ab4c12ed3"), 21ul);
