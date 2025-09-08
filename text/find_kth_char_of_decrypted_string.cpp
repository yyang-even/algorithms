#include "common_header.h"

#include "number_convertion.h"


namespace {

/**
 * @reference   Find k'th character of decrypted string
 *              https://www.geeksforgeeks.org/find-kth-character-of-decrypted-string/
 *
 * Given an encoded string where repetitions of substrings are represented as substring followed by
 * count of substrings. For example, if encrypted string is "ab2cd2" and k=4, so output will be 'b'
 * because decrypted string is "ababcdcd" and 4th character is 'b'.
 * Note: Frequency of encrypted substring can be of more than one digit. For example, in "ab12c3", ab is
 * repeated 12 times. No leading 0 is present in frequency of substring.
 */
auto FindKthCharOfDecryptedString(const std::string_view encoded, const std::size_t K) {
    assert(K > 0);

    std::string decrypted;

    for (std::size_t i = 0; decrypted.size() < K and i < encoded.size();) {
        const auto frequency_start = encoded.find_first_of(DIGIT_CHARS, i);
        const auto substring = encoded.substr(i, frequency_start - i);

        i = encoded.find_first_of(LOWERCASE_CHARS, frequency_start);
        if (i == std::string_view::npos) {
            i = encoded.size();
        }
        const auto frequency =
            from_string_view(encoded.substr(frequency_start, i - frequency_start));
        for (auto j = 0; j < frequency and decrypted.size() < K; ++j) {
            decrypted.append(substring);
        }
    }

    return decrypted[K - 1];
}


/**
 * @reference   Design Compressed String Iterator
 *              http://lixinchengdu.github.io/algorithmbook/leetcode/design-compressed-string-iterator.html
 * @reference   https://www.cnblogs.com/grandyang/p/7026999.html
 *
 * Design and implement a data structure for a compressed string iterator. It should support the
 * following operations: next and hasNext. The given compressed string will be in the form of each
 * letter followed by a positive integer representing the number of this letter existing in the original
 * uncompressed string.
 *  next() - if the original string still has uncompressed characters, return the next letter; Otherwise
 *      return a white space.
 *  hasNext() - Judge whether there is any letter needs to be uncompressed.
 * Note: Please remember to RESET your class variables declared in StringIterator, as static/class
 * variables are persisted across multiple test cases. Please see here for more details.
 *
 * @tags    #string-stream
 */
class CompressedStringIterator {
    std::string_view m_compressed;
    std::size_t i = 0;
    int count = 0;
    char c = 0;

public:
    constexpr explicit CompressedStringIterator(const std::string_view compressed) :
        m_compressed(compressed) {
    }

    auto hasNext() {
        if (count > 0) {
            return true;
        }

        if (i >= m_compressed.size()) {
            return false;
        }

        c = m_compressed[i++];
        while (i < m_compressed.size() and std::isdigit(m_compressed[i])) {
            count = count * 10 + m_compressed[i++] - '0';
        }

        return true;
    }

    auto next() {
        if (hasNext()) {
            --count;
            return c;
        }

        return ' ';
    }
};


class CompressedStringIterator_SS {
    std::istringstream ss;
    int count = 0;
    char c = 0;

public:
    explicit CompressedStringIterator_SS(const std::string &compressed) {
        ss = std::istringstream {compressed};
    }

    auto hasNext() {
        if (count == 0) {
            ss >> c >> count;
        }

        return count > 0;
    }

    auto next() {
        if (hasNext()) {
            --count;
            return c;
        }

        return ' ';
    }
};

template<typename Iterator>
constexpr auto testCompressedStringIterator(const std::string &compressed) {
    Iterator iter {compressed};
    std::string result;
    while (iter.hasNext()) {
        result.push_back(iter.next());
    }

    return result;
}

constexpr auto testCompressedStringIterator_Plain =
    testCompressedStringIterator<CompressedStringIterator>;
constexpr auto testCompressedStringIterator_SS =
    testCompressedStringIterator<CompressedStringIterator_SS>;

} //namespace


THE_BENCHMARK(FindKthCharOfDecryptedString, "ab4c12ed3", 21);

SIMPLE_TEST(FindKthCharOfDecryptedString, TestSAMPLE1, 'c', "a2b2c3", 5);
SIMPLE_TEST(FindKthCharOfDecryptedString, TestSAMPLE2, 'c', "ab4c2ed3", 9);
SIMPLE_TEST(FindKthCharOfDecryptedString, TestSAMPLE3, 'e', "ab4c12ed3", 21);


SIMPLE_TEST(testCompressedStringIterator_Plain, TestSAMPLE1, "aabbccc", "a2b2c3");
SIMPLE_TEST(testCompressedStringIterator_Plain, TestSAMPLE2, "aabbbbbbbbbb", "a2b10");


SIMPLE_TEST(testCompressedStringIterator_SS, TestSAMPLE1, "aabbccc", "a2b2c3");
SIMPLE_TEST(testCompressedStringIterator_SS, TestSAMPLE2, "aabbbbbbbbbb", "a2b10");
