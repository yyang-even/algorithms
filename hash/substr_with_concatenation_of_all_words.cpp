#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Substring with Concatenation of All Words
 *
 * @reference   https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 *
 * You are given a string s and an array of strings words of the same length. Return all starting
 * indices of substring(s) in s that is a concatenation of each word in words exactly once, in any
 * order, and without any intervening characters.
 * You can return the answer in any order.
 */
auto SubstrWithConcatenationOfAllWords(const std::string_view s, const ArrayType &words) {
    std::unordered_map<std::string_view, int> counts;
    for (const auto &w : words) {
        ++counts[w];
    }

    const auto length = words.front().size();
    const auto total = length * words.size();
    std::vector<int> result;
    for (std::size_t i = 0; i + total <= s.size(); ++i) {
        std::unordered_map<std::string_view, int> temp;
        int required = counts.size();

        for (auto j = i; j < i + total; j += length) {
            const auto sub = s.substr(j, length);
            const auto iter_temp = temp.find(sub);
            const auto iter = counts.find(sub);
            if (iter == counts.cend() or
                (iter_temp != temp.cend() and iter_temp->second >= iter->second)) {
                break;
            }

            if (++temp[sub] == iter->second) {
                --required;
            }
        }

        if (required == 0) {
            result.push_back(i);
        }
    }

    return result;
}


auto slidingWindow(std::size_t left,
                   const std::string_view s,
                   const ArrayType &words,
                   const std::unordered_map<std::string_view, int> &counts,
                   std::vector<int> &result) {
    std::unordered_map<std::string_view, int> found;
    const auto length = words.front().size();
    int required = words.size();
    const auto total = length * words.size();
    bool excess = false;

    for (auto right = left; right <= s.size() - length; right += length) {
        const auto sub = s.substr(right, length);
        const auto iter = counts.find(sub);
        if (iter == counts.cend()) {
            found.clear();
            required = words.size();
            excess = false;
            left = right + length;
        } else {
            while (right - left == total or excess) {
                const auto left_sub = s.substr(left, length);
                left += length;
                if (found[left_sub]-- > counts.at(left_sub)) {
                    excess = false;
                } else {
                    ++required;
                }
            }

            if (++(found[sub]) <= iter->second) {
                --required;
            } else {
                excess = true;
            }

            if (required == 0 and not excess) {
                result.push_back(left);
            }
        }
    }
}

auto SubstrWithConcatenationOfAllWords_SlidingWindow(const std::string_view s,
                                                     const ArrayType &words) {
    std::unordered_map<std::string_view, int> counts;
    for (const auto &w : words) {
        ++counts[w];
    }

    std::vector<int> result;
    for (std::size_t i = 0; i < words.front().size(); ++i) {
        slidingWindow(i, s, words, counts, result);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {"foo", "bar"};
const std::vector EXPECTED1 = {0, 9};

const ArrayType SAMPLE2 = {"word", "good", "best", "word"};
const std::vector<int> EXPECTED2 = {};

const ArrayType SAMPLE3 = {"bar", "foo", "the"};
const std::vector EXPECTED3 = {6, 9, 12};


THE_BENCHMARK(SubstrWithConcatenationOfAllWords, "barfoothefoobarman", SAMPLE1);

SIMPLE_TEST(
    SubstrWithConcatenationOfAllWords, TestSAMPLE1, EXPECTED1, "barfoothefoobarman", SAMPLE1);
SIMPLE_TEST(SubstrWithConcatenationOfAllWords,
            TestSAMPLE2,
            EXPECTED2,
            "wordgoodgoodgoodbestword",
            SAMPLE2);
SIMPLE_TEST(SubstrWithConcatenationOfAllWords,
            TestSAMPLE3,
            EXPECTED3,
            "barfoofoobarthefoobarman",
            SAMPLE3);


THE_BENCHMARK(SubstrWithConcatenationOfAllWords_SlidingWindow, "barfoothefoobarman", SAMPLE1);

SIMPLE_TEST(SubstrWithConcatenationOfAllWords_SlidingWindow,
            TestSAMPLE1,
            EXPECTED1,
            "barfoothefoobarman",
            SAMPLE1);
SIMPLE_TEST(SubstrWithConcatenationOfAllWords_SlidingWindow,
            TestSAMPLE2,
            EXPECTED2,
            "wordgoodgoodgoodbestword",
            SAMPLE2);
SIMPLE_TEST(SubstrWithConcatenationOfAllWords_SlidingWindow,
            TestSAMPLE3,
            EXPECTED3,
            "barfoofoobarthefoobarman",
            SAMPLE3);
