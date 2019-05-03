#include "singly_linked_list.h"
#include "middle_of_singly_linked_list.h"


namespace {

/** Find middle of singly linked list Recursively
 *
 * @reference   https://www.geeksforgeeks.org/find-middle-singly-linked-list-recursively/
 */
std::forward_list<int>::const_iterator GetMiddle_Recursive(
    const std::forward_list<int>::const_iterator cbegin,
    const std::forward_list<int>::const_iterator cend,
    std::forward_list<int>::size_type &n) {

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
auto GetMiddle_Recursive(const std::forward_list<int> &l) {
    assert(not l.empty());
    std::forward_list<int>::size_type n = 0;
    return *GetMiddle_Recursive(l.cbegin(), l.end(), n);
}

const std::vector<int> SINGLE_ARRAY = {1};
const std::vector<int> EVEN_ARRAY = {1, 3};
const std::vector<int> ODD_ARRAY = {1, 2, 3};
const std::vector<int> SAMPLE_ARRAY = {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


auto testGetMid_Size(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMid_Size();
}


auto testGetMid_TwoPointers(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMid_TwoPointers();
}


auto testGetMid_Odd(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMid_Odd();
}


auto testGetBeforeMiddle_TwoPointersSTL(const std::vector<int> &array) {
    std::forward_list<int> l{array.cbegin(), array.cend()};
    auto before_mid = GetBeforeMiddle_TwoPointersSTL(l.cbefore_begin(), l.cend());
    return *(++before_mid);
}


auto testGetMiddle_Recursive(const std::vector<int> &array) {
    std::forward_list<int> l{array.cbegin(), array.cend()};
    return GetMiddle_Recursive(l);
}


/** Insert node into the middle of the linked list
 *
 * @reference   https://www.geeksforgeeks.org/insert-node-middle-linked-list/
 */


/** Delete middle of linked list
 *
 * @reference   https://www.geeksforgeeks.org/delete-middle-of-linked-list/
 */

}//namespace


SIMPLE_BENCHMARK(testGetMid_Size, SAMPLE_ARRAY);

SIMPLE_TEST(testGetMid_Size, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMid_Size, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMid_Size, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMid_Size, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testGetMid_TwoPointers, SAMPLE_ARRAY);

SIMPLE_TEST(testGetMid_TwoPointers, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2],
            SINGLE_ARRAY);
SIMPLE_TEST(testGetMid_TwoPointers, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMid_TwoPointers, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMid_TwoPointers, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2],
            SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testGetMid_Odd, SAMPLE_ARRAY);

SIMPLE_TEST(testGetMid_Odd, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMid_Odd, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMid_Odd, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMid_Odd, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testGetBeforeMiddle_TwoPointersSTL, SAMPLE_ARRAY);

SIMPLE_TEST(testGetBeforeMiddle_TwoPointersSTL, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2],
            SINGLE_ARRAY);
SIMPLE_TEST(testGetBeforeMiddle_TwoPointersSTL, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2],
            EVEN_ARRAY);
SIMPLE_TEST(testGetBeforeMiddle_TwoPointersSTL, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2],
            ODD_ARRAY);
SIMPLE_TEST(testGetBeforeMiddle_TwoPointersSTL, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2],
            SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testGetMiddle_Recursive, SAMPLE_ARRAY);

SIMPLE_TEST(testGetMiddle_Recursive, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2],
            SINGLE_ARRAY);
SIMPLE_TEST(testGetMiddle_Recursive, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMiddle_Recursive, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMiddle_Recursive, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2],
            SAMPLE_ARRAY);
