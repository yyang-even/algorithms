#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Valid Word Square
 *
 * @reference   https://github.com/grandyang/leetcode/issues/422
 *
 * Given a sequence of words, check whether it forms a valid word square. A sequence of
 * words forms a valid word square if the kth row and column read the exact same string,
 * where 0 ≤ k < max(numRows, numColumns).
 */
auto ValidWordSquare(const ArrayType &words) {
    if (words.empty()) {
        return true;
    }

    for (std::size_t i = 0; i < words.size(); ++i) {
        for (std::size_t j = 0; j < words[i].size(); ++j) {
            if (j >= words.size() or words[j].size() <= i or words[i][j] != words[j][i]) {
                return false;
            }
        }
    }

    return true;
}

}//namespace


const ArrayType SAMPLE1 = {
    "abcd",
    "bnrt",
    "crmy",
    "dtye"
};

const ArrayType SAMPLE2 = {
    "abcd",
    "bnrt",
    "crm",
    "dt"
};

const ArrayType SAMPLE3 = {
    "ball",
    "area",
    "read",
    "lady"
};


THE_BENCHMARK(ValidWordSquare, SAMPLE1);

SIMPLE_TEST(ValidWordSquare, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(ValidWordSquare, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(ValidWordSquare, TestSAMPLE3, false, SAMPLE3);
