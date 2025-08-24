#include "common_header.h"

#include "doubly_list/doubly_circular_linked_list.h"
#include "doubly_list/doubly_linked_list.h"
#include "singly_list/singly_circular_linked_list.h"
#include "singly_list/singly_linked_list.h"


namespace {

using ArrayType = std::vector<int>;

const ArrayType SAMPLE_ARRAY = {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


SinglyLinkedList::Node::PointerType
DetectLoop_Hash(const SinglyLinkedList::Node::PointerType head) {
    std::unordered_set<SinglyLinkedList::Node *> visited_nodes;

    for (auto current = head; current; current = current->next) {
        if (not visited_nodes.insert(current.get()).second) {
            return current;
        }
    }

    return nullptr;
}

inline auto testDetectLoop_Hash_SinglyList() {
    SinglyLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_Hash(list.GetHead()) == nullptr;
}

inline auto testDetectLoop_Hash_SinglyCircular() {
    SinglyCircularLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_Hash(list.GetHead()) == list.GetHead();
}

inline auto testDetectLoop_Hash_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_Hash(list.GetHead()) == list.At(index);
}


/**
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 4.
 * @reference   Detect loop in a linked list
 *              https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/
 * @reference   How does Floyd’s slow and fast pointers approach work?
 *              https://www.geeksforgeeks.org/how-does-floyds-slow-and-fast-pointers-approach-work/
 * @reference   Finding a Loop in a Singly Linked List
 *              https://blog.ostermiller.org/find-loop-singly-linked-list
 * @reference   Linked List Cycle
 *              https://leetcode.com/problems/linked-list-cycle/
 *
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * There is a cycle in a linked list if there is some node in the list that can be reached again by
 * continuously following the next pointer. Internally, pos is used to denote the index of the node that
 * tail's next pointer is connected to. Note that pos is not passed as a parameter.
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 *
 * This solution is "Floyd's Cycle-Finding Algorithm" as published in "Non-deterministic Algorithms" by
 * Robert W. Floyd in 1967. It is also called "The Tortoise and the Hare Algorithm".
 *
 * @reference   Find first node of loop in a linked list
 *              https://www.geeksforgeeks.org/find-first-node-of-loop-in-a-linked-list/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 2.6.
 * @reference   Linked List Cycle II
 *              https://leetcode.com/problems/linked-list-cycle-ii/
 *
 * Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return
 * null.
 * There is a cycle in a linked list if there is some node in the list that can be reached again by
 * continuously following the next pointer. Internally, pos is used to denote the index of the node that
 * tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not
 * passed as a parameter.
 * Do not modify the linked list.
 *
 * @reference   Detect and Remove Loop in a Linked List
 *              https://www.geeksforgeeks.org/detect-and-remove-loop-in-a-linked-list/
 *
 * Write a function detectAndRemoveLoop() that checks whether a given Linked List contains loop and if
 * loop is present then removes the loop and returns true. If the list doesn't contain loop then it
 * returns false.
 *
 * @reference   Find length of loop in linked list
 *              https://www.geeksforgeeks.org/find-length-of-loop-in-linked-list/
 *
 * Write a function detectAndCountLoop() that checks whether a given Linked List contains loop and if
 * loop is present then returns count of nodes in loop.
 */
auto DetectLoop_FloydsCycleFinding(const SinglyLinkedList::Node::PointerType head,
                                   std::size_t *loop_length = nullptr,
                                   SinglyLinkedList::Node::PointerType *first_node = nullptr,
                                   SinglyLinkedList::Node::PointerType *last_node = nullptr) {
    auto slow_ptr = head;
    auto fast_ptr = head;

    while (fast_ptr and fast_ptr->next) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;

        if (slow_ptr == fast_ptr) {
            if (loop_length) {
                *loop_length = 0;
                do {
                    ++(*loop_length);
                    slow_ptr = slow_ptr->next;
                } while (slow_ptr != fast_ptr);
            }
            if (first_node or last_node) {
                SinglyLinkedList::Node::PointerType prev = nullptr;
                for (slow_ptr = head; slow_ptr != fast_ptr;
                     slow_ptr = slow_ptr->next, fast_ptr = fast_ptr->next) {
                    prev = slow_ptr;
                }
                if (first_node) {
                    *first_node = slow_ptr;
                }
                if (last_node) {
                    if (not prev) {
                        for (prev = head; prev->next != head; prev = prev->next)
                            ;
                    }
                    *last_node = prev;
                }
            }
            return true;
        }
    }

