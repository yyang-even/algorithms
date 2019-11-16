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
 * @reference   The Ubiquitous Binary Search | Set 1
 *              https://www.geeksforgeeks.org/the-ubiquitous-binary-search-set-1/
 * @reference   A Problem in Many Binary Search Implementations
 *              https://www.geeksforgeeks.org/problem-binary-search-implementations/
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


inline auto BinarySearch_STL_Lower(const ArrayType &elements, const ArrayType::value_type x) {
    return std::lower_bound(elements.cbegin(), elements.cend(), x);
}


inline auto BinarySearch_STL_Upper(const ArrayType &elements, const ArrayType::value_type x) {
    const auto iter = std::upper_bound(elements.cbegin(), elements.cend(), x);
    if (iter != elements.cend()) {
        return std::prev(iter);
    }
    return iter;
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


/** Find first and last positions of an element in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-first-and-last-positions-of-an-element-in-a-sorted-array/
 *
 * Given a sorted array with possibly duplicate elements, the task is to find indexes
 * of first and last occurrences of an element x in the given array.
 *
 * @reference   Find the index of first 1 in a sorted array of 0’s and 1’s
 *              https://www.geeksforgeeks.org/find-index-first-1-sorted-array-0s-1s/
 */
auto BinarySearch_First_Recursive(const ArrayType &elements,
                                  const ArrayType::const_iterator cbegin,
                                  const ArrayType::size_type length,
                                  const ArrayType::value_type x) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x and (mid == elements.cbegin() or x > *std::prev(mid))) {
            return mid;
        }
        if (*mid < x) {
            return BinarySearch_First_Recursive(elements, std::next(mid), length - half - 1, x);
        }
        return BinarySearch_First_Recursive(elements, cbegin, half, x);
    }

    return elements.cend();
}

auto BinarySearch_First_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_First_Recursive(elements, elements.cbegin(), elements.size(), x);
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 */
auto BinarSearch_First_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid < x) {
            cbegin = std::next(mid);
            length -= (half + 1);
        } else {
            if (*mid == x) {
                output = mid;
            }
            length = half;
        }
    }

    return output;
}


auto BinarySearch_Last_Recursive(const ArrayType &elements,
                                 const ArrayType::const_iterator cbegin,
                                 const ArrayType::size_type length,
                                 const ArrayType::value_type x) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;
        const auto mid_next = std::next(mid);

        if (*mid == x and (mid_next == elements.cend() or x < *mid_next)) {
            return mid;
        }
        if (*mid > x) {
            return BinarySearch_Last_Recursive(elements, cbegin, half, x);
        }
        return BinarySearch_Last_Recursive(elements, std::next(mid), length - half - 1, x);
    }

    return elements.cend();
}

auto BinarySearch_Last_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_Last_Recursive(elements, elements.cbegin(), elements.size(), x);
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 */
auto BinarSearch_Last_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid > x) {
            length = half;
        } else {
            if (*mid == x) {
                output = mid;
            }
            cbegin = std::next(mid);
            length -= (half + 1);
        }
    }

    return output;
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 * Find index of first occurrence of least element greater than key in array
 */
auto UpperBound_BinarySearch(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid > x) {
            output = mid;
            length = half;
        } else {
            cbegin = std::next(mid);
            length -= (half + 1);
        }
    }

    return output;
}


inline auto UpperBound_STL(const ArrayType &elements, const ArrayType::value_type x) {
    return std::upper_bound(elements.cbegin(), elements.cend(), x);
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 * Find index of last occurrence of greatest element less than key in array
 */
auto GreatestLesser_BinarySearch(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid < x) {
            output = mid;
            cbegin = std::next(mid);
            length -= (half + 1);
        } else {
            length = half;
        }
    }

    return output;
}


inline auto GreatestLesser_STL(const ArrayType &elements, const ArrayType::value_type x) {
    const auto iter = std::lower_bound(elements.cbegin(), elements.cend(), x);
    if (iter == elements.cbegin() or iter == elements.cend()) {
        elements.cend();
    }
    return std::prev(iter);
}


/**
 * @reference   Randomized Binary Search Algorithm
 *              https://www.geeksforgeeks.org/randomized-binary-search-algorithm/
 */
