#include "common_header.h"

#include "a_pair_elements_sum_as_n.h"

#include "data_structure/tree/binary_tree/BST/binary_search_tree.h"
#include "data_structure/tree/binary_tree/binary_tree_traversals.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<bool>;
using OperationArrayType = std::vector<std::pair<bool, int>>;

/**
 * @reference   Given an array A[] and a number x, check for pair in A[] with sum as x
 *              https://www.geeksforgeeks.org/given-an-array-a-and-a-number-x-check-for-pair-in-a-with-sum-as-x/
 *
 * Given an array A[] of n numbers and another number x, determines whether or not there exist two
 * elements in A whose sum is exactly x.
 *
 * @reference   Two Sum
 *              https://leetcode.com/problems/two-sum/
 *
 * Given an array of integers nums and an integer target, return indices of the two numbers such that
 * they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element
 * twice.
 * You can return the answer in any order.
 *
 * @complexity: O(n)
 *
 * @tags    #hash-table
 */
template<typename ArrayType>
inline constexpr auto HasPairOfElementsSumAsN_Hashmap(const ArrayType &values, const int target) {
    return PairOfElementsSumAsN_Hashmap<ArrayType>(values, target, nullptr);
}


/**
 * @reference   Two Pointers Technique
 *              https://www.geeksforgeeks.org/two-pointers-technique/
 *
 * @complexity: Same as the sorting algorithm used.
 *
 * @reference   Find pairs with given sum in doubly linked list
 *              https://www.geeksforgeeks.org/find-pairs-given-sum-doubly-linked-list/
 *
 * Given a sorted doubly linked list of positive distinct elements, the task is to find pairs in doubly
 * linked list whose sum is equal to given value x, without using any extra space?
 *
 * @reference   Two Sum II - Input array is sorted
 *              https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two
 * numbers such that they add up to a specific target number. Let these two numbers be numbers[index1]
 * and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
 * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1,
 * index2] of length 2.
 * The tests are generated such that there is exactly one solution. You may not use the same element
 * twice.
 * Your solution must use only constant extra space.
 *
 * @tags    #sorting #two-pointers
 */
template<typename Container>
constexpr auto HasPairOfElementsSumAsN_TwoPointers(const Container &values, const int target) {
    assert(std::is_sorted(values.cbegin(), values.cend()));

    auto left = values.cbegin();
    auto right = std::prev(values.cend());

    while (left != right) {
        const auto sum = *left + *right;
        if (sum == target) {
            return true;
        } else if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }

    return false;
}

inline auto HasPairOfElementsSumAsN_Sort(ArrayType values, const int target) {
    if (values.empty()) {
        return false;
    }
    std::sort(values.begin(), values.end());
    return HasPairOfElementsSumAsN_TwoPointers(values, target);
}


/**
 * @reference   Count pairs with given sum
 *              https://www.geeksforgeeks.org/count-pairs-with-given-sum/
 * @reference   Count pairs with given sum | Set 2
 *              https://www.geeksforgeeks.org/count-pairs-with-given-sum-set-2/
 *
 * Given an array of integers, and a number 'sum', find the number of pairs of integers in the array
 * whose sum is equal to 'sum'.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.12.
 *
 * @tags    #hash-table #sorting #two-pointers
 */


/**
 * @reference   Max Number of K-Sum Pairs
 *              https://leetcode.com/problems/max-number-of-k-sum-pairs/
 *
 * You are given an integer array nums and an integer k.
 * In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.
 * Return the maximum number of operations you can perform on the array.
 * 1 <= nums[i] <= 10^9
 * 1 <= k <= 10^9
 *
 * @tags    #hash-table
 */
auto CountTwoSumsSingleUse(const ArrayType &nums, const int k) {
    std::unordered_map<int, int> counts;
    int result = 0;
    for (const auto n : nums) {
        const auto other = k - n;
        const auto iter = counts.find(other);
        if (iter != counts.cend() and iter->second > 0) {
            ++result;
            --(iter->second);
        } else {
            ++counts[n];
        }
    }

    return result;
}


