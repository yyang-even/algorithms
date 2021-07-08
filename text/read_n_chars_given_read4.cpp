#include "common_header.h"


namespace {

using ArrayType = std::vector<std::size_t>;
using OutputType = std::vector<std::string>;

/** Read N Characters Given Read4
 *
 * @reference   https://tenderleo.gitbooks.io/leetcode-solutions-/content/GoogleEasy/157.html
 *
 * The API: int read4(char *buf) reads 4 characters at a time from a file. The return
 * value is the actual number of characters read. For example, it returns 3 if there is
 * only 3 characters left in the file. By using the read4 API, implement the function
 * int read(char *buf, int n) that reads n characters from the file. Note: The read
 * function will only be called once for each test case.
 */
int Read4(const std::string_view text, std::size_t &begin, char *buffer) {
    const auto end = std::min(text.size(), begin + 4);
    const auto size = end - begin;
    while (begin < end) {
        *(buffer++) = text[begin++];
    }

    return size;
}

auto ReadN(char *buffer, const std::size_t n, const std::function<int(char *)> read4) {
    std::size_t i = 0;

    while (i < n) {
        const auto size = read4(buffer);
        i += size;

        if (size < 4) {
            break;
        }

        buffer += size;
    }

    return std::min(i, n);
}

auto ReadN(const std::string_view text, const std::size_t n) {
    std::string buffer(n + 4, 0);

    std::size_t begin = 0;
    const auto size = ReadN(buffer.data(), n, [text, &begin](char *buffer) {
        return Read4(text, begin, buffer);
    });
    buffer.resize(size);

    return buffer;
}


/**
 * @reference   Read N Characters Given Read4 II - Call multiple times
 *              https://www.lintcode.com/problem/660/
 *
 * The API: int read4(char *buf) reads 4 characters at a time from a file. The return
 * value is the actual number of characters read. For example, it returns 3 if there is
 * only 3 characters left in the file. By using the read4 API, implement the function
 * int read(char *buf, int n) that reads n characters from the file. The read function
 * may be called multiple times.
 */
auto ReadN_Multi(char *buffer, const std::size_t n,
                 const std::function<int(char *)> read4, std::string &prev_buffer) {
    std::size_t i = 0;

    for (; i < n and i < prev_buffer.size(); ++i) {
        *(buffer++) = prev_buffer[i];
    }
    prev_buffer.erase(0, i);
    if (i >= n) {
        return n;
    }

    while (i < n) {
        const auto size = read4(buffer);
        i += size;
        buffer += size;

        if (size < 4) {
            break;
        }
    }

    if (i > n) {
        buffer -= (i - n);
        for (; i > n; --i) {
            prev_buffer.push_back(*(buffer++));
        }
    }

    return i;
}

auto ReadN_Multi(const std::string_view text, const ArrayType queries) {
    OutputType results;

    std::size_t begin = 0;
    const auto read4 = [text, &begin](char *buffer) {
        return Read4(text, begin, buffer);
    };
    std::string prev_buffer;

    for (const auto a_query : queries) {
        results.emplace_back(a_query + 4, 0);
        auto &buffer = results.back();
        const auto size = ReadN_Multi(buffer.data(), a_query, read4, prev_buffer);
        buffer.resize(size);
    }

    return results;
}

}//namespace


THE_BENCHMARK(ReadN, "adc", 4);

SIMPLE_TEST(ReadN, TestSAMPLE1, "abc", "abc", 4);
SIMPLE_TEST(ReadN, TestSAMPLE2, "a", "abc", 1);
SIMPLE_TEST(ReadN, TestSAMPLE3, "abc", "abc", 3);
SIMPLE_TEST(ReadN, TestSAMPLE4, "abc", "abcde", 3);
SIMPLE_TEST(ReadN, TestSAMPLE5, "abcd", "abcde", 4);
SIMPLE_TEST(ReadN, TestSAMPLE6, "abcde", "abcde", 5);
SIMPLE_TEST(ReadN, TestSAMPLE7, "abcdefgh", "abcdefgh", 8);


const ArrayType SAMPLE1 = {6, 5, 4, 3, 2, 1, 10};
const OutputType EXPECTED1 = {"filete", "stbuf", "fer", "", "", "", ""};

const ArrayType SAMPLE2 = {1, 5};
const OutputType EXPECTED2 = {"a", "bcdef"};

const ArrayType SAMPLE3 = {1, 1, 1, 10};
const OutputType EXPECTED3 = {"a", "b", "c", "def"};


THE_BENCHMARK(ReadN_Multi, "filetestbuffer", SAMPLE1);

SIMPLE_TEST(ReadN_Multi, TestSAMPLE1, EXPECTED1, "filetestbuffer", SAMPLE1);
SIMPLE_TEST(ReadN_Multi, TestSAMPLE2, EXPECTED2, "abcdef", SAMPLE2);
SIMPLE_TEST(ReadN_Multi, TestSAMPLE3, EXPECTED3, "abcdef", SAMPLE3);
