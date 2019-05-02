#include "common_header.h"

#include <stack>
#include <queue>

#include "data_structure/linked_list/singly_linked_list.h"

/** Implementing Queue using Arrays
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.1.
 * @reference   Queue | Set 1 (Introduction and Array Implementation)
 *              https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
 * @reference   Queue in Standard Template Library (STL)
 *              https://www.geeksforgeeks.org/queue-cpp-stl/
 * @reference   Array implementation of queue (Simple)
 *              https://www.geeksforgeeks.org/array-implementation-of-queue-simple/
 * @reference   Circular Queue | Set 1 (Introduction and Array Implementation)
 *              https://www.geeksforgeeks.org/circular-queue-set-1-introduction-array-implementation/
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
        return elem;
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
 *              Introduction to Algorithms, Third Edition. Chapter 10.1. Exercises 10.1-3.
 * @reference   Queue | Set 2 (Linked List Implementation)
 *              https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
 */
class ListQueue {
    SinglyLinkedList buffer;

public:
    void Enqueue(const SinglyLinkedList::ValueType v) {
        buffer.PushBack(v);
    }

    auto Dequeue() {
        return buffer.PopHead();
    }

    auto Empty() const {
        return buffer.Empty();
    }
};


/** Implement Queue using Stacks
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.1. Exercises 10.1-6.
 * @reference   https://www.geeksforgeeks.org/queue-using-stacks/
 *
 * Method 1 (By making enQueue operation costly) This method makes sure that oldest
 * entered element is always at the top of stack 1, so that deQueue operation just
 * pops from stack1. To put the element at top of stack1, stack2 is used.
 *
 * Method 2 (By making deQueue operation costly) In this method, in en-queue operation,
 * the new element is entered at the top of stack1. In de-queue operation, if stack2
 * is empty then all the elements are moved to stack2 and finally top of stack2 is returned.
 *
 * Method 2 is definitely better than method 1.
 */
class DequeueCostlyTwoStackQueue {
    using ValueType = int;
    std::stack<ValueType> enqueue_stack, dequeue_stack;

public:
    auto Empty() const {
        return enqueue_stack.empty() and dequeue_stack.empty();
    }

    void Enqueue(const ValueType v) {
        enqueue_stack.push(v);
    }

    auto Dequeue() {
        assert(not Empty());

        if (dequeue_stack.empty()) {
            while (not enqueue_stack.empty()) {
                dequeue_stack.push(enqueue_stack.top());
                enqueue_stack.pop();
            }
        }

        const auto v = dequeue_stack.top();
        dequeue_stack.pop();
        return v;
    }
};
/**
 * Queue can also be implemented using one user stack and one Function Call Stack.
 */
class DequeueCostlyOneStackQueue {
    using ValueType = int;
    std::stack<ValueType> enqueue_stack;

public:
    void Enqueue(const ValueType v) {
        enqueue_stack.push(v);
    }

    auto Dequeue() {
        assert(not enqueue_stack.empty());

        if (enqueue_stack.size() == 1) {
            const auto output = enqueue_stack.top();
            enqueue_stack.pop();
            return output;
        } else {
            const auto v = enqueue_stack.top();
            enqueue_stack.pop();
            const auto output = Dequeue();
            enqueue_stack.push(v);
            return output;
        }
    }

    auto Empty() const {
        return enqueue_stack.empty();
    }
};


/** Implement queue using priority queue or heap
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.5. Exercises 6.5-7.
 */
class HeapQueue {
    using ValueType = int;
    using KeyValuePair = std::pair<std::size_t, ValueType>;

    std::priority_queue<KeyValuePair, std::vector<KeyValuePair>, std::function<bool(const KeyValuePair &, const KeyValuePair &)>>
    queue{[](const auto & lhs, const auto & rhs) {
            return lhs.first > rhs.first;
        }};
    std::size_t counter = 0;

public:
    void Enqueue(const ValueType v) {
        queue.push(std::make_pair(++counter, v));
    }

    auto Dequeue() {
        assert(not queue.empty());

        const auto v = queue.top().second;
        queue.pop();
        return v;
    }

    auto Empty() const {
        return queue.empty();
    }
};


namespace {

const std::vector<int> EXPECTED_ARRAY {2, 3, 4, 5, 6, 7};

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
    while (not queue.Empty()) {
        output.push_back(queue.Dequeue());
    }

    return output;
}


auto testArrayQueue() {
    return testQueueHelper<ArrayQueue>();
}


auto testListQueue() {
    return testQueueHelper<ListQueue>();
}


auto testDequeueCostlyTwoStackQueue() {
    return testQueueHelper<DequeueCostlyTwoStackQueue>();
}


auto testDequeueCostlyOneStackQueue() {
    return testQueueHelper<DequeueCostlyOneStackQueue>();
}


auto testHeapQueue() {
    return testQueueHelper<HeapQueue>();
}

}//namespace


SIMPLE_TEST0(testArrayQueue, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testListQueue, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testDequeueCostlyTwoStackQueue, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testDequeueCostlyOneStackQueue, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testHeapQueue, TestSample, EXPECTED_ARRAY);
