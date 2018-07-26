#include "common_header.h"

/** Binary Heap
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.1. 6.2. 6.3.
 *
 *              https://www.geeksforgeeks.org/binary-heap/
 *              Array Representation Of Binary Heap
 *              https://www.geeksforgeeks.org/array-representation-of-binary-heap/
 */
template <typename Compare = std::less<int> >
class BinaryHeap {
public:
    using ArrayType = std::vector<int>;

private:
    ArrayType heap;
    const Compare compare;

    auto parent(const ArrayType::size_type i) const {
        assert(not i);
        return (i - 1) / 2;
    }

    auto left(const ArrayType::size_type i) const {
        return (2 * i + 1);
    }

    auto right(const ArrayType::size_type i) const {
        return (2 * i + 2);
    }

    void heapifyRecursive(const ArrayType::size_type i,
                          const ArrayType::size_type heap_size) {
        const auto l = left(i);
        const auto r = right(i);
        std::vector<int>::size_type best = i;

        if (l < heap_size and compare(heap[l], heap[best])) {
            best = l;
        }
        if (r < heap_size and compare(heap[r], heap[best])) {
            best = r;
        }

        if (best != i) {
            std::swap(heap[i], heap[best]);
            heapifyRecursive(best, heap.size());
        }
    }

    void buildHeap() {
        assert(not heap.empty());
        for (int i = heap.size() / 2; i >= 0; --i) {
            heapifyRecursive(i, heap.size());
        }
    }

public:
    BinaryHeap(const ArrayType &array): heap(array) {
        if (not heap.empty()) {
            buildHeap();
        }
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

    void Push(const int value) {
        heap.push_back(value);

        auto i = heap.size() - 1;
        while (i and compare(heap[i], heap[parent(i)])) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
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
};