    return false;
}

inline auto testDetectLoop_FloydsCycleFinding_SinglyList() {
    SinglyLinkedList list {SAMPLE_ARRAY};
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    SinglyLinkedList::Node::PointerType last_node = nullptr;
    return not(
        DetectLoop_FloydsCycleFinding(list.GetHead(), &loop_length, &first_node, &last_node) or
        loop_length or first_node or last_node);
}

inline auto testDetectLoop_FloydsCycleFinding_SinglyCircular() {
    SinglyCircularLinkedList list {SAMPLE_ARRAY};
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    SinglyLinkedList::Node::PointerType last_node = nullptr;
    return DetectLoop_FloydsCycleFinding(
               list.GetHead(), &loop_length, &first_node, &last_node) and
           loop_length == SAMPLE_ARRAY.size() and first_node == list.GetHead() and
           last_node->next == first_node;
}

inline auto testDetectLoop_FloydsCycleFinding_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    std::size_t loop_length = 0;
    SinglyLinkedList::Node::PointerType first_node = nullptr;
    SinglyLinkedList::Node::PointerType last_node = nullptr;
    return DetectLoop_FloydsCycleFinding(
               list.GetHead(), &loop_length, &first_node, &last_node) and
           loop_length == (SAMPLE_ARRAY.size() - index) and first_node == list.At(index) and
           last_node->next == first_node;
}


SinglyLinkedList::Node::PointerType
DetectLoop_NextFlag(const SinglyLinkedList::Node::PointerType head) {
    const auto temp_node = std::make_shared<SinglyLinkedList::Node>();

    for (auto current = head; current;) {
        if (current->next == temp_node) {
            return current;
        } else {
            const auto next = current->next;
            current->next = temp_node;
            current = next;
        }
    }

    return nullptr;
}

inline auto testDetectLoop_NextFlag_SinglyList() {
    SinglyLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_NextFlag(list.GetHead()) == nullptr;
}

inline auto testDetectLoop_NextFlag_SinglyCircular() {
    SinglyCircularLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_NextFlag(list.GetHead()) == list.GetHead();
}

inline auto testDetectLoop_NextFlag_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_NextFlag(list.GetHead()) == list.At(index);
}


auto DetectLoop_DoublyList(const DoublyLinkedList::Node::PointerType head) {
    DoublyLinkedList::Node::PointerType prev = nullptr;

    for (auto current = head; current; current = current->Next()) {
        if (prev != current->Prev()) {
            return true;
        }
        prev = current;
    }

    return false;
}

inline auto testDetectLoop_DoublyList() {
    DoublyLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_DoublyList(list.GetHead());
}

inline auto testDetectLoop_DoublyCircular() {
    DoublyCircularLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_DoublyList(list.GetHead());
}


