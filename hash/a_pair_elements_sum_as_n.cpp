#include "common_header.h"

#include "a_pair_elements_sum_as_n.h"

#include "data_structure/tree/binary_tree/binary_tree_traversals.h"
#include "data_structure/tree/binary_tree/BST/binary_search_tree.h"


namespace {

template <std::size_t N>
using ArrayType = std::array<int, N>;
using OutputType = std::vector<bool>;
using OperationArrayType = std::vector<std::pair<bool, int>>;

/** Given an array A[] and a number x, check for pair in A[] with sum as x
 *
 * @reference   https://www.geeksforgeeks.org/given-an-array-a-and-a-number-x-check-for-pair-in-a-with-sum-as-x/
 *
 * Given an array A[] of n numbers and another number x, determines whether or not there
 * exist two elements in A whose sum is exactly x.
 *
 * @reference   Two Sum
 *              https://leetcode.com/problems/two-sum/
 *
 * Given an array of integers nums and an integer target, return indices of the two
 * numbers such that they add up to target. You may assume that each input would have
 * exactly one solution, and you may not use the same element twice. You can return
 * the answer in any order.
 *
 * @complexity: O(n)
 */
template <typename ArrayType>
inline constexpr auto
HasPairOfElementsSumAsN_Hashmap(const ArrayType &values, const int target) {
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
 * Given a sorted doubly linked list of positive distinct elements, the task is to find
 * pairs in doubly linked list whose sum is equal to given value x, without using any
 * extra space?
 *
 * @reference   Two Sum II - Input array is sorted
 *              https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 *
 * Given an array of integers numbers that is already sorted in non-decreasing order,
 * find two numbers such that they add up to a specific target number. Return the
 * indices of the two numbers (1-indexed) as an integer array answer of size 2, where
 * 1 <= answer[0] < answer[1] <= numbers.length. The tests are generated such that there
 * is exactly one solution. You may not use the same element twice.
 */
template <typename Container>
constexpr auto
HasPairOfElementsSumAsN_TwoPointers(const Container &values, const int target) {
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

template <std::size_t N>
inline constexpr auto HasPairOfElementsSumAsN_Sort(ArrayType<N> values,
                                                   const int target) {
    if (values.empty()) {
        return false;
    }
    std::sort(values.begin(), values.end());
    return HasPairOfElementsSumAsN_TwoPointers(values, target);
}


/** Count pairs with given sum
 *
 * @reference   https://www.geeksforgeeks.org/count-pairs-with-given-sum/
 * @reference   Count pairs with given sum | Set 2
 *              https://www.geeksforgeeks.org/count-pairs-with-given-sum-set-2/
 *
 * Given an array of integers, and a number 'sum', find the number of pairs of integers
 * in the array whose sum is equal to 'sum'.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.12.
 */


/**
 * @reference   Two Sum III - Data structure design
 *              https://aaronice.gitbook.io/lintcode/high_frequency/two-sum-iii-data-structure-design
 *
 * Design and implement a TwoSum class. It should support the following operations:
 *  add- Add the number to an internal data structure.
 *  find- Find if there exists any pair of numbers which sum is equal to the value.
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
    for (const auto [is_add, value] : operations) {
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
 * Given the root of a Binary Search Tree and a target number k, return true if there
 * exist two elements in the BST such that their sum is equal to the given target.
 */
inline auto
HasPairOfElementsSumAsN_BST_Inorder(const BinaryTree::Node::PointerType root,
                                    const int target) {
    BinaryTree::ArrayType inorder;
    InorderTraversal_Recursive(root, inorder);
    return HasPairOfElementsSumAsN_TwoPointers(inorder, target);
}


inline auto
HasPairOfElementsSumAsN_BST_Hash(const BinaryTree::Node::PointerType node,
                                 const int target, std::unordered_set<int> &hash) {
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

inline auto
HasPairOfElementsSumAsN_BST_Hash(const BinaryTree::Node::PointerType root,
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
auto
HasPairOfElementsSumAsN_BST_TwoPointers(const BinaryTree::Node::PointerType root,
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

}//namespace


static constexpr ArrayType<0> VALUES1 = {};
static constexpr ArrayType<1> VALUES2 = {1};
static constexpr ArrayType<8> VALUES3 = {1, 4, 45, 6, 10, -8, 9, 4};


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


const auto SAMPLE1T = MakeTheSampleBST().GetRoot();


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
