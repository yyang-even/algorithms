#include "common_header.h"


namespace {

/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 7.7.
 *
 * Design an algorithm such that we have to find the kth element in the array such that
 * their only prime factors are 3,5 an 7.
 */
auto KthMagicNumber(const unsigned k) {
    std::queue<int> queue_threes;
    std::queue<int> queue_fives;
    std::queue<int> queue_sevens;
    int result = 1;
    queue_threes.push(result);
    for (unsigned i = 0; i < k; ++i) {
        const auto threes_front = queue_threes.empty() ? std::numeric_limits<int>::max() :
                                  queue_threes.front();
        const auto fives_front = queue_fives.empty() ? std::numeric_limits<int>::max() :
                                 queue_fives.front();
        const auto sevens_front = queue_sevens.empty() ? std::numeric_limits<int>::max() :
                                  queue_sevens.front();

        result = std::min(std::min(threes_front, fives_front), sevens_front);
        if (result == threes_front) {
            queue_threes.pop();
            queue_threes.push(3 * result);
            queue_fives.push(5 * result);
        } else if (result == fives_front) {
            queue_fives.pop();
            queue_fives.push(5 * result);
        } else if (result == sevens_front) {
            queue_sevens.pop();
        }
        queue_sevens.push(7 * result);
    }

    return result;
}

}//namespace


THE_BENCHMARK(KthMagicNumber, 25);

SIMPLE_TEST(KthMagicNumber, TestSAMPLE1, 1, 0);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE2, 1, 1);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE3, 25, 8);
SIMPLE_TEST(KthMagicNumber, TestSAMPLE4, 63, 13);
