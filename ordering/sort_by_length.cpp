#include "common_header.h"

#include "bucket_sort.h"
#include "counting_sort.h"


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


auto SortByLengths_Stable(ArrayType strings) {
    std::stable_sort(strings.begin(), strings.end(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.length() < rhs.length();
    });

    return strings;
}


/**
 * @reference   Sort an array of strings according to string lengths using Map
 *              https://www.geeksforgeeks.org/sort-an-array-of-strings-according-to-string-lengths-using-map/
 */
auto SortByLengths_Stable_Bucket(const ArrayType &strings) {
    return BucketSort_STL(strings, [](const auto & str) {
        return str.length();
    }, Void);
}


auto SortByLengths_Stable_CountingSort(const ArrayType &strings) {
    return CountingSort_STL(strings, [](const auto & str) {
        return str.length();
    });
}

}//namespace


const ArrayType SAMPLE1 = {"GeeksforGeeks", "I", "from", "am"};
const ArrayType EXPECTED1 = {"I", "am", "from", "GeeksforGeeks"};
const ArrayType SAMPLE2 = {"You", "are", "beautiful", "looking"};
const ArrayType EXPECTED2 = {"You", "are", "looking", "beautiful"};


SIMPLE_BENCHMARK(SortByLengths, Sample1, SAMPLE1);

SIMPLE_TEST(SortByLengths, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByLengths, TestSAMPLE2, EXPECTED2, SAMPLE2);


SIMPLE_BENCHMARK(SortByLengths_Stable, Sample1, SAMPLE1);

SIMPLE_TEST(SortByLengths_Stable, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByLengths_Stable, TestSAMPLE2, EXPECTED2, SAMPLE2);


SIMPLE_BENCHMARK(SortByLengths_Stable_Bucket, Sample1, SAMPLE1);

SIMPLE_TEST(SortByLengths_Stable_Bucket, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByLengths_Stable_Bucket, TestSAMPLE2, EXPECTED2, SAMPLE2);


SIMPLE_BENCHMARK(SortByLengths_Stable_CountingSort, Sample1, SAMPLE1);

SIMPLE_TEST(SortByLengths_Stable_CountingSort, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByLengths_Stable_CountingSort, TestSAMPLE2, EXPECTED2, SAMPLE2);
