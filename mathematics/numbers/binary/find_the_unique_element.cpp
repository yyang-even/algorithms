#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Unique element in an array where all elements occur k times except one
 *
 * @reference   https://www.geeksforgeeks.org/find-unique-element-element-occurs-k-times-except-one/
 *
 * Given an array which contains all elements occurring k times, but one occurs only
 * once. Find that unique element.
 *
 * @reference   Find the element that appears once
 *              https://www.geeksforgeeks.org/find-the-element-that-appears-once/
 *
 * Given an array where every element occurs three times, except one element which occurs
 * only once. Find the element that occurs once. Expected time complexity is O(n) and O(1)
 * extra space.
 */
ArrayType::value_type FindTheUniqueElement_Hash(const ArrayType &elements,
                                                const ArrayType::size_type) {
    const auto counters = ToFrequencyHashTable(elements);

    for (const auto [key, count] : counters) {
        if (count == 1) {
            return key;
        }
    }
    return 0;
}


auto FindTheUniqueElement_Bits(const ArrayType &elements,
                               const ArrayType::size_type K) {
    static constexpr auto NUMBER_BITS = BitsNumber<ArrayType::value_type>;
    std::vector<ArrayType::value_type> counters(NUMBER_BITS, 0);

    for (size_t i = 0; i < NUMBER_BITS; ++i) {
        const auto mask = 1u << i;
        for (const auto elem : elements) {
            if (elem & mask) {
                ++counters[i];
            }
        }
    }

    ArrayType::value_type result = 0;
    for (size_t i = 0; i < NUMBER_BITS; ++i) {
        result += (counters[i] % K) * (1u << i);
    }

    return result;
}


auto FindTheUniqueElement3_Xor(const ArrayType &elements) {
    ArrayType::value_type ones = 0, twos = 0;
    ArrayType::value_type common_bit_mask{};

    for (const auto value : elements) {
        twos |= (ones & value);
        ones ^= value;
        common_bit_mask = ~(ones & twos);
        ones &= common_bit_mask;
        twos &= common_bit_mask;
    }

    return ones;
}

}//namespace


const ArrayType SAMPLE1 = {6, 2, 5, 2, 2, 6, 6};
const ArrayType SAMPLE2 = {2, 2, 2, 10, 2};
const ArrayType SAMPLE3 = {12, 1, 12, 3, 12, 1, 1, 2, 3, 3};
const ArrayType SAMPLE4 = {10, 20, 10, 30, 10, 30, 30};


THE_BENCHMARK(FindTheUniqueElement_Hash, SAMPLE1, 3);

SIMPLE_TEST(FindTheUniqueElement_Hash, TestSample1, 5, SAMPLE1, 3);
SIMPLE_TEST(FindTheUniqueElement_Hash, TestSample2, 10, SAMPLE2, 4);
SIMPLE_TEST(FindTheUniqueElement_Hash, TestSample3, 2, SAMPLE3, 3);
SIMPLE_TEST(FindTheUniqueElement_Hash, TestSample4, 20, SAMPLE4, 3);


THE_BENCHMARK(FindTheUniqueElement_Bits, SAMPLE1, 3);

SIMPLE_TEST(FindTheUniqueElement_Bits, TestSample1, 5, SAMPLE1, 3);
SIMPLE_TEST(FindTheUniqueElement_Bits, TestSample2, 10, SAMPLE2, 4);
SIMPLE_TEST(FindTheUniqueElement_Bits, TestSample3, 2, SAMPLE3, 3);
SIMPLE_TEST(FindTheUniqueElement_Bits, TestSample4, 20, SAMPLE4, 3);


THE_BENCHMARK(FindTheUniqueElement3_Xor, SAMPLE1);

SIMPLE_TEST(FindTheUniqueElement3_Xor, TestSample1, 5, SAMPLE1);
SIMPLE_TEST(FindTheUniqueElement3_Xor, TestSample3, 2, SAMPLE3);
SIMPLE_TEST(FindTheUniqueElement3_Xor, TestSample4, 20, SAMPLE4);