/**
 * @reference   Two Sum III - Data structure design
 *              https://aaronice.gitbook.io/lintcode/high_frequency/two-sum-iii-data-structure-design
 *
 * Design and implement a TwoSum class. It should support the following operations:
 *  add- Add the number to an internal data structure.
 *  find- Find if there exists any pair of numbers which sum is equal to the value.
 *
 * @tags    #hash-table
 */
class TwoSum {
    std::unordered_map<int, int> counter;
    int low = INT_MAX;
    int high = INT_MIN;

public:
    void Add(const int number) {
        if (not counter[number]++) {
            low = std::min(number, low);
            high = std::max(number, high);
        }
    }

    auto Find(const int target) const {
        if (low * 2 > target or target > high * 2) {
            return false;
        }

        for (const auto [number, _] : counter) {
            const auto the_other = target - number;
            if (const auto iter = counter.find(the_other); iter != counter.cend()) {
                if (iter->second > (number == the_other)) {
                    return true;
                }
            }
        }

        return false;
    }
};

auto testTwoSum(const OperationArrayType &operations) {
    OutputType results;
    TwoSum two_sum;
    for (const auto &[is_add, value] : operations) {
        if (is_add) {
            two_sum.Add(value);
        } else {
            results.push_back(two_sum.Find(value));
        }
    }

    return results;
}


/**
 * @reference   Find a pair with given sum in BST
 *              https://www.geeksforgeeks.org/find-pair-given-sum-bst/
 * @reference   Two Sum IV - Input is a BST
 *              https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
 *
 * Given the root of a binary search tree and an integer k, return true if there exist two elements in
 * the BST such that their sum is equal to k, or false otherwise.
 */
inline auto HasPairOfElementsSumAsN_BST_Inorder(const BinaryTree::Node::PointerType root,
                                                const int target) {
    BinaryTree::ArrayType inorder;
    InorderTraversal_Recursive(root, inorder);
    return HasPairOfElementsSumAsN_TwoPointers(inorder, target);
}


inline auto HasPairOfElementsSumAsN_BST_Hash(const BinaryTree::Node::PointerType node,
                                             const int target,
                                             std::unordered_set<int> &hash) {
    if (node) {
        if (hash.find(target - node->value) != hash.cend()) {
            return true;
        }

        hash.insert(node->value);
        return HasPairOfElementsSumAsN_BST_Hash(node->left, target, hash) or
               HasPairOfElementsSumAsN_BST_Hash(node->right, target, hash);
    }

    return false;
}

inline auto HasPairOfElementsSumAsN_BST_Hash(const BinaryTree::Node::PointerType root,
                                             const int target) {
    std::unordered_set<int> hash;
    return HasPairOfElementsSumAsN_BST_Hash(root, target, hash);
}


/**
 * @reference   Find a pair with given sum in a Balanced BST
 *              https://www.geeksforgeeks.org/find-a-pair-with-given-sum-in-bst/
 * @reference   Pair with a given sum in BST | Set 2
 *              https://www.geeksforgeeks.org/pair-with-a-given-sum-in-bst-set-2/
 */
auto HasPairOfElementsSumAsN_BST_TwoPointers(const BinaryTree::Node::PointerType root,
                                             const int target) {
    std::stack<BinaryTree::Node::PointerType> left_stack;
    std::stack<BinaryTree::Node::PointerType> right_stack;

    bool move_left = true, move_right = true;
    int left = 0, right = 1;
    auto left_current = root;
    auto right_current = root;

    while (left < right) {
        while (move_left) {
            if (left_current) {
                left_stack.push(left_current);
                left_current = left_current->left;
            } else {
                if (not left_stack.empty()) {
                    left_current = left_stack.top();
                    left_stack.pop();
                    left = left_current->value;
                    left_current = left_current->right;
                }
                move_left = false;
            }
        }

        while (move_right) {
            if (right_current) {
                right_stack.push(right_current);
                right_current = right_current->right;
            } else {
                if (not right_stack.empty()) {
                    right_current = right_stack.top();
                    right_stack.pop();
                    right = right_current->value;
                    right_current = right_current->left;
                }
                move_right = false;
            }
        }

        const auto sum = left + right;
        if ((left != right) and sum == target) {
            return true;
        } else if (sum < target) {
            move_left = true;
        } else if (sum > target) {
            move_right = true;
        }
    }

    return false;
}