auto DetectLoop_Reverse(const SinglyLinkedList::Node::PointerType head) {
    auto current = head;
    SinglyLinkedList::Node::PointerType prev = nullptr;

    while (current) {
        const auto next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev == head;
}

inline auto testDetectLoop_Reverse_SinglyList() {
    SinglyLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_Reverse(list.GetHead());
}

inline auto testDetectLoop_Reverse_SinglyCircular() {
    SinglyCircularLinkedList list {SAMPLE_ARRAY};
    return DetectLoop_Reverse(list.GetHead());
}

inline auto testDetectLoop_Reverse_SinglyMakeLoop(const std::size_t index) {
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.MakeLoopAt(index);
    return DetectLoop_Reverse(list.GetHead());
}


/**
 *
 * @reference   Find the only repetitive element between 1 to n-1
 *              https://www.geeksforgeeks.org/find-repetitive-element-1-n-1/
 *
 * We are given an array arr[] of size n. Numbers are from 1 to (n-1) in random order.
 * The array has only one repetitive element. We need to find the repetitive element.
 *
 * @tags    #hash-table #bit-tricks #index-marking
 */
inline auto FindTheOnlyRepeatingElement_Sum(const ArrayType &elements) {
    const auto sum = std::accumulate(elements.cbegin(), elements.cend(), 0u);
    return sum - (elements.size() - 1) * elements.size() / 2;
}


auto FindTheOnlyRepeatingElement_Hash(const ArrayType &elements) {
    std::vector<bool> counters(elements.size(), false);
    for (const auto elem : elements) {
        if (counters[elem]) {
            return elem;
        }
        counters[elem] = true;
    }

    return 0;
}


auto FindTheOnlyRepeatingElement_Xor(const ArrayType &elements) {
    ArrayType::value_type result = 0;
    for (unsigned i = 0; i < elements.size() - 1; ++i) {
        result ^= ((i + 1) ^ elements[i]);
    }

    return result ^ elements.back();
}


auto FindTheOnlyRepeatingElement_InPlace(ArrayType elements) {
    for (const auto elem : elements) {
        const auto absolute_element = std::abs(elem);
        auto &counter = elements[absolute_element];
        if (counter < 0) {
            return absolute_element;
        }
        counter = -counter;
    }

    return 0;
}


/**
 * @reference   Find the only repeating element in a sorted array of size n
 *              https://www.geeksforgeeks.org/find-repeating-element-sorted-array-size-n/
 *
 * Given a sorted array of n elements containing elements in range from 1 to n-1 i.e.
 * One element occurs twice, the task is to find the repeating element in an array.
 *
 * @tags    #binary-search
 */
ArrayType::value_type FindTheOnlyRepeatingElement_Sorted_BinarySearch(
    const ArrayType &elements, const ArrayType::size_type low, const ArrayType::size_type high) {
    if (low > high) {
        return 0;
    }

    const auto mid = (low + high) / 2;
    if (elements[mid] - mid != 1) {
        if (mid > 0 and elements[mid] == elements[mid - 1]) {
            return mid;
        }
        return FindTheOnlyRepeatingElement_Sorted_BinarySearch(elements, low, mid - 1);
    }

    return FindTheOnlyRepeatingElement_Sorted_BinarySearch(elements, mid + 1, high);
}

inline auto FindTheOnlyRepeatingElement_Sorted_BinarySearch(const ArrayType &elements) {
    return FindTheOnlyRepeatingElement_Sorted_BinarySearch(elements, 0, elements.size() - 1);
}


/**
 * @reference   Find duplicate in an array in O(n) and by using O(1) extra space
 *              https://www.geeksforgeeks.org/duplicates-array-using-o1-extra-space-set-3/
 *
 * Given an array arr[] containing n + 1 integers where each integer is between 1 and n (inclusive).
 * There is only one duplicate element, find the duplicate element in O(n) time complexity and O(1)
 * space.
 *
 * @reference   Find duplicates in constant array with elements 0 to N-1 in O(1) space
 *              https://www.geeksforgeeks.org/find-duplicates-constant-array-elements-0-n-1-o1-space/
 *
 * Given a constant array of n elements which contains elements from 0 to n-1, with any of these numbers
 * appearing any number of times. Find any one of these repeating numbers in O(n) and using only
 * constant memory space.
 */
auto FindTheDuplicate_FloydsCycleFinding(const ArrayType &values) {
    auto slow_ptr = values.front();
    auto fast_ptr = values.front();

    do {
        slow_ptr = values[slow_ptr];
        fast_ptr = values[values[fast_ptr]];
    } while (slow_ptr != fast_ptr);

    slow_ptr = values.front();
    while (slow_ptr != fast_ptr) {
        slow_ptr = values[slow_ptr];
        fast_ptr = values[fast_ptr];
    }

    return slow_ptr;
}


/**
 * @reference   Find the Duplicate Number
 *              https://leetcode.com/problems/find-the-duplicate-number/
 *
 * Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n]
 * inclusive.
 * There is only one repeated number in nums, return this repeated number.
 * You must solve the problem without modifying the array nums and uses only constant extra space.
 * Follow up:
 *  How can we prove that at least one duplicate number must exist in nums?
 *  Can you solve the problem in linear runtime complexity?
 */
auto FindTheDuplicate_Swap(ArrayType nums) {
    while (nums[0] != nums[nums[0]]) {
        std::swap(nums[0], nums[nums[0]]);
    }
    return nums[0];
}


auto FindTheDuplicate_BinarySearch(const ArrayType &nums) {
    int low = 1, high = nums.size();
    int duplicate = -1;
    while (low <= high) {
        const auto mid = (low + high) / 2;
        const auto count = std::count_if(nums.cbegin(), nums.cend(), [mid](const auto n) {
            return n <= mid;
        });
        if (count > mid) {
            duplicate = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return duplicate;
}


/**
 * @reference   Array Nesting
 *              https://leetcode.com/problems/array-nesting/
 *
 * You are given an integer array nums of length n where nums is a permutation of the numbers in the
 * range [0, n - 1]. You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... }
 * subjected to the following rule:
 *  The first element in s[k] starts with the selection of the element nums[k] of index = k.
 *  The next element in s[k] should be nums[nums[k]], and then nums[nums[nums[k]]], and so on.
 *  We stop adding right before a duplicate element occurs in s[k].
 * Return the longest length of a set s[k].
 */
auto LongestNestingArray(const ArrayType &nums) {
    std::vector visited(nums.size(), false);

    int result = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (not visited[i]) {
            int count = 0;
            for (auto j = i; not visited[j]; j = nums[j]) {
                ++count;
                visited[j] = true;
            }

            result = std::max(result, count);
        }
    }

    return result;
}

} //namespace


SIMPLE_BENCHMARK0(testDetectLoop_Hash_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_Hash_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_Hash_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_Hash_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_Hash_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_Hash_SinglyMakeLoop, TestSample3, true, SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK0(testDetectLoop_FloydsCycleFinding_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_FloydsCycleFinding_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_FloydsCycleFinding_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_FloydsCycleFinding_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_FloydsCycleFinding_SinglyMakeLoop,
            TestSample3,
            true,
            SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK0(testDetectLoop_NextFlag_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_NextFlag_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_NextFlag_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_NextFlag_SinglyList, TestSample, true);
SIMPLE_TEST0(testDetectLoop_NextFlag_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_NextFlag_SinglyMakeLoop, TestSample3, true, SAMPLE_ARRAY.size() - 1);


SIMPLE_BENCHMARK0(testDetectLoop_DoublyList);
SIMPLE_BENCHMARK0(testDetectLoop_DoublyCircular);

SIMPLE_TEST0(testDetectLoop_DoublyList, TestSample, false);
SIMPLE_TEST0(testDetectLoop_DoublyCircular, TestSample, true);


SIMPLE_BENCHMARK0(testDetectLoop_Reverse_SinglyList);
SIMPLE_BENCHMARK0(testDetectLoop_Reverse_SinglyCircular);
SIMPLE_BENCHMARK(testDetectLoop_Reverse_SinglyMakeLoop, Sample1, 3);

SIMPLE_TEST0(testDetectLoop_Reverse_SinglyList, TestSample, false);
SIMPLE_TEST0(testDetectLoop_Reverse_SinglyCircular, TestSample, true);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample1, true, 2);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample2, true, 3);
SIMPLE_TEST(testDetectLoop_Reverse_SinglyMakeLoop, TestSample3, true, SAMPLE_ARRAY.size() - 1);


const ArrayType SAMPLE1D = {1, 3, 2, 3, 4};
const ArrayType SAMPLE2D = {1, 5, 1, 2, 3, 4};
const ArrayType SAMPLE3D = {9, 8, 2, 6, 1, 8, 5, 3, 4, 7};
const ArrayType SAMPLE4D = {2, 2, 2, 2, 2};


THE_BENCHMARK(FindTheDuplicate_Swap, SAMPLE1D);

SIMPLE_TEST(FindTheDuplicate_Swap, TestSample1, 3, SAMPLE1D);
SIMPLE_TEST(FindTheDuplicate_Swap, TestSample2, 1, SAMPLE2D);
SIMPLE_TEST(FindTheDuplicate_Swap, TestSample3, 8, SAMPLE3D);
SIMPLE_TEST(FindTheDuplicate_Swap, TestSample4, 2, SAMPLE4D);


THE_BENCHMARK(FindTheDuplicate_BinarySearch, SAMPLE1D);

SIMPLE_TEST(FindTheDuplicate_BinarySearch, TestSample1, 3, SAMPLE1D);
SIMPLE_TEST(FindTheDuplicate_BinarySearch, TestSample2, 1, SAMPLE2D);
SIMPLE_TEST(FindTheDuplicate_BinarySearch, TestSample3, 8, SAMPLE3D);
SIMPLE_TEST(FindTheDuplicate_BinarySearch, TestSample4, 2, SAMPLE4D);


THE_BENCHMARK(FindTheDuplicate_FloydsCycleFinding, SAMPLE1D);

SIMPLE_TEST(FindTheDuplicate_FloydsCycleFinding, TestSample1, 3, SAMPLE1D);
SIMPLE_TEST(FindTheDuplicate_FloydsCycleFinding, TestSample2, 1, SAMPLE2D);
SIMPLE_TEST(FindTheDuplicate_FloydsCycleFinding, TestSample3, 8, SAMPLE3D);
SIMPLE_TEST(FindTheDuplicate_FloydsCycleFinding, TestSample4, 2, SAMPLE4D);


const ArrayType SAMPLE3 = {5, 4, 0, 3, 1, 6, 2};
const ArrayType SAMPLE4 = {0, 1, 2};


THE_BENCHMARK(LongestNestingArray, SAMPLE3);

SIMPLE_TEST(LongestNestingArray, TestSample3, 4, SAMPLE3);
SIMPLE_TEST(LongestNestingArray, TestSample4, 1, SAMPLE4);


THE_BENCHMARK(FindTheOnlyRepeatingElement_Sum, SAMPLE1D);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Sum, TestSample1, 3, SAMPLE1D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sum, TestSample2, 1, SAMPLE2D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sum, TestSample3, 8, SAMPLE3D);


