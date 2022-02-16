#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Faulty Sensor
 *
 * @reference   https://leetcode.ca/2021-06-17-1826-Faulty-Sensor/
 *
 * An experiment is being conducted in a lab. To ensure accuracy, there are two sensors
 * collecting data simultaneously. You are given 2 arrays sensor1 and sensor2, where
 * sensor1[i] and sensor2[i] are the i-th data points collected by the two sensors.
 * However, this type of sensor has a chance of being defective, which causes exactly one
 * data point to be dropped. After the data is dropped, all the data points to the right
 * of the dropped data are shifted one place to the left, and the last data point is
 * replaced with some random value. It is guaranteed that this random value will not be
 * equal to the dropped value.
 *  For example, if the correct data is [1,2,3,4,5] and 3 is dropped, the sensor could
 *      return [1,2,4,5,7] (the last position can be *any value, not just 7).
 * We know that there is a defect in at most one of the sensors. Return the sensor number
 * (1 or 2) with the defect. If there is no defect in either sensor or if it is impossible
 * to determine the defective sensor, return -1.
 */
auto FaultySensor(const ArrayType &sensor1, const ArrayType &sensor2) {
    std::size_t i = 0;
    while (i < sensor1.size() and sensor1[i] == sensor2[i]) {
        ++i;
    }

    if (i >= sensor1.size() - 1) {
        return -1;
    }

    while (i < sensor1.size() - 1 and sensor1[i] == sensor2[i + 1]) {
        ++i;
    }

    return i == sensor1.size() - 1 ? 1 : 2;
}

}//namespace


const ArrayType SAMPLE1L = {2, 3, 4, 5};
const ArrayType SAMPLE1R = {2, 1, 3, 4};

const ArrayType SAMPLE2L = {2, 2, 2, 2, 2};
const ArrayType SAMPLE2R = {2, 2, 2, 2, 5};

const ArrayType SAMPLE3L = {2, 3, 2, 2, 3, 2};
const ArrayType SAMPLE3R = {2, 3, 2, 3, 2, 7};


THE_BENCHMARK(FaultySensor, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(FaultySensor, TestSAMPLE1, 1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(FaultySensor, TestSAMPLE2, -1, SAMPLE2L, SAMPLE2R);
SIMPLE_TEST(FaultySensor, TestSAMPLE3, 2, SAMPLE3L, SAMPLE3R);