/**
 * @reference   Number of Subsequences That Satisfy the Given Sum Condition
 *              https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
 *
 * You are given an array of integers nums and an integer target.
 * Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum
 * element on it is less or equal to target. Since the answer may be too large, return it modulo 10^9 + 7.
 * 1 <= nums.length <= 10^5
 */
auto NumberSubsequences(ArrayType nums, const int target) {
    std::sort(nums.begin(), nums.end());

    std::vector<int> powers(nums.size(), 1);
    for (std::size_t i = 1; i < nums.size(); ++i) {
        powers[i] = powers[i - 1] * 2 % LARGE_PRIME;
    }

    int left = 0;
    int right = nums.size() - 1;
    int result = 0;

    while (left <= right) {
        if (nums[left] + nums[right] > target) {
            --right;
        } else {
            result = (result + powers[right - left++]) % LARGE_PRIME;
        }
    }

    return result;
}


/**
 * @reference   3Sum
 *              https://leetcode.com/problems/3sum/
 *
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i
 * != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Notice that the solution set must not contain duplicate triplets.
 *
 * @reference   Find all triplets with zero sum
 *              https://www.geeksforgeeks.org/find-triplets-array-whose-sum-equal-zero/
 *
 * @reference   Find a triplet that sum to a given value
 *              https://www.geeksforgeeks.org/find-a-triplet-that-sum-to-a-given-value/
 * @reference   Print all triplets with given sum
 *              https://www.geeksforgeeks.org/print-all-triplets-with-given-sum/
 * @reference   All unique triplets that sum up to a given value
 *              https://www.geeksforgeeks.org/unique-triplets-sum-given-value/
 *
 * @tags    #sorting #two-pointers
 */
