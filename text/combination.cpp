#include "common_header.h"


namespace {

using ArrayType = std::unordered_multiset<std::string>;

/** Print all possible combinations of r elements in a given array of size n
 *
 * @reference   https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
 * @reference   Print all subsets of given size of a set
 *              https://www.geeksforgeeks.org/print-subsets-given-size-set/
 *
 * @reference   Make all combinations of size k
 *              https://www.geeksforgeeks.org/make-combinations-size-k/
 *
 * Given two numbers n and k and you have to find all possible combination of k numbers
 * from 1...n.
 */
void CombinationsOfLength_Start(const std::string_view elements,
                                const std::size_t length,
                                const std::size_t start,
                                std::string &one_combination,
                                ArrayType &results) {
    assert(length <= elements.size());

    for (auto i = start; i < elements.size(); ++i) {
        one_combination.push_back(elements[i]);
        if (one_combination.size() == length) {
            results.insert(one_combination);
        } else if (one_combination.size() < length) {
            CombinationsOfLength_Start(elements, length, i + 1, one_combination, results);
        }
        one_combination.pop_back();
    }
}

inline auto CombinationsOfLength_Start(const std::string_view elements,
                                       const std::size_t length) {
    std::string one_combination;
    ArrayType results;
    CombinationsOfLength_Start(elements, length, 0, one_combination, results);

    return results;
}


void CombinationsOfLength_Include(const std::string_view elements,
                                  const std::size_t length,
                                  const std::size_t start,
                                  std::string &one_combination,
                                  ArrayType &results) {
    if (start < elements.size()) {
        one_combination.push_back(elements[start]);
        if (one_combination.size() == length) {
            results.insert(one_combination);
        } else if (one_combination.size() < length) {
            CombinationsOfLength_Include(elements, length, start + 1, one_combination, results);
        }
        one_combination.pop_back();

        if (one_combination.size() < length) {
            CombinationsOfLength_Include(elements, length, start + 1, one_combination, results);
        }
    }
}

inline auto CombinationsOfLength_Include(const std::string_view elements,
                                         const std::size_t length) {
    std::string one_combination;
    ArrayType results;
    CombinationsOfLength_Include(elements, length, 0, one_combination, results);

    return results;
}


/**
 * @reference   Iterator for Combination
 *              https://leetcode.com/problems/iterator-for-combination/
 *
 * Design the CombinationIterator class:
 *  CombinationIterator(string characters, int combinationLength) Initializes the object
 *      with a string characters of sorted distinct lowercase English letters and a number
 *      combinationLength as arguments.
 *  next() Returns the next combination of length combinationLength in lexicographical order.
 *  hasNext() Returns true if and only if there exists a next combination.
 * 1 <= combinationLength <= characters.length <= 15
 */
class CombinationIterator {
    std::string_view chars;
    int length;
    unsigned mask;

public:
    constexpr CombinationIterator(const std::string_view characters, const int l):
        chars(characters), length(l), mask((1 << characters.size()) - 1) {
    }

    std::string next() {
        hasNext();
        std::string result;
        for (std::size_t i = 0; i < chars.size(); ++i) {
            if (mask & (1 << (chars.size() - i - 1))) {
                result.push_back(chars[i]);
            }
        }
        --mask;

        return result;
    }

