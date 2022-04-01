#include "singly_linked_list.h"
#include "middle_of_singly_linked_list.h"


namespace {

using ArrayType = std::vector<int>;
using ListType = std::forward_list<int>;

/** Find middle of singly linked list Recursively
 *
 * @reference   https://www.geeksforgeeks.org/find-middle-singly-linked-list-recursively/
 */
ListType::const_iterator GetMiddle_Recursive(
    const ListType::const_iterator cbegin,
    const ListType::const_iterator cend,
    ListType::size_type &n) {

    const auto next = std::next(cbegin);
    if (cbegin == cend or next == cend) {
        n /= 2;
    } else {
        const auto mid = GetMiddle_Recursive(next, cend, ++n);
        if (--n) {
            return mid;
        }
    }
    return cbegin;
}

inline auto GetMiddle_Recursive(const ListType &l) {
    assert(not l.empty());
    ListType::size_type n = 0;
    return *GetMiddle_Recursive(l.cbegin(), l.end(), n);
}


inline auto testGetMid_Size(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMid_Size();
}


inline auto testGetMid_TwoPointers(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMid_TwoPointers();
}


inline auto testGetMid_Odd(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMid_Odd();
}


inline auto testGetBeforeMiddle_TwoPointersSTL(std::vector<int> array) {
    const auto l = ContainerCast<ListType>(std::move(array));
    auto before_mid = GetBeforeMiddle_TwoPointersSTL(l.cbefore_begin(), l.cend());
    return *(++before_mid);
}


/** Insert node into the middle of the linked list
 *
 * @reference   https://www.geeksforgeeks.org/insert-node-middle-linked-list/
 */


/** Delete middle of linked list
 *
 * @reference   https://www.geeksforgeeks.org/delete-middle-of-linked-list/
 */


inline auto GetMiddle(const std::vector<int> &array) {
    return array[array.size() / 2];
}


/**
 * @reference   Reorder List
 *              https://leetcode.com/problems/reorder-list/
 *
 * You are given the head of a singly linked-list. The list can be represented as:
 *  L0 → L1 → … → Ln - 1 → Ln
 * Reorder the list to be on the following form:
 *  L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
 * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
 */
template<typename Pointer>
static inline constexpr auto GetBeforeMidNode(const Pointer head) {
    assert(head);

    auto fast_ptr = head->next;
    auto slow_ptr = head;

    while (fast_ptr and fast_ptr->next) {
        fast_ptr = fast_ptr->next->next;
        slow_ptr = slow_ptr->next;
    }

    return slow_ptr;
}

auto Merge(const SinglyLinkedList::Node::PointerType one_head,
           const SinglyLinkedList::Node::PointerType another_head) {
    auto one = one_head;
    auto another = another_head;

    while (one != nullptr and another != nullptr) {
        const auto one_next = one->next;
        const auto another_next = another->next;
        another->next = one->next;
        one->next = another;
        one = one_next;
        another = another_next;
    }

    return one_head;
}

auto ReorderList(const SinglyLinkedList::Node::PointerType head) {
    const auto before_mid = GetBeforeMidNode(head);
    auto second_head = before_mid->next;
    before_mid->next = nullptr;

    second_head = Reverse(second_head);
    return Merge(head, second_head);
}

inline auto testReorderList(const ArrayType &array) {
    return TestHelper(ReorderList, array);
}

}//namespace


using InitializerType = std::initializer_list<ListType::value_type>;

constexpr InitializerType SINGLE_ARRAY = {1};
constexpr InitializerType EVEN_ARRAY = {1, 3};
constexpr InitializerType ODD_ARRAY = {1, 2, 3};
constexpr InitializerType SAMPLE_ARRAY = {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


THE_BENCHMARK(testGetMid_Size, SAMPLE_ARRAY);

MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Size, TestSingle, SINGLE_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Size, TestEven, EVEN_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Size, TestOdd, ODD_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Size, TestSample, SAMPLE_ARRAY);


THE_BENCHMARK(testGetMid_TwoPointers, SAMPLE_ARRAY);

MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_TwoPointers, TestSingle, SINGLE_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_TwoPointers, TestEven, EVEN_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_TwoPointers, TestOdd, ODD_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_TwoPointers, TestSample, SAMPLE_ARRAY);


THE_BENCHMARK(testGetMid_Odd, SAMPLE_ARRAY);

MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Odd, TestSingle, SINGLE_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Odd, TestEven, EVEN_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Odd, TestOdd, ODD_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetMid_Odd, TestSample, SAMPLE_ARRAY);


THE_BENCHMARK(testGetBeforeMiddle_TwoPointersSTL, SAMPLE_ARRAY);

MUTUAL_SIMPLE_TEST(GetMiddle, testGetBeforeMiddle_TwoPointersSTL, TestSingle,
                   SINGLE_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetBeforeMiddle_TwoPointersSTL, TestEven, EVEN_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetBeforeMiddle_TwoPointersSTL, TestOdd, ODD_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, testGetBeforeMiddle_TwoPointersSTL, TestSample,
                   SAMPLE_ARRAY);


THE_BENCHMARK(GetMiddle_Recursive, SAMPLE_ARRAY);

MUTUAL_SIMPLE_TEST(GetMiddle, GetMiddle_Recursive, TestSingle, SINGLE_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, GetMiddle_Recursive, TestEven, EVEN_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, GetMiddle_Recursive, TestOdd, ODD_ARRAY);
MUTUAL_SIMPLE_TEST(GetMiddle, GetMiddle_Recursive, TestSample, SAMPLE_ARRAY);


const ArrayType SAMPLE1 = {1, 2, 3, 4};
const ArrayType EXPECTED1 = {1, 4, 2, 3};

const ArrayType SAMPLE2 = {1, 2, 3, 4, 5};
const ArrayType EXPECTED2 = {1, 5, 2, 4, 3};


THE_BENCHMARK(testReorderList, SINGLE_ARRAY);

SIMPLE_TEST(testReorderList, TestSample1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(testReorderList, TestSample2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(testReorderList, TestSample3, SINGLE_ARRAY, SINGLE_ARRAY);
SIMPLE_TEST(testReorderList, TestSample4, EVEN_ARRAY, EVEN_ARRAY);
