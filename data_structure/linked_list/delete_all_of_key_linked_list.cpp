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


/** Write a function that counts the number of times a given int occurs in a Linked List
 *
 * @reference   https://www.geeksforgeeks.org/write-a-function-that-counts-the-number-of-times-a-given-int-occurs-in-a-linked-list/
 */


/** Delete all occurrences of a given key in a doubly linked list
 *
 * @reference   https://www.geeksforgeeks.org/delete-occurrences-given-key-doubly-linked-list/
 */
auto DeleteWithKey_Doubly(std::list<int> doubly_list, const std::list<int>::value_type key) {
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
auto testDeleteWithKey(const ListType &list, const typename ListType::value_type key,
                       const DeleteFunc delete_func) {
    auto expected = list;
    expected.remove(key);

    const auto key_deleted_list = delete_func(list, key);
    return expected == key_deleted_list;
}

}//namespace


const std::forward_list<int> SAMPLE_SINGLY_LIST = {2, 2, 1, 8, 2, 3, 2, 7};


SIMPLE_BENCHMARK(testDeleteWithKey, SAMPLE_SINGLY_LIST, 2, &DeleteWithKey_Singly);

SIMPLE_TEST(testDeleteWithKey, TestSinglySample1, true, SAMPLE_SINGLY_LIST, 2,
            &DeleteWithKey_Singly);
SIMPLE_TEST(testDeleteWithKey, TestSinglySample2, true, SAMPLE_SINGLY_LIST, 1,
            &DeleteWithKey_Singly);
SIMPLE_TEST(testDeleteWithKey, TestSinglySample3, true, SAMPLE_SINGLY_LIST, 7,
            &DeleteWithKey_Singly);


const std::list<int> SAMPLE_DOUBLY_LIST = {2, 2, 1, 8, 2, 3, 2, 7};


SIMPLE_BENCHMARK(testDeleteWithKey, SAMPLE_DOUBLY_LIST, 2, &DeleteWithKey_Doubly);

SIMPLE_TEST(testDeleteWithKey, TestDoublySample1, true, SAMPLE_DOUBLY_LIST, 2,
            &DeleteWithKey_Doubly);
SIMPLE_TEST(testDeleteWithKey, TestDoublySample2, true, SAMPLE_DOUBLY_LIST, 1,
            &DeleteWithKey_Doubly);
SIMPLE_TEST(testDeleteWithKey, TestDoublySample3, true, SAMPLE_DOUBLY_LIST, 7,
            &DeleteWithKey_Doubly);