auto BinarySearch_Randomized_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    assert(not elements.empty());
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    ArrayType::size_type low = 0;
    auto high = elements.size() - 1;

    while (low <= high) {
        const auto mid = Random_Number(low, high);
        if (elements[mid] == x) {
            return elements.cbegin() + mid;
        }

        if (elements[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return elements.cend();
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {2, 3, 4, 10, 40};


SIMPLE_BENCHMARK(BinarySearch_Recursive, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Recursive, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Recursive, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Recursive, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(BinarySearch_Iterative, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Iterative, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Iterative, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(BinarySearch_Meta, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Meta, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Meta, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Meta, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Meta, TestNotExist, VALUES2.cend(), VALUES2, 999);


SIMPLE_BENCHMARK(BinarySearch_Uniform5, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Uniform5, TestBegin, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Uniform5, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Uniform5, TestLast, std::prev(VALUES2.cend()), VALUES2, VALUES2.back());
SIMPLE_TEST(BinarySearch_Uniform5, TestNotExist, VALUES2.cend(), VALUES2, 999);


const ArrayType VALUES3 = {2, 3, 3, 5, 5, 5, 6, 6};


SIMPLE_BENCHMARK(BinarSearch_First_Iterative, VALUES2, 10);

SIMPLE_TEST(BinarSearch_First_Iterative, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarSearch_First_Iterative, TestBegin2, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarSearch_First_Iterative, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarSearch_First_Iterative, TestLast, std::prev(VALUES2.cend()), VALUES2,
            VALUES2.back());
SIMPLE_TEST(BinarSearch_First_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);
SIMPLE_TEST(BinarSearch_First_Iterative, TestBegin3, VALUES3.cbegin(), VALUES3, VALUES3.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarSearch_First_Iterative, TestSample2, VALUES3, 5);


SIMPLE_BENCHMARK(BinarySearch_First_Recursive, VALUES2, 10);

SIMPLE_TEST(BinarySearch_First_Recursive, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_First_Recursive, TestBegin2, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Recursive, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_First_Recursive, TestLast, std::prev(VALUES2.cend()), VALUES2,
            VALUES2.back());
SIMPLE_TEST(BinarySearch_First_Recursive, TestNotExist, VALUES2.cend(), VALUES2, 999);
SIMPLE_TEST(BinarySearch_First_Recursive, TestBegin3, VALUES3.cbegin(), VALUES3, VALUES3.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Recursive, TestSample2, VALUES3, 5);


SIMPLE_BENCHMARK(BinarSearch_Last_Iterative, VALUES2, 10);

SIMPLE_TEST(BinarSearch_Last_Iterative, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestBegin2, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarSearch_Last_Iterative, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestLast, std::prev(VALUES2.cend()), VALUES2,
            VALUES2.back());
SIMPLE_TEST(BinarSearch_Last_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestLast3, std::prev(VALUES3.cend()), VALUES3,
            VALUES3.back());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Upper, BinarSearch_Last_Iterative, TestSample2, VALUES3, 5);


SIMPLE_BENCHMARK(BinarySearch_Last_Recursive, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Last_Recursive, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestBegin2, VALUES2.cbegin(), VALUES2, VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Last_Recursive, TestSample1, VALUES2, 10);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestLast, std::prev(VALUES2.cend()), VALUES2,
            VALUES2.back());
SIMPLE_TEST(BinarySearch_Last_Recursive, TestNotExist, VALUES2.cend(), VALUES2, 999);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestLast3, std::prev(VALUES3.cend()), VALUES3,
            VALUES3.back());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Upper, BinarySearch_Last_Recursive, TestSample2, VALUES3, 5);


SIMPLE_BENCHMARK(UpperBound_BinarySearch, VALUES2, 10);

SIMPLE_TEST(UpperBound_BinarySearch, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(UpperBound_BinarySearch, TestBegin2, VALUES2.cbegin(), VALUES2, VALUES2.front() - 1);
MUTUAL_SIMPLE_TEST(UpperBound_STL, UpperBound_BinarySearch, TestSample1, VALUES2, 10);
SIMPLE_TEST(UpperBound_BinarySearch, TestLast, std::prev(VALUES2.cend()), VALUES2,
            VALUES2.back() - 1);
SIMPLE_TEST(UpperBound_BinarySearch, TestNotExist, VALUES2.cend(), VALUES2, 999);
SIMPLE_TEST(UpperBound_BinarySearch, TestLast3, VALUES3.cend(), VALUES3, VALUES3.back());
MUTUAL_SIMPLE_TEST(UpperBound_STL, UpperBound_BinarySearch, TestSample2, VALUES3, 5);


SIMPLE_BENCHMARK(GreatestLesser_BinarySearch, VALUES2, 10);

SIMPLE_TEST(GreatestLesser_BinarySearch, TestEmpty, VALUES1.cend(), VALUES1, 10);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestBegin2, VALUES2.cbegin(), VALUES2,
            VALUES2.front() + 1);
MUTUAL_SIMPLE_TEST(GreatestLesser_STL, GreatestLesser_BinarySearch, TestSample1, VALUES2, 10);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestLast, std::prev(VALUES2.cend()), VALUES2,
            VALUES2.back() + 1);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestNotExist, VALUES2.cend(), VALUES2, 0);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestLast3, std::prev(VALUES3.cend()), VALUES3,
            VALUES2.back() + 1);
MUTUAL_SIMPLE_TEST(GreatestLesser_STL, GreatestLesser_BinarySearch, TestSample2, VALUES3, 5);


SIMPLE_BENCHMARK(BinarySearch_Randomized_Iterative, VALUES2, 10);

SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestBegin, VALUES2.cbegin(), VALUES2,
            VALUES2.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Randomized_Iterative, TestSample1, VALUES2,
                   10);
SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestLast, std::prev(VALUES2.cend()), VALUES2,
            VALUES2.back());
SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestNotExist, VALUES2.cend(), VALUES2, 999);
