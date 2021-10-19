#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Distance Between Bus Stops
 *
 * @reference   https://leetcode.com/problems/distance-between-bus-stops/
 *
 * A bus has n stops numbered from 0 to n - 1 that form a circle. We know the distance
 * between all pairs of neighboring stops where distance[i] is the distance between the
 * stops number i and (i + 1) % n. The bus goes along both directions i.e. clockwise and
 * counterclockwise. Return the shortest distance between the given start and destination
 * stops.
 */
int DistanceBetweenStops(const ArrayType &distances,
                         const std::size_t start, const std::size_t destination) {
    if (start > destination) {
        return DistanceBetweenStops(distances, destination, start);
    }

    int clockwise_distance = 0;
    int counterclockwise = 0;

    for (std::size_t i = 0; i < distances.size(); ++i) {
        if (i >= start and i < destination) {
            clockwise_distance += distances[i];
        } else {
            counterclockwise += distances[i];
        }
    }

    return std::min(clockwise_distance, counterclockwise);
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4};


THE_BENCHMARK(DistanceBetweenStops, SAMPLE1, 0, 1);

SIMPLE_TEST(DistanceBetweenStops, TestSAMPLE1, 1, SAMPLE1, 0, 1);
SIMPLE_TEST(DistanceBetweenStops, TestSAMPLE2, 3, SAMPLE1, 0, 2);
SIMPLE_TEST(DistanceBetweenStops, TestSAMPLE3, 4, SAMPLE1, 0, 3);
