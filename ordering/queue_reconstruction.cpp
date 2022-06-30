#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Queue Reconstruction by Height
 *
 * @reference   https://leetcode.com/problems/queue-reconstruction-by-height/
 *
 * You are given an array of people, people, which are the attributes of some people in a queue
 * (not necessarily in order). Each people[i] = [hi, ki] represents the ith person of height hi
 * with exactly ki other people in front who have a height greater than or equal to hi.
 * Reconstruct and return the queue that is represented by the input array people. The returned
 * queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of
 * the jth person in the queue (queue[0] is the person at the front of the queue).
 */
auto QueueReconstruction_TallFirst(ArrayType people) {
    std::sort(people.begin(), people.end(), [](const auto &one, const auto &another) {
        if (one.first == another.first) {
            return one.second < another.second;
        }
        return one.first > another.first;
    });

    ArrayType result;
    for (const auto [h, k] : people) {
        result.insert(result.begin() + k, {h, k});
    }

    return result;
}


auto QueueReconstruction_ShortFirst(ArrayType people) {
    std::sort(people.begin(), people.end(), [](const auto &one, const auto &another) {
        if (one.first == another.first) {
            return one.second > another.second;
        }
        return one.first < another.first;
    });

    ArrayType result(people.size(), {-1, -1});
    for (const auto [h, k] : people) {
        std::size_t j = 0;
        for (int count = 0; j < result.size(); ++j) {
            if (result[j].first == -1) {
                if (count++ == k) {
                    break;
                }
            }
        }

        result[j] = {h, k};
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
const ArrayType EXPECTED1 = {{5, 0}, {7, 0}, {5, 2}, {6, 1}, {4, 4}, {7, 1}};

const ArrayType SAMPLE2 = {{6, 0}, {5, 0}, {4, 0}, {3, 2}, {2, 2}, {1, 4}};
const ArrayType EXPECTED2 = {{4, 0}, {5, 0}, {2, 2}, {3, 2}, {1, 4}, {6, 0}};


THE_BENCHMARK(QueueReconstruction_TallFirst, SAMPLE1);

SIMPLE_TEST(QueueReconstruction_TallFirst, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(QueueReconstruction_TallFirst, TestSAMPLE2, EXPECTED2, SAMPLE2);


THE_BENCHMARK(QueueReconstruction_ShortFirst, SAMPLE1);

SIMPLE_TEST(QueueReconstruction_ShortFirst, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(QueueReconstruction_ShortFirst, TestSAMPLE2, EXPECTED2, SAMPLE2);
