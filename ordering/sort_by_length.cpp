#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Sort an array of strings according to string lengths
 *
 * @reference   https://www.geeksforgeeks.org/sort-array-strings-according-string-lengths/
 */
auto SortByLengths(ArrayType strings) {
    std::sort(strings.begin(), strings.end(), [](const auto & lhs, const auto & rhs) {
        return lhs.length() < rhs.length();
    });

    return strings;
}


/**
 * @reference   Sort an array of strings according to string lengths using Map
 *              https://www.geeksforgeeks.org/sort-an-array-of-strings-according-to-string-lengths-using-map/
 */
auto SortByLengths_Bucket(ArrayType strings) {
    std::map<std::string::size_type, ArrayType> buckets;
    for (auto &str : strings) {
        buckets[str.length()].emplace_back(std::move(str));
    }

    auto iter = strings.begin();
    for (auto &key_value_pair : buckets) {
        iter = std::copy(std::make_move_iterator(key_value_pair.second.cbegin()),
                         std::make_move_iterator(key_value_pair.second.cend()), iter);
    }

    return strings;
}

}//namespace


const ArrayType SAMPLE1 = {"GeeksforGeeks", "I", "from", "am"};
const ArrayType EXPECTED1 = {"I", "am", "from", "GeeksforGeeks"};
const ArrayType SAMPLE2 = {"You", "are", "beautiful", "looking"};
const ArrayType EXPECTED2 = {"You", "are", "looking", "beautiful"};


SIMPLE_BENCHMARK(SortByLengths, SAMPLE1);

SIMPLE_TEST(SortByLengths, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByLengths, TestSAMPLE2, EXPECTED2, SAMPLE2);


SIMPLE_BENCHMARK(SortByLengths_Bucket, SAMPLE1);

SIMPLE_TEST(SortByLengths_Bucket, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByLengths_Bucket, TestSAMPLE2, EXPECTED2, SAMPLE2);
