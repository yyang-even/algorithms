#include "common_header.h"

#include "mathematics/numbers/binary/count_total_bits.h"

namespace {

using ArrayType = std::vector<int>;

/** Binary Search
 *
 * @reference   https://www.geeksforgeeks.org/binary-search/
 * @reference   C Program for Binary Search (Recursive and Iterative)
 *              https://www.geeksforgeeks.org/c-program-for-binary-search-recursive-and-iterative/
 * @reference   Linear Search vs Binary Search
 *              https://www.geeksforgeeks.org/linear-search-vs-binary-search/
 * @reference   Binary Search a String
 *              https://www.geeksforgeeks.org/binary-search-a-string/
 * @reference   Complexity Analysis of Binary Search
 *              https://www.geeksforgeeks.org/complexity-analysis-of-binary-search/
 */
auto BinarySearch_Recursive(const ArrayType::const_iterator cbegin,
                            const ArrayType::size_type length, const ArrayType::const_iterator cend,
                            const ArrayType::value_type x) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x) {
            return mid;
        }
        if (*mid > x) {
            return BinarySearch_Recursive(cbegin, half, cend, x);
        }
        return BinarySearch_Recursive(std::next(mid), length - half - 1, cend, x);
    }

    return cend;
}

auto BinarySearch_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_Recursive(elements.cbegin(), elements.size(), elements.cend(), x);
}


inline auto BinarySearch_STL(const ArrayType &elements, const ArrayType::value_type x) {
    return std::lower_bound(elements.cbegin(), elements.cend(), x);
}


auto BinarySearch_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x) {
            return mid;
        }
        if (*mid > x) {
            length = half;
        } else {
            cbegin = std::next(mid);
            length -= (half + 1);
        }
    }

    return elements.cend();
}


/**
 * @reference   Meta Binary Search | One-Sided Binary Search
 *              https://www.geeksforgeeks.org/meta-binary-search-one-sided-binary-search/
 * @reference   What is meta binary search?
 *              https://www.quora.com/What-is-meta-binary-search
 */
auto BinarySearch_Meta(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    assert(not elements.empty());

    if (x == elements.front()) {
        return elements.cbegin();
    }

    const auto max_index_bits = CountTotalBits_Log(elements.size() - 1);
    ArrayType::size_type i = 0;
    for (int shift = max_index_bits - 1; shift >= 0; --shift) {
        const auto index_candidate = i + (1 << shift);

        if (index_candidate >= elements.size()) {
            continue;
        }
        if (elements[index_candidate] == x) {
            return elements.cbegin() + index_candidate;
        }
        if (elements[index_candidate] < x) {
            i = index_candidate;
        }
    }

    return elements.cend();
}


/**
 * @reference   Uniform Binary Search
 *              https://www.geeksforgeeks.org/uniform-binary-search/
 */
auto CreateDeltaTable(const ArrayType::size_type size) {
    std::cout << "Creating delta table of size " << size << std::endl;

    std::vector<ArrayType::size_type> delta_table(CountTotalBits_Log(size) + 1);

    unsigned power = 1;
    int i = 0;
    do {
        const auto half = power;
        power <<= 1;
        delta_table[i] = (size + half) / power;
    } while (delta_table[i++] != 0);

    return delta_table;
}

template <unsigned size>
const auto &GetDeltaTable() {
    static const auto delta_table = CreateDeltaTable(size);
    return delta_table;
}

template <unsigned size>
auto BinarySearch_Uniform(const ArrayType &elements, const ArrayType::value_type x) {
    assert(size == elements.size());
    assert(not elements.empty());
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    const auto &delta_table = GetDeltaTable<size>();
    auto delta = 0;
    for (auto i = delta_table[delta] - 1; delta_table[delta];) {
        if (x == elements[i]) {
            return elements.cbegin() + i;
        }
        if (x < elements[i]) {
            i -= delta_table[++delta];
        } else {
            i += delta_table[++delta];
        }
    }

    return elements.cend();
}

const auto BinarySearch_Uniform5 = BinarySearch_Uniform<5>;

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {2, 3, 4, 10, 40};


SIMPLE_BENCHMARK(BinarySearch_Recursive, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Recursive, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL, BinarySearch_Recursive, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Recursive, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(BinarySearch_Iterative, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Iterative, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL, BinarySearch_Iterative, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(BinarySearch_Meta, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Meta, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL, BinarySearch_Meta, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Meta, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Meta, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(BinarySearch_Uniform5, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Uniform5, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL, BinarySearch_Uniform5, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Uniform5, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Uniform5, TestNotExist, VALUES2.cend(), VALUES2, 999);