auto ThreeSum(ArrayType nums, const int target) {
    std::sort(nums.begin(), nums.end());

    std::vector<ArrayType> results;
    const int SIZE = nums.size();
    for (int i = 0; i < SIZE - 2; ++i) {
        if (i >= 1 and nums[i] == nums[i - 1]) {
            continue;
        }

        auto left = i + 1;
        int right = SIZE - 1;
        const auto X = target - nums[i];
        while (left < right) {
            const auto sum = nums[left] + nums[right];
            if (sum == X) {
                results.push_back({nums[i], nums[left], nums[right]});

                while (left < SIZE - 1 and nums[left] == nums[left + 1]) {
                    ++left;
                }
                while (right > 0 and nums[right] == nums[right - 1]) {
                    --right;
                }

                ++left;
                --right;
            } else if (sum < X) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return results;
}


/**
 * @reference   3Sum With Multiplicity
 *              https://leetcode.com/problems/3sum-with-multiplicity/
 *
 * Given an integer array arr, and an integer target, return the number of tuples i, j, k such that i <
 * j < k and arr[i] + arr[j] + arr[k] == target.
 * As the answer can be very large, return it modulo 10^9 + 7.
 * 0 <= arr[i] <= 100
 */
auto ThreeSumWithMultiplicity(const ArrayType &nums, const int target) {
    long counts[101] = {};
    for (const auto n : nums) {
        ++counts[n];
    }

    long result = 0;
    for (int i = 0; i < 101; ++i) {
        for (auto j = i; j < 101; ++j) {
            const auto k = target - i - j;
            if (k < 0 or k < j) {
                break;
            }
            if (k >= 101) {
                continue;
            }

            if (i == j and j == k) {
                result += counts[i] * (counts[i] - 1) * (counts[i] - 2) / 6;
            } else if (i == j and j != k) {
                result += counts[i] * (counts[i] - 1) / 2 * counts[k];
            } else if (j == k) {
                result += counts[k] * (counts[k] - 1) / 2 * counts[i];
            } else {
                result += counts[i] * counts[j] * counts[k];
            }
        }
    }

    return result % LARGE_PRIME;
}


/**
 * @reference   4Sum
 *              https://leetcode.com/problems/4sum/
 *
 * Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b],
 * nums[c], nums[d]] such that:
 *  0 <= a, b, c, d < n
 *  a, b, c, and d are distinct.
 *  nums[a] + nums[b] + nums[c] + nums[d] == target
 * You may return the answer in any order.
 */
auto twoSum(const ArrayType &nums, const int target, const int start) {
    std::vector<ArrayType> results;

    const int LAST = nums.size() - 1;
    int left = start, right = LAST;
    while (left < right) {
        const int sum = nums[left] + nums[right];
        if (sum < target or (left > start and nums[left] == nums[left - 1])) {
            ++left;
        } else if (sum > target or (right < LAST and nums[right] == nums[right + 1])) {
            --right;
        } else
            results.push_back({nums[left++], nums[right--]});
    }

    return results;
}

auto kSum(const int K, const ArrayType &nums, const int target, const std::size_t start) {
    std::vector<ArrayType> results;

    if (start == nums.size() or nums[start] * K > target or target > nums.back() * K) {
        return results;
    }

    if (K == 2) {
        return twoSum(nums, target, start);
    }

    for (auto i = start; i < nums.size(); ++i) {
        if (i == start or nums[i - 1] != nums[i]) {
            auto sub_results = kSum(K - 1, nums, target - nums[i], i + 1);
            for (auto &one_result : sub_results) {
                one_result.insert(one_result.cbegin(), nums[i]);
                results.push_back(std::move(one_result));
            }
        }
    }

    return results;
}

inline auto kSum(const int K, ArrayType nums, const int target) {
    std::sort(nums.begin(), nums.end());

    return kSum(K, nums, target, 0);
}

inline auto FourSum(ArrayType nums, const int target) {
    return kSum(4, std::move(nums), target);
}


/** Given two unsorted arrays, find all pairs whose sum is x
 *
 * @reference   https://www.geeksforgeeks.org/given-two-unsorted-arrays-find-pairs-whose-sum-x/
 *
 * Given two unsorted arrays of distinct elements, the task is to find all pairs from both arrays whose
 * sum is equal to x.
 */
auto FindAllPairsSumAsN_Hash(const ArrayType &arr1,
                             const ArrayType &arr2,
                             const ArrayType::value_type SUM) {
    std::unordered_set array1_set(arr1.cbegin(), arr1.cend());
    std::vector<ArrayType> outputs;

    for (const auto elem : arr2) {
        const auto pair = SUM - elem;
        if (array1_set.find(pair) != array1_set.cend()) {
            outputs.push_back({pair, elem});
        }
    }

    return outputs;
}


/**
 * @reference   Count pairs from two sorted arrays whose sum is equal to a given value x
 *              https://www.geeksforgeeks.org/count-pairs-two-sorted-arrays-whose-sum-equal-given-value-x/
 *
 * Given two sorted arrays of size m and n of distinct elements. Given a value x. The problem is to
 * count all pairs from both arrays whose sum is equal to x. Note: The pair has an element from each
 * array.
 */
auto FindAllPairsSumAsN_TwoPointers(const ArrayType &arr1,
                                    const ArrayType &arr2,
                                    const ArrayType::value_type SUM) {
    assert(std::is_sorted(arr1.cbegin(), arr1.cend()));
    assert(std::is_sorted(arr2.cbegin(), arr2.cend()));

    std::vector<ArrayType> outputs;
    auto l = arr1.cbegin();
    auto r = arr2.crbegin();

    while (l != arr1.cend() and r != arr2.crend()) {
        const auto new_sum = *l + *r;
        if (new_sum == SUM) {
            outputs.push_back({*l, *r});
            ++l;
            ++r;
        } else if (new_sum < SUM) {
            ++l;
        } else {
            ++r;
        }
    }

    return outputs;
}

inline auto FindAllPairsSumAsN_Sort_TwoPointers(ArrayType arr1,
                                                ArrayType arr2,
                                                const ArrayType::value_type SUM) {
    std::sort(arr1.begin(), arr1.end());
    std::sort(arr2.begin(), arr2.end());

    return FindAllPairsSumAsN_TwoPointers(arr1, arr2, SUM);
}


/**
 * @reference   4Sum II
 *              https://leetcode.com/problems/4sum-ii/
 *
 * Given four integer arrays nums1, nums2, nums3, and nums4 all of length n, return the number of tuples
 * (i, j, k, l) such that:
 *  0 <= i, j, k, l < n
 *  nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 */
inline auto FourSum4Array(const std::vector<ArrayType> &num_arrays, const int target) {
    assert(num_arrays.size() == 4);

    std::unordered_map<int, int> half_sums;
    for (const auto i : num_arrays.front()) {
        for (const auto j : num_arrays[1]) {
            ++half_sums[i + j];
        }
    }

    int count = 0;
    for (const auto i : num_arrays[2]) {
        for (const auto j : num_arrays[3]) {
            const auto iter = half_sums.find(target - i - j);
            if (iter != half_sums.cend()) {
                count += iter->second;
            }
        }
    }

    return count;
}


/**
 * @reference   Count Special Quadruplets
 *              https://leetcode.com/problems/count-special-quadruplets/
 *
 * Given a 0-indexed integer array nums, return the number of distinct quadruplets (a, b, c, d) such
 * that:
 *  nums[a] + nums[b] + nums[c] == nums[d], and
 *  a < b < c < d
 * 1 <= nums[i] <= 100
 */
auto CountSpecialQuestions(const ArrayType &nums) {
    const int N = nums.size();

    int counts[201] = {};
    if (nums[N - 1] > nums[N - 2]) {
        counts[nums[N - 1] - nums[N - 2]] = 1;
    }

    int result = 0;
    for (int b = N - 3; b >= 1; --b) {
        for (int a = b - 1; a >= 0; --a) {
            result += counts[nums[a] + nums[b]];
        }

        for (int x = N - 1; x > b; --x) {
            if (nums[x] > nums[b]) {
                ++counts[nums[x] - nums[b]];
            }
        }
    }

    return result;
}


/**
 * @reference   Largest Positive Integer That Exists With Its Negative
 *              https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/
 *
 * Given an integer array nums that does not contain any zeros, find the largest positive integer k such
 * that -k also exists in the array.
 * Return the positive integer k. If there is no such integer, return -1.
 */

} //namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 4, 45, 6, 10, -8, 9, 4};


SIMPLE_BENCHMARK(HasPairOfElementsSumAsN_Hashmap, Sample1, VALUES3, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE1, false, VALUES1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE2, false, VALUES2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE3, true, VALUES3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE4, true, VALUES3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE5, false, VALUES3, 6);


THE_BENCHMARK(HasPairOfElementsSumAsN_Sort, VALUES3, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE1, false, VALUES1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE2, false, VALUES2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE3, true, VALUES3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE4, true, VALUES3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE5, false, VALUES3, 6);


const std::list<int> LIST1 = {};
const std::list<int> LIST2 = {1};
const std::list<int> LIST3 = {1, 4, 45, 6, 10, -8, 9, 4};


SIMPLE_BENCHMARK(HasPairOfElementsSumAsN_Hashmap, Sample3, LIST3, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE6, false, LIST1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE7, false, LIST2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE8, true, LIST3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE9, true, LIST3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE10, false, LIST3, 6);


const OperationArrayType SAMPLE1 = {{true, 1}, {true, 3}, {true, 5}, {false, 4}, {false, 7}};
const OutputType EXPECTED1 = {true, false};

const OperationArrayType SAMPLE2 = {{true, 3}, {true, 1}, {true, 2}, {false, 3}, {false, 6}};
const OutputType EXPECTED2 = {true, false};


THE_BENCHMARK(testTwoSum, SAMPLE1);

SIMPLE_TEST(testTwoSum, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(testTwoSum, TestSAMPLE2, EXPECTED2, SAMPLE2);


const auto SAMPLE1T = MakeTheSampleBST();


THE_BENCHMARK(HasPairOfElementsSumAsN_BST_Inorder, SAMPLE1T, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Inorder, TestSAMPLE1, true, SAMPLE1T, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Inorder, TestSAMPLE2, true, SAMPLE1T, 3);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Inorder, TestSAMPLE3, true, SAMPLE1T, 7);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Inorder, TestSAMPLE4, false, SAMPLE1T, -1);


