#include "common_header.h"

/** Binary Heap
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.1. 6.2. 6.3.
 *
 *              https://www.geeksforgeeks.org/binary-heap/
 *              Array Representation Of Binary Heap
 *              https://www.geeksforgeeks.org/array-representation-of-binary-heap/
 *              Time Complexity of building a heap
 *              https://www.geeksforgeeks.org/time-complexity-of-building-a-heap/
 */
template <typename T, typename Compare = std::less<T> >
class BinaryHeap {
public:
    using ArrayType = typename std::vector<T>;
    using SizeType = typename ArrayType::size_type;

private:
    ArrayType heap;
    const Compare compare {};

    auto parent(const SizeType i) const {
        assert(i);
        return (i - 1) / 2;
    }

    auto left(const SizeType i) const {
        return (2 * i + 1);
    }

    auto right(const SizeType i) const {
        return (2 * i + 2);
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
            for (int i = heap.size() / 2; i >= 0; --i) {
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
};

template <typename T>
using MaxHeap = BinaryHeap<T, std::greater<T> > ;
template <typename T>
using MinHeap = BinaryHeap<T, std::less<T> > ;
