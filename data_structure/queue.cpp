#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "singly_linked_list.h"

/** Implementing Queue using Arrays
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.1.
 * @reference   Queue | Set 1 (Introduction and Array Implementation)
 *              https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
 */
class ArrayQueue {
    using ValueType = int;

    const std::size_t CAPACITY;
    std::vector<ValueType> buffer;
    std::size_t size = 0;
    std::size_t front = 0;
    std::size_t rear;

    void advance(std::size_t &index) const {
                index = (index + 1) % CAPACITY;
    }

    public:
    ArrayQueue(const std::size_t cap = 1024): CAPACITY(cap), buffer(cap, 0), rear(cap - 1) {}

    void Enqueue(const ValueType v) {
        assert(size < CAPACITY);

        advance(rear);
        buffer[rear] = v;
        ++size;
    }

    auto Dequeue() {
        assert(size);

        const auto elem = buffer[front];
        advance(front);
        --size;
    }

    auto Front() const {
        assert(size);
        return buffer[front];
    }

    auto Rear() const {
        assert(size);
        return buffer[rear];
    }

    auto Empty() const {
        return size == 0;
    }
};


/** Implementing Queue using Linked List 
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.1.
 * @reference   Queue | Set 2 (Linked List Implementation)
 *              https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
 */
class ListQueue {
    SinglyLinkedList buffer;

    public:
    void Enqueue(const ValueType v) {
        buffer.PushBack(v);
    }

    auto Dequeue() {
        buffer.PopHead();
    }

    auto Empty() const {
        return buffer.Empty();
    }
};


const std::vector<int> EXPECTED_ARRAY {2,3,4,5,6,7};

template <typename Queue>
auto testQueueHelper() {
    Queue queue;
    queue.Enqueue(0);
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    queue.Enqueue(5);
    queue.Dequeue();
    queue.Dequeue();
    queue.Enqueue(6);
    queue.Enqueue(7);

    std::vector<int> output;
    while(not queue.Empty()){
        output.push_back(queue.Dequeue());
    }

    return output;
}

auto testArrayQueue() {
    return testQueueHelper<ArrayQueue>();
}

SIMPLE_TEST0(testArrayQueue, TestSample, EXPECTED_ARRAY);


auto testListQueue() {
    return testQueueHelper<ListQueue>();
}

SIMPLE_TEST0(testListQueue, TestSample, EXPECTED_ARRAY);