THE_BENCHMARK(HasPairOfElementsSumAsN_BST_TwoPointers, SAMPLE1T, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_BST_TwoPointers, TestSAMPLE1, true, SAMPLE1T, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_TwoPointers, TestSAMPLE2, true, SAMPLE1T, 3);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_TwoPointers, TestSAMPLE3, true, SAMPLE1T, 7);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_TwoPointers, TestSAMPLE4, false, SAMPLE1T, -1);


THE_BENCHMARK(HasPairOfElementsSumAsN_BST_Hash, SAMPLE1T, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Hash, TestSAMPLE1, true, SAMPLE1T, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Hash, TestSAMPLE2, true, SAMPLE1T, 3);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Hash, TestSAMPLE3, true, SAMPLE1T, 7);
SIMPLE_TEST(HasPairOfElementsSumAsN_BST_Hash, TestSAMPLE4, false, SAMPLE1T, -1);


const std::vector<ArrayType> EXPECTED0 = {};

const ArrayType VALUES4 = {-1, 0, 1, 2, -1, -4};
const std::vector<ArrayType> EXPECTED4 = {{-1, -1, 2}, {-1, 0, 1}};

const ArrayType VALUES5 = {0, -1, 2, -3, 1};
const std::vector<ArrayType> EXPECTED5 = {{-3, 1, 2}, {-1, 0, 1}};

