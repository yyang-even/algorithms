#include "singly_list/singly_linked_list.h"
#include "middle_of_singly_linked_list.h"


namespace {

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


using InitializerType = std::initializer_list<ListType::value_type>;

const InitializerType SINGLE_ARRAY = {1};
const InitializerType EVEN_ARRAY = {1, 3};
const InitializerType ODD_ARRAY = {1, 2, 3};
const InitializerType SAMPLE_ARRAY = {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


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
    auto l = ContainerCast<ListType>(std::move(array));
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

}//namespace


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
