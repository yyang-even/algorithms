#include "common_header.h"


namespace {

/** Delete all occurrences of a given key in a linked list
 *
 * @reference   https://www.geeksforgeeks.org/delete-occurrences-given-key-linked-list/
 * @reference   Delete multiple occurrences of key in Linked list using double pointer
 *              https://www.geeksforgeeks.org/delete-multiple-occurrences-of-key-in-linked-list-using-double-pointer/
 */
auto DeleteWithKey_Singly(std::forward_list<int> single_list,
                          const std::forward_list<int>::value_type key) {
    auto iter = single_list.cbegin();
    for (auto before_iter = single_list.cbefore_begin(); iter != single_list.cend();) {
        if (*iter == key) {
            iter = single_list.erase_after(before_iter);
        } else {
            before_iter = iter++;
        }
    }

    return single_list;
}


/**
 * @reference   Delete all occurrences of a given key in a doubly linked list
 *              https://www.geeksforgeeks.org/delete-occurrences-given-key-doubly-linked-list/
 */
auto DeleteWithKey_Doubly(std::list<int> doubly_list,
                          const std::list<int>::value_type key) {
    for (auto iter = doubly_list.cbegin(); iter != doubly_list.cend();) {
        if (*iter == key) {
            iter = doubly_list.erase(iter);
        } else {
            ++iter;
        }
    }

    return doubly_list;
}


template <typename ListType, typename DeleteFunc>
inline constexpr auto testDeleteWithKey(const ListType &list,
                                        const typename ListType::value_type key,
                                        const DeleteFunc delete_func) {
    auto expected = list;
    expected.remove(key);

    const auto key_deleted_list = delete_func(list, key);
    return expected == key_deleted_list;
}


/** Write a function that counts the number of times a given int occurs in a Linked List
 *
 * @reference   https://www.geeksforgeeks.org/write-a-function-that-counts-the-number-of-times-a-given-int-occurs-in-a-linked-list/
 * @reference   Count of Prime Nodes of a Singly Linked List
 *              https://www.geeksforgeeks.org/count-of-prime-nodes-of-a-singly-linked-list/
 *
 * Given a singly linked list containing N nodes, the task is to find the total count of
 * prime numbers.
 */


/** Delete all the even nodes from a Doubly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/delete-all-the-even-nodes-from-a-doubly-linked-list/
 * @reference   Delete all the even nodes of a Circular Linked List
 *              https://www.geeksforgeeks.org/delete-all-the-even-nodes-of-a-circular-linked-list/
 *
 * Given a doubly linked list containing N nodes, the task is to delete all the even nodes from the list.
 *
 * @reference   Remove every k-th node of the linked list
 *              https://www.geeksforgeeks.org/remove-every-k-th-node-linked-list/
 *
 * Given a singly linked list, Your task is to remove every K-th node of the linked list.
 * Assume that K is always less than or equal to length of Linked List.
 */


/** Delete all the nodes from the doubly linked list that are greater than a given value
 *
 * @reference   https://www.geeksforgeeks.org/delete-all-the-nodes-from-the-doubly-linked-list-that-are-greater-than-a-given-value/
 * @reference   Delete all the nodes from the list that are greater than x
 *              https://www.geeksforgeeks.org/delete-nodes-list-greater-x/
 *
 * Given a doubly linked list containing N nodes and a number X, the task is to delete
 * all the nodes from the list that are greater than the given value X.
 *
 * @reference   Delete all the nodes from the list which are less than K
 *              https://www.geeksforgeeks.org/delete-all-the-nodes-from-the-list-which-are-less-than-k/
 * @reference   Delete all the nodes from a doubly linked list that are smaller than a given value
 *              https://www.geeksforgeeks.org/delete-all-the-nodes-from-a-doubly-linked-list-that-are-smaller-than-a-given-value/
 *
 * Given a Linked List and a key K. The task is to write a program to delete all the
 * nodes from the list that are lesser than the key K.
 */


/** Delete all Prime Nodes from a Singly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/delete-all-prime-nodes-from-a-singly-linked-list/
 * @reference   Delete all Non-Prime Nodes from a Singly Linked List
 *              https://www.geeksforgeeks.org/delete-all-non-prime-nodes-from-a-singly-linked-list/
 * @reference   Delete all Prime Nodes from a Doubly Linked List
 *              https://www.geeksforgeeks.org/delete-all-prime-nodes-from-a-doubly-linked-list/
 * @reference   Delete all Prime Nodes from a Circular Singly Linked List
 *              https://www.geeksforgeeks.org/delete-all-prime-nodes-from-a-circular-singly-linked-list/
 *
 * Given a singly linked list containing N nodes, the task is to delete all nodes from
 * the list which are prime.
 */


/** Delete all the nodes from the list which are divisible by any given number K
 *
 * @reference   https://www.geeksforgeeks.org/delete-all-the-nodes-from-the-list-which-are-divisible-by-any-given-number-k/
 * @reference   Delete all nodes from the doubly linked list which are divisible by K
 *              https://www.geeksforgeeks.org/delete-all-nodes-from-the-doubly-linked-list-which-are-divisible-by-k/
 *
 * Given a Linked List and a key K. The task is to write a program to delete all the
 * nodes from the list that are divisible by K.
 */

}//namespace


const std::forward_list<int> SAMPLE_SINGLY_LIST = {2, 2, 1, 8, 2, 3, 2, 7};


SIMPLE_BENCHMARK(testDeleteWithKey, Sample1, SAMPLE_SINGLY_LIST,
                 2, &DeleteWithKey_Singly);

SIMPLE_TEST(testDeleteWithKey, TestSinglySample1, true, SAMPLE_SINGLY_LIST, 2,
            &DeleteWithKey_Singly);
SIMPLE_TEST(testDeleteWithKey, TestSinglySample2, true, SAMPLE_SINGLY_LIST, 1,
            &DeleteWithKey_Singly);
SIMPLE_TEST(testDeleteWithKey, TestSinglySample3, true, SAMPLE_SINGLY_LIST, 7,
            &DeleteWithKey_Singly);


const std::list<int> SAMPLE_DOUBLY_LIST = {2, 2, 1, 8, 2, 3, 2, 7};


SIMPLE_BENCHMARK(testDeleteWithKey, Sample2, SAMPLE_DOUBLY_LIST,
                 2, &DeleteWithKey_Doubly);

SIMPLE_TEST(testDeleteWithKey, TestDoublySample1, true, SAMPLE_DOUBLY_LIST, 2,
            &DeleteWithKey_Doubly);
SIMPLE_TEST(testDeleteWithKey, TestDoublySample2, true, SAMPLE_DOUBLY_LIST, 1,
            &DeleteWithKey_Doubly);
SIMPLE_TEST(testDeleteWithKey, TestDoublySample3, true, SAMPLE_DOUBLY_LIST, 7,
            &DeleteWithKey_Doubly);