const ArrayType VALUES6 = {1, -2, 1, 0, 5};
const std::vector<ArrayType> EXPECTED6 = {{-2, 1, 1}};

const ArrayType VALUES7 = {12, 3, 4, 1, 6, 9};
const std::vector<ArrayType> EXPECTED7 = {{3, 9, 12}};

const ArrayType VALUES8 = {1, 2, 3, 4, 5};
const std::vector<ArrayType> EXPECTED8 = {{1, 3, 5}, {2, 3, 4}};

const ArrayType VALUES9 = {12, 3, 6, 1, 6, 9};
const std::vector<ArrayType> EXPECTED9 = {{3, 9, 12}, {6, 6, 12}};

const ArrayType VALUES10 = {-2, 0, 1, 1, 2};
const std::vector<ArrayType> EXPECTED10 = {{-2, 0, 2}, {-2, 1, 1}};

const ArrayType VALUES12T = {0, 0, 0, 0};
const std::vector<ArrayType> EXPECTED12T = {
    {0, 0, 0},
};


THE_BENCHMARK(ThreeSum, VALUES8, 8);

SIMPLE_TEST(ThreeSum, TestSAMPLE1, EXPECTED0, VALUES1, 0);
SIMPLE_TEST(ThreeSum, TestSAMPLE2, EXPECTED0, VALUES2, 0);
SIMPLE_TEST(ThreeSum, TestSAMPLE4, EXPECTED4, VALUES4, 0);
SIMPLE_TEST(ThreeSum, TestSAMPLE5, EXPECTED5, VALUES5, 0);
SIMPLE_TEST(ThreeSum, TestSAMPLE6, EXPECTED6, VALUES6, 0);
SIMPLE_TEST(ThreeSum, TestSAMPLE7, EXPECTED7, VALUES7, 24);
SIMPLE_TEST(ThreeSum, TestSAMPLE8, EXPECTED8, VALUES8, 9);
SIMPLE_TEST(ThreeSum, TestSAMPLE9, EXPECTED9, VALUES9, 24);
SIMPLE_TEST(ThreeSum, TestSAMPLE10, EXPECTED10, VALUES10, 0);
SIMPLE_TEST(ThreeSum, TestSAMPLE11, EXPECTED0, VALUES10, 10);
SIMPLE_TEST(ThreeSum, TestSAMPLE12, EXPECTED12T, VALUES12T, 0);