THE_BENCHMARK(FindTheOnlyRepeatingElement_Hash, SAMPLE1D);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Hash, TestSample1, 3, SAMPLE1D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Hash, TestSample2, 1, SAMPLE2D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Hash, TestSample3, 8, SAMPLE3D);


THE_BENCHMARK(FindTheOnlyRepeatingElement_Xor, SAMPLE1D);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Xor, TestSample1, 3, SAMPLE1D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Xor, TestSample2, 1, SAMPLE2D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Xor, TestSample3, 8, SAMPLE3D);


THE_BENCHMARK(FindTheOnlyRepeatingElement_InPlace, SAMPLE1D);

SIMPLE_TEST(FindTheOnlyRepeatingElement_InPlace, TestSample1, 3, SAMPLE1D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_InPlace, TestSample2, 1, SAMPLE2D);
SIMPLE_TEST(FindTheOnlyRepeatingElement_InPlace, TestSample3, 8, SAMPLE3D);


const ArrayType SAMPLE1S = {1, 1, 2, 3, 4};
const ArrayType SAMPLE2S = {1, 2, 3, 4, 4};
const ArrayType SAMPLE3S = {1, 2, 3, 3, 4};


THE_BENCHMARK(FindTheOnlyRepeatingElement_Sorted_BinarySearch, SAMPLE3S);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Sorted_BinarySearch,
            TestFront,
            SAMPLE1S.front(),
            SAMPLE1S);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sorted_BinarySearch, TestBack, SAMPLE2S.back(), SAMPLE2S);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sorted_BinarySearch, TestSample1, 3, SAMPLE3S);
