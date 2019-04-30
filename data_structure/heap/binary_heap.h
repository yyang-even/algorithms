#pragma once

#include "common_header.h"

/** Binary Heap
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.1. 6.2. 6.3. Problems 6-1.
 *
 * @reference   https://www.geeksforgeeks.org/binary-heap/
 * @reference   Array Representation Of Binary Heap
 *              https://www.geeksforgeeks.org/array-representation-of-binary-heap/
 * @reference   Time Complexity of building a heap
 *              https://www.geeksforgeeks.org/time-complexity-of-building-a-heap/
 * @reference   Building Heap from Array
 *              https://www.geeksforgeeks.org/building-heap-from-array/
 * @reference   Insertion and Deletion in Heaps
 *              https://www.geeksforgeeks.org/insertion-and-deletion-in-heaps/
 * @reference   Leaf starting point in a Binary Heap data structure
 *              https://www.geeksforgeeks.org/leaf-starting-point-binary-heap-data-structure/
 * @reference   Height of a complete binary tree (or Heap) with N nodes
 *              https://www.geeksforgeeks.org/height-complete-binary-tree-heap-n-nodes/
 * @reference   Heap in C++ STL | make_heap(), push_heap(), pop_heap(), sort_heap(), is_heap, is_heap_until()
 *              https://www.geeksforgeeks.org/heap-using-stl-c/
 * @reference   How to implement Min Heap using STL?
 *              https://www.geeksforgeeks.org/implement-min-heap-using-stl/
 */
/** LFU (Least Frequently Used) Cache Implementation
 *
 * @reference   https://www.geeksforgeeks.org/lfu-least-frequently-used-cache-implementation/
 *
 * Least Frequently Used (LFU) is a caching algorithm in which the least frequently used
 * cache block is removed whenever the cache is overflowed. In LFU we check the old page
 * as well as the frequency of that page and if the frequency of the page is larger than
 * the old page we cannot remove it and if all the old pages are having same frequency
 * then take last.
 */
template <typename T, typename Compare = std::less<T> >
class BinaryHeap {
public:
    using ArrayType = typename std::vector<T>;
    using SizeType = typename ArrayType::size_type;

private:
    ArrayType heap;
    static const Compare compare;

    static SizeType parent(const SizeType i) {
        assert(i);
        return (i - 1) / 2;
    }

    static SizeType left(const SizeType i) {
        return (2 * i + 1);
    }

    static SizeType right(const SizeType i) {
        return (2 * i + 2);
    }

    static SizeType indexOfFirstLeave(const SizeType n) {
        return n / 2;
    }

    static SizeType height(const SizeType n) {
        return std::ceil(std::log2(n + 1)) - 1;
    }

    void heapifyRecursive(SizeType i,
                          const SizeType heap_size) {
        const auto l = left(i);
        const auto r = right(i);
        SizeType best = i;

        if (l < heap_size and compare(heap[l], heap[best])) {
            best = l;
        }
        if (r < heap_size and compare(heap[r], heap[best])) {
            best = r;
        }

        if (best != i) {
            std::swap(heap[i], heap[best]);
            heapifyRecursive(best, heap_size);
        }
    }
    void heapifyIterative(SizeType i,
                          const SizeType heap_size) {
        while (i < heap_size) {
            const auto l = left(i);
            const auto r = right(i);
            SizeType best = i;

            if (l < heap_size and compare(heap[l], heap[best])) {
                best = l;
            }
            if (r < heap_size and compare(heap[r], heap[best])) {
                best = r;
            }

            if (best != i) {
                std::swap(heap[i], heap[best]);
                i = best;
            } else {
                break;
            }
        }
    }

    void buildHeap(const std::function<void(BinaryHeap<T, Compare>*,
                                            SizeType, const SizeType)> heapify) {
        if (not heap.empty()) {
            for (int i = indexOfFirstLeave(heap.size()) - 1; i >= 0; --i) {
                heapify(this, i, heap.size());
            }
        }
    }

    void bubbleUp(SizeType i, const bool suppose_better = false) {
        while (i and (suppose_better or compare(heap[i], heap[parent(i)]))) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

public:
    BinaryHeap() = default;
    BinaryHeap(const ArrayType &array, const bool recursive = true): heap(array) {
        buildHeap(recursive ? &BinaryHeap<T, Compare>::heapifyRecursive :
                  &BinaryHeap<T, Compare>::heapifyIterative);
    }

    auto Top() const {
        assert(not heap.empty());
        return heap.front();
    }

    auto Pop() {
        const auto top = Top();
        heap.front() = heap.back();
        heap.pop_back();
        heapifyRecursive(0, heap.size());

        return top;
    }

    void Push(const T value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    bool Empty() const {
        return heap.empty();
    }

    ArrayType ToSortedArray() {
        for (auto heap_size = heap.size(); heap_size > 1;) {
            std::swap(heap.front(), heap[--heap_size]);
            heapifyRecursive(0, heap_size);
        }

        return std::move(heap);
    }

    void Prioritize(const SizeType i, const T new_key) {
        assert(i < heap.size());

        if (compare(new_key, heap[i])) {
            heap[i] = new_key;
            bubbleUp(i);
        }
    }


    /** Heap Delete
    *
    * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
    *              Introduction to Algorithms, Third Edition. Exercises 6.5-8.
    */
    void Delete(const SizeType i) {
        assert(i < heap.size());

        bubbleUp(i, true);
        Pop();
    }


    /** How to check if a given array represents a Binary Heap?
     *
     * @reference   https://www.geeksforgeeks.org/how-to-check-if-a-given-array-represents-a-binary-heap/
     * @reference   Given level order traversal of a Binary Tree, check if the Tree is a Min-Heap
     *              https://www.geeksforgeeks.org/given-level-order-traversal-binary-tree-check-tree-min-heap/
     */
    static auto isHeap_Recursive(const ArrayType &values, const SizeType i = 0) {
        assert(values.size());

        const auto left_child_index = left(i);
        if (left_child_index >= values.size()) {
            return true;
        }

        const auto right_child_index = right(i);
        if (compare(values[i], values[left_child_index]) and
            (right_child_index >= values.size() or compare(values[i], values[right_child_index])) and
            isHeap_Recursive(values, left_child_index) and
            isHeap_Recursive(values, right_child_index)) {
            return true;
        }

        return false;
    }
    static auto isHeap_Iterative(const ArrayType &values) {
        for (SizeType i = 0; i < indexOfFirstLeave(values.size()); ++i) {
            if (not compare(values[i], values[left(i)])) {
                return false;
            }

            const auto right_child_index = right(i);
            if (right_child_index < values.size() and
                not compare(values[i], values[right_child_index])) {
                return false;
            }
        }

        return true;
    }
};

template <typename T, typename Compare>
const Compare BinaryHeap<T, Compare>::compare;

template <typename T>
using MaxHeap = BinaryHeap<T, std::greater<T> > ;
template <typename T>
using MinHeap = BinaryHeap<T, std::less<T> > ;