const ArrayType SAMPLE1M = {0, 0, 0, 0};
const ArrayType SAMPLE2M = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
const ArrayType SAMPLE3M = {1, 1, 2, 2, 2, 2};


THE_BENCHMARK(ThreeSumWithMultiplicity, SAMPLE1M, 0);

SIMPLE_TEST(ThreeSumWithMultiplicity, TestSAMPLE1, 4, SAMPLE1M, 0);
SIMPLE_TEST(ThreeSumWithMultiplicity, TestSAMPLE2, 20, SAMPLE2M, 8);
SIMPLE_TEST(ThreeSumWithMultiplicity, TestSAMPLE3, 12, SAMPLE3M, 5);


THE_BENCHMARK(kSum, 3, VALUES8, 8);

SIMPLE_TEST(kSum, TestSAMPLE1, EXPECTED0, 3, VALUES1, 0);
SIMPLE_TEST(kSum, TestSAMPLE2, EXPECTED0, 3, VALUES2, 0);
SIMPLE_TEST(kSum, TestSAMPLE4, EXPECTED4, 3, VALUES4, 0);
SIMPLE_TEST(kSum, TestSAMPLE5, EXPECTED5, 3, VALUES5, 0);
SIMPLE_TEST(kSum, TestSAMPLE6, EXPECTED6, 3, VALUES6, 0);
SIMPLE_TEST(kSum, TestSAMPLE7, EXPECTED7, 3, VALUES7, 24);
SIMPLE_TEST(kSum, TestSAMPLE8, EXPECTED8, 3, VALUES8, 9);
SIMPLE_TEST(kSum, TestSAMPLE9, EXPECTED9, 3, VALUES9, 24);
SIMPLE_TEST(kSum, TestSAMPLE10, EXPECTED10, 3, VALUES10, 0);
SIMPLE_TEST(kSum, TestSAMPLE11, EXPECTED0, 3, VALUES10, 10);


const ArrayType VALUES11 = {1, 0, -1, 0, -2, 2};
const std::vector<ArrayType> EXPECTED11 = {
    {-2, -1, 1, 2},
    {-2, 0, 0, 2},
    {-1, 0, 0, 1},
};

const ArrayType VALUES12 = {2, 2, 2, 2, 2};
const std::vector<ArrayType> EXPECTED12 = {{2, 2, 2, 2}};


THE_BENCHMARK(FourSum, VALUES11, 8);

SIMPLE_TEST(FourSum, TestSAMPLE11, EXPECTED11, VALUES11, 0);
SIMPLE_TEST(FourSum, TestSAMPLE12, EXPECTED12, VALUES12, 8);


const ArrayType SAMPLE1L = {-1, -2, 4, -6, 5, 7};
const ArrayType SAMPLE1R = {6, 3, 4, 0};
const std::vector<ArrayType> EXPECTED1T = {{5, 3}, {4, 4}};

const ArrayType SAMPLE2L = {1, 2, 4, 5, 7};
const ArrayType SAMPLE2R = {5, 6, 3, 4, 8};
const std::vector<ArrayType> EXPECTED2T = {{4, 5}, {5, 4}, {1, 8}};

const ArrayType SAMPLE3L = {1, 2, 3, 7, 5, 4};
const ArrayType SAMPLE3R = {0, 7, 4, 3, 2, 1};
const std::vector<ArrayType> EXPECTED3T = {{1, 7}, {4, 4}, {5, 3}, {7, 1}};

const ArrayType SAMPLE4L = {1, 0, -4, 7, 6, 4};
const ArrayType SAMPLE4R = {0, 2, 4, -3, 2, 1};
const std::vector<ArrayType> EXPECTED4T = {{6, 2}, {4, 4}, {6, 2}, {7, 1}};


