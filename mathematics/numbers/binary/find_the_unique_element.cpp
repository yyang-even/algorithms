#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

using ArrayType = std::vector<unsigned>;

/** Unique element in an array where all elements occur k times except one
 *
 * @reference   https://www.geeksforgeeks.org/find-unique-element-element-occurs-k-times-except-one/
 *
 * Given an array which contains all elements occurring k times, but one occurs only once. Find that unique element.
 */
ArrayType::value_type FindTheUniqueElementHash(const ArrayType &elements,
        const ArrayType::size_type K) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> counters;

    for (const auto elem : elements) {
        ++counters[elem];
    }

    for (auto iter = counters.cbegin(); iter != counters.cend(); ++iter) {
        if (iter->second == 1u) {
            return iter->first;
        }
    }
    return 0u;
}

auto FindTheUniqueElementBits(const ArrayType &elements, const ArrayType::size_type K) {
    const auto NUMBER_BITS = Bits_Number<ArrayType::value_type>();
    std::vector<ArrayType::value_type> counters(NUMBER_BITS, 0u);

    for (size_t i = 0; i < NUMBER_BITS; ++i) {
        const auto mask = 1u << i;
        for (const auto elem : elements) {
            if (elem & mask) {
                ++counters[i];
            }
        }
    }

    ArrayType::value_type result = 0u;
    for (size_t i = 0; i < NUMBER_BITS; ++i) {
        result += (counters[i] % K) * (1u << i);
    }

    return result;
}


const ArrayType SAMPLE1 = {6, 2, 5, 2, 2, 6, 6};
const ArrayType SAMPLE2 = {2, 2, 2, 10, 2};


SIMPLE_BENCHMARK(FindTheUniqueElementHash, SAMPLE1, 3u);

SIMPLE_TEST(FindTheUniqueElementHash, TestSample1, 5u, SAMPLE1, 3u);
SIMPLE_TEST(FindTheUniqueElementHash, TestSample2, 10u, SAMPLE2, 4u);


SIMPLE_BENCHMARK(FindTheUniqueElementBits, SAMPLE1, 3u);

SIMPLE_TEST(FindTheUniqueElementBits, TestSample1, 5u, SAMPLE1, 3u);
SIMPLE_TEST(FindTheUniqueElementBits, TestSample2, 10u, SAMPLE2, 4u);