    constexpr bool hasNext() {
        while (mask and __builtin_popcount(mask) != length) {
            --mask;
        }

        return mask;
    }
};

auto testCombinationIterator(const std::string_view chars,
                             const std::size_t length) {
    ArrayType results;
    CombinationIterator iter(chars, length);
    while (iter.hasNext()) {
        results.insert(iter.next());
    }

    return results;
}


/** Combinations of a String
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 7.
 * @reference   Backtracking to find all subsets
 *              https://www.geeksforgeeks.org/backtracking-to-find-all-subsets/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.4.
 */
void AllCombinations_Recursive(const std::string_view elements,
                               const std::size_t start,
                               std::string &one_combination,
                               ArrayType &results) {
    for (auto i = start; i < elements.size(); ++i) {
        one_combination.push_back(elements[i]);
        results.insert(one_combination);
        AllCombinations_Recursive(elements, i + 1, one_combination, results);
        one_combination.pop_back();
    }
}

inline auto AllCombinations_Recursive(const std::string_view elements) {
    std::string one_combination;
    ArrayType results;
    AllCombinations_Recursive(elements, 0, one_combination, results);

    return results;
}


/**
 * @reference   Power Set
 *              https://www.geeksforgeeks.org/power-set/
 * @reference   Find all distinct subsets of a given set using BitMasking Approach
 *              https://www.geeksforgeeks.org/find-distinct-subsets-given-set/
 * @reference   Printing all subsets of {1,2,3,...n} without using array or loop
 *              https://www.geeksforgeeks.org/printing-all-subsets-of-123-n-without-using-array-or-loop/
 */
auto AllCombinations_BitMask(const std::string_view elements) {
    assert(elements.size() < BitsNumber<unsigned long long>);

    const auto power_set_size = 1ull << elements.size();

    ArrayType results;
    for (auto mask = 1ull; mask < power_set_size; ++mask) {
        std::string a_subset;
        for (std::size_t i = 0; i < elements.size(); ++i) {
            if (mask & (1ull << i)) {
                a_subset.push_back(elements[i]);
            }
        }
        results.insert(a_subset);
    }

    return results;
}


/**
 * @reference   Recursive program to generate power set
 *              https://www.geeksforgeeks.org/recursive-program-to-generate-power-set/
 *
 * @reference   Subsets
 *              https://leetcode.com/problems/subsets/
 *
 * Given an integer array nums of unique elements, return all possible subsets (the power
 * set). The solution set must not contain duplicate subsets. Return the solution in any
 * order.
 */
void AllCombinations_Recursive_Copy(const std::string_view elements,
                                    ArrayType &results,
                                    const std::size_t index = 0,
                                    const std::string &subset = "") {
    if (index == elements.size()) {
        if (not subset.empty()) {
            results.insert(subset);
        }
        return;
    }

    AllCombinations_Recursive_Copy(elements, results, index + 1, subset + elements[index]);
    AllCombinations_Recursive_Copy(elements, results, index + 1, subset);
}

inline auto AllCombinations_Recursive_Copy(const std::string_view elements) {
    ArrayType results;
    AllCombinations_Recursive_Copy(elements, results);

    return results;
}


auto AllCombinations_Iterative(const std::string_view elements) {
    ArrayType results = {""};

    for (const auto c : elements) {
        ArrayType new_subsets = results;
        for (const auto &curr : results) {
            new_subsets.insert(curr + c);
        }

        results.swap(new_subsets);
    }

    results.erase("");
    return results;
}


/**
 * @reference   Subsets II
 *              https://leetcode.com/problems/subsets-ii/
 *
 * Given an integer array nums that may contain duplicates, return all possible subsets
 * (the power set). The solution set must not contain duplicate subsets. Return the
 * solution in any order.
 */
void AllCombinationsWithDuplicates_For(const std::string &elements,
                                       const std::size_t start,
                                       std::string &one_combination, ArrayType &results) {
    results.insert(one_combination);

    for (auto i = start; i < elements.size(); ++i) {
        if (i != start and elements[i] == elements[i - 1]) {
            continue;
        }

        one_combination.push_back(elements[i]);
        AllCombinationsWithDuplicates_For(elements, i + 1, one_combination, results);
        one_combination.pop_back();
    }
}

inline auto AllCombinationsWithDuplicates_For(std::string elements) {
    ArrayType results;
    std::sort(elements.begin(), elements.end());
    std::string one_combination;
    AllCombinationsWithDuplicates_For(elements, 0, one_combination, results);

    return results;
}


void AllCombinationsWithDuplicates(const std::string &elements, std::size_t i,
                                   std::string &one_combination, ArrayType &results) {
    if (i == elements.size()) {
        results.insert(one_combination);
        return;
    }

    one_combination.push_back(elements[i]);
    AllCombinationsWithDuplicates(elements, i + 1, one_combination, results);
    one_combination.pop_back();

    i++;
    while (i < elements.size() and elements[i] == elements[i - 1]) {
        i++;
    }

    AllCombinationsWithDuplicates(elements, i, one_combination, results);
}

inline auto AllCombinationsWithDuplicates(std::string elements) {
    ArrayType results;
    std::sort(elements.begin(), elements.end());
    std::string one_combination;
    AllCombinationsWithDuplicates(elements, 0, one_combination, results);

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {"a"};
const ArrayType EXPECTED2 = {"a", "b", "ab"};
const ArrayType EXPECTED3 = {"w", "x", "y", "z", "wx", "xy", "yz", "wxy", "xyz", "wxyz", "xz", "wxz", "wy", "wyz", "wz"};
const ArrayType EXPECTED4 = {"wx", "xy", "yz", "xz", "wy", "wz"};
const ArrayType EXPECTED5 = {"123", "124", "125", "134", "135", "145", "234", "235", "245", "345"};


THE_BENCHMARK(CombinationsOfLength_Start, "abcd", 2);

SIMPLE_TEST(CombinationsOfLength_Start, TestSAMPLE1, EXPECTED1, "a", 1);
SIMPLE_TEST(CombinationsOfLength_Start, TestSAMPLE4, EXPECTED4, "wxyz", 2);
SIMPLE_TEST(CombinationsOfLength_Start, TestSAMPLE5, EXPECTED5, "12345", 3);


THE_BENCHMARK(CombinationsOfLength_Include, "abcd", 2);

SIMPLE_TEST(CombinationsOfLength_Include, TestSAMPLE1, EXPECTED1, "a", 1);
SIMPLE_TEST(CombinationsOfLength_Include, TestSAMPLE4, EXPECTED4, "wxyz", 2);
SIMPLE_TEST(CombinationsOfLength_Include, TestSAMPLE5, EXPECTED5, "12345", 3);


THE_BENCHMARK(testCombinationIterator, "abcd", 2);

SIMPLE_TEST(testCombinationIterator, TestSAMPLE1, EXPECTED1, "a", 1);
SIMPLE_TEST(testCombinationIterator, TestSAMPLE4, EXPECTED4, "wxyz", 2);
SIMPLE_TEST(testCombinationIterator, TestSAMPLE5, EXPECTED5, "12345", 3);


THE_BENCHMARK(AllCombinations_Recursive, "abcd");

SIMPLE_TEST(AllCombinations_Recursive, TestSAMPLE1, EXPECTED1, "a");
SIMPLE_TEST(AllCombinations_Recursive, TestSAMPLE2, EXPECTED2, "ab");
SIMPLE_TEST(AllCombinations_Recursive, TestSAMPLE3, EXPECTED3, "wxyz");


THE_BENCHMARK(AllCombinations_BitMask, "abcd");

SIMPLE_TEST(AllCombinations_BitMask, TestSAMPLE1, EXPECTED1, "a");
SIMPLE_TEST(AllCombinations_BitMask, TestSAMPLE2, EXPECTED2, "ab");
SIMPLE_TEST(AllCombinations_BitMask, TestSAMPLE3, EXPECTED3, "wxyz");


THE_BENCHMARK(AllCombinations_Recursive_Copy, "abcd");

SIMPLE_TEST(AllCombinations_Recursive_Copy, TestSAMPLE1, EXPECTED1, "a");
SIMPLE_TEST(AllCombinations_Recursive_Copy, TestSAMPLE2, EXPECTED2, "ab");
SIMPLE_TEST(AllCombinations_Recursive_Copy, TestSAMPLE3, EXPECTED3, "wxyz");


THE_BENCHMARK(AllCombinations_Iterative, "abcd");

SIMPLE_TEST(AllCombinations_Iterative, TestSAMPLE1, EXPECTED1, "a");
SIMPLE_TEST(AllCombinations_Iterative, TestSAMPLE2, EXPECTED2, "ab");
SIMPLE_TEST(AllCombinations_Iterative, TestSAMPLE3, EXPECTED3, "wxyz");


const ArrayType EXPECTED6 = {"", "1", "12", "122", "2", "22"};
const ArrayType EXPECTED7 = {"", "0"};


THE_BENCHMARK(AllCombinationsWithDuplicates_For, "122");

SIMPLE_TEST(AllCombinationsWithDuplicates_For, TestSAMPLE6, EXPECTED6, "122");
SIMPLE_TEST(AllCombinationsWithDuplicates_For, TestSAMPLE7, EXPECTED7, "0");


THE_BENCHMARK(AllCombinationsWithDuplicates, "122");

SIMPLE_TEST(AllCombinationsWithDuplicates, TestSAMPLE6, EXPECTED6, "122");
SIMPLE_TEST(AllCombinationsWithDuplicates, TestSAMPLE7, EXPECTED7, "0");