THE_BENCHMARK(FindAllPairsSumAsN_Hash, SAMPLE1L, SAMPLE1R, 8);

SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample1, EXPECTED1T, SAMPLE1L, SAMPLE1R, 8);
SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample2, EXPECTED2T, SAMPLE2L, SAMPLE2R, 9);
SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample3, EXPECTED3T, SAMPLE3L, SAMPLE3R, 8);
SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample4, EXPECTED4T, SAMPLE4L, SAMPLE4R, 8);


const std::vector<ArrayType> EXPECTED_SORTED1 = {{4, 4}, {5, 3}};
const std::vector<ArrayType> EXPECTED_SORTED2 = {{1, 8}, {4, 5}, {5, 4}};


THE_BENCHMARK(FindAllPairsSumAsN_Sort_TwoPointers, SAMPLE1L, SAMPLE1R, 8);

SIMPLE_TEST(
    FindAllPairsSumAsN_Sort_TwoPointers, TestSample1, EXPECTED_SORTED1, SAMPLE1L, SAMPLE1R, 8);
SIMPLE_TEST(
    FindAllPairsSumAsN_Sort_TwoPointers, TestSample2, EXPECTED_SORTED2, SAMPLE2L, SAMPLE2R, 9);
SIMPLE_TEST(FindAllPairsSumAsN_Sort_TwoPointers, TestSample3, EXPECTED3T, SAMPLE3L, SAMPLE3R, 8);


const std::vector<ArrayType> SAMPLE1A = {{1, 2}, {-2, -1}, {-1, 2}, {0, 2}};

const std::vector<ArrayType> SAMPLE2A = {{0}, {0}, {0}, {0}};

const std::vector<ArrayType> SAMPLE3A = {{-1, -1}, {-1, 1}, {-1, 1}, {1, -1}};


THE_BENCHMARK(FourSum4Array, SAMPLE1A, 0);

SIMPLE_TEST(FourSum4Array, TestSample1, 2, SAMPLE1A, 0);
SIMPLE_TEST(FourSum4Array, TestSample2, 1, SAMPLE2A, 0);
SIMPLE_TEST(FourSum4Array, TestSample3, 6, SAMPLE3A, 0);


const ArrayType SAMPLE1Q = {1, 2, 3, 6};
const ArrayType SAMPLE2Q = {3, 3, 6, 4, 5};
const ArrayType SAMPLE3Q = {1, 1, 1, 3, 5};


THE_BENCHMARK(CountSpecialQuestions, SAMPLE1Q);

SIMPLE_TEST(CountSpecialQuestions, TestSAMPLE1, 1, SAMPLE1Q);
SIMPLE_TEST(CountSpecialQuestions, TestSAMPLE2, 0, SAMPLE2Q);
SIMPLE_TEST(CountSpecialQuestions, TestSAMPLE3, 4, SAMPLE3Q);


const ArrayType SAMPLE1S = {1, 2, 3, 4};
const ArrayType SAMPLE2S = {3, 1, 3, 4, 3};


THE_BENCHMARK(CountTwoSumsSingleUse, SAMPLE1S, 5);

SIMPLE_TEST(CountTwoSumsSingleUse, TestSAMPLE1, 2, SAMPLE1S, 5);
SIMPLE_TEST(CountTwoSumsSingleUse, TestSAMPLE2, 1, SAMPLE2S, 6);


const ArrayType SAMPLE1N = {3, 5, 6, 7};
const ArrayType SAMPLE2N = {3, 3, 6, 8};
const ArrayType SAMPLE3N = {2, 3, 3, 4, 6, 7};


THE_BENCHMARK(NumberSubsequences, SAMPLE1N, 9);

SIMPLE_TEST(NumberSubsequences, TestSAMPLE1, 4, SAMPLE1N, 9);
SIMPLE_TEST(NumberSubsequences, TestSAMPLE2, 6, SAMPLE2N, 10);
SIMPLE_TEST(NumberSubsequences, TestSAMPLE3, 61, SAMPLE3N, 12);
