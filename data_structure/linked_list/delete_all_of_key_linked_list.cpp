#include "common_header.h"

#include <forward_list>


namespace {

/** Delete all occurrences of a given key in a linked list
 *
 * @reference   https://www.geeksforgeeks.org/delete-occurrences-given-key-linked-list/
 * @reference   Delete multiple occurrences of key in Linked list using double pointer
 *              https://www.geeksforgeeks.org/delete-multiple-occurrences-of-key-in-linked-list-using-double-pointer/
 */
auto DeleteWithKey(std::forward_list<int> single_list, std::forward_list<int>::value_type key) {
    auto iter = single_list.begin();
    for (auto before_iter = single_list.before_begin(); iter != single_list.end();) {
        if (*iter == key) {
            iter = single_list.erase_after(before_iter);
        } else {
            before_iter = iter++;
        }
    }

    return single_list;
}

auto testDeleteWithKey(const std::forward_list<int> &single_list,
                       std::forward_list<int>::value_type key) {
    auto expected = single_list;
    expected.remove(key);

    const auto key_deleted_list = DeleteWithKey(single_list, key);
    return expected == key_deleted_list;
}


/** Write a function that counts the number of times a given int occurs in a Linked List
 *
 * @reference   https://www.geeksforgeeks.org/write-a-function-that-counts-the-number-of-times-a-given-int-occurs-in-a-linked-list/
 */

}//namespace


const std::forward_list<int> SAMPLE_LIST = {2, 2, 1, 8, 2, 3, 2, 7};


SIMPLE_BENCHMARK(testDeleteWithKey, SAMPLE_LIST, 2);

SIMPLE_TEST(testDeleteWithKey, TestSample1, true, SAMPLE_LIST, 2);
SIMPLE_TEST(testDeleteWithKey, TestSample2, true, SAMPLE_LIST, 1);
SIMPLE_TEST(testDeleteWithKey, TestSample3, true, SAMPLE_LIST, 7);
