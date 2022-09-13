#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Bag of Tokens
 *
 * @reference   https://leetcode.com/problems/bag-of-tokens/
 *
 * You have an initial power of power, an initial score of 0, and a bag of tokens where tokens[i] is the
 * value of the ith token (0-indexed).
 * Your goal is to maximize your total score by potentially playing each token in one of two ways:
 *  If your current power is at least tokens[i], you may play the ith token face up, losing tokens[i]
 *  power and gaining 1 score.
 * If your current score is at least 1, you may play the ith token face down, gaining tokens[i] power
 *  and losing 1 score.
 * Each token may be played at most once and in any order. You do not have to play all the tokens.
 * Return the largest possible score you can achieve after playing any number of tokens.
 */
auto BagOfTokens(ArrayType tokens, int power) {
    std::sort(tokens.begin(), tokens.end());

    int left = 0;
    int right = tokens.size() - 1;
    int score = 0;
    int result = 0;
    while (left <= right) {
        if (power >= tokens[left]) {
            power -= tokens[left++];
            result = std::max(result, ++score);
        } else if (score > 0) {
            --score;
            power += tokens[right--];
        } else {
            break;
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {100};
const ArrayType SAMPLE2 = {100, 200};
const ArrayType SAMPLE3 = {100, 200, 300, 400};


THE_BENCHMARK(BagOfTokens, SAMPLE1, 50);

SIMPLE_TEST(BagOfTokens, TestSAMPLE1, 0, SAMPLE1, 50);
SIMPLE_TEST(BagOfTokens, TestSAMPLE2, 1, SAMPLE2, 150);
SIMPLE_TEST(BagOfTokens, TestSAMPLE3, 2, SAMPLE3, 200);
