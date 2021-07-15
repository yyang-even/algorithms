#include "common_header.h"

#include "data_structure/linked_list/singly_list/singly_linked_list.h"
#include "data_structure/linked_list/singly_list/singly_circular_linked_list.h"


/** Implementing Queue using Arrays
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.1.
 * @reference   Queue | Set 1 (Introduction and Array Implementation)
 *              https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
 * @reference   Queue in Standard Template Library (STL)
 *              https://www.geeksforgeeks.org/queue-cpp-stl/
 * @reference   Array implementation of queue (Simple)
 *              https://www.geeksforgeeks.org/array-implementation-of-queue-simple/
 * @reference   Circular Queue | Set 1 (Introduction and Array Implementation)
 *              https://www.geeksforgeeks.org/circular-queue-set-1-introduction-array-implementation/
 * @reference   FIFO (First-In-First-Out) approach in Programming
 *              https://www.geeksforgeeks.org/fifo-first-in-first-out-approach-in-programming/
 * @reference   FIFO vs LIFO approach in Programming
 *              https://www.geeksforgeeks.org/fifo-vs-lifo-approach-in-programming/
 * @reference   Circular array
 *              https://www.geeksforgeeks.org/circular-array/
 * @reference   Applications of Queue Data Structure
 *              https://www.geeksforgeeks.org/applications-of-queue-data-structure/
 */
class ArrayCircularQueue {
    using ValueType = int;

    std::size_t CAPACITY;
    std::vector<ValueType> buffer;
    std::size_t size = 0;
    std::size_t front = 0;
    std::size_t rear;

    constexpr void advance(std::size_t &index) const {
        index = (index + 1) % CAPACITY;
    }

public:
    explicit ArrayCircularQueue(const std::size_t cap = 1024):
        CAPACITY(cap), buffer(cap, 0), rear(cap - 1) {}

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

    constexpr auto Empty() const {
        return size == 0;
    }
};


/** Implementing Queue using Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.1. Exercises 10.1-3.
 * @reference   Queue | Set 2 (Linked List Implementation)
 *              https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
 * @reference   Queue – Linked List Implementation
 *              https://www.geeksforgeeks.org/queue-linked-list-implementation/
 * @reference   Difference between a Static Queue and a Singly Linked List
 *              https://www.geeksforgeeks.org/difference-between-a-static-queue-and-a-singly-linked-list/
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


/** Circular Queue | Set 2 (Circular Linked List Implementation)
 *
 * @reference   https://www.geeksforgeeks.org/circular-queue-set-2-circular-linked-list-implementation/
 */
class ListCircularQueue {
    SinglyCircularLinkedList buffer;

public:
    void Enqueue(const SinglyLinkedList::ValueType v) {
        buffer.PushBack(v);
    }

    auto Dequeue() {
        return buffer.PopHead();
    }

    constexpr auto Empty() const {
        return buffer.Empty();
    }
};


/** Implement Queue using Stacks
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.1. Exercises 10.1-6.
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 3.5.
 * @reference   https://www.geeksforgeeks.org/queue-using-stacks/
 *
 * Method 1 (By making enQueue operation costly) This method makes sure that oldest
 * entered element is always at the top of stack 1, so that deQueue operation just
 * pops from stack1. To put the element at top of stack1, stack2 is used.
 *
 * Method 2 (By making deQueue operation costly) In this method, in en-queue operation,
 * the new element is entered at the top of stack1. In de-queue operation, if stack2
 * is empty then all the elements are moved to stack2 and finally top of stack2 is
 * returned.
 *
 * Method 2 is definitely better than method 1.
 *
 * @reference   Implement Queue using Stacks
 *              https://leetcode.com/problems/implement-queue-using-stacks/
 *
 * Implement a first in first out (FIFO) queue using only two stacks. The implemented
 * queue should support all the functions of a normal queue (push, peek, pop, and empty).
 * Implement the MyQueue class:
 *  void push(int x) Pushes element x to the back of the queue.
 *  int pop() Removes the element from the front of the queue and returns it.
 *  int peek() Returns the element at the front of the queue.
 *  boolean empty() Returns true if the queue is empty, false otherwise.
 * Follow-up: Can you implement the queue such that each operation is amortized O(1)
 * time complexity? In other words, performing n operations will take overall O(n) time
 * even if one of those operations may take longer.
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
 *              Introduction to Algorithms, Third Edition. Section 6.5. Exercises 6.5-7.
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
        queue.push(std::pair(counter++, v));
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

template <typename Queue>
constexpr auto testQueueHelper() {
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

}//namespace


#ifdef WANT_TESTS
const std::vector<int> EXPECTED_ARRAY {2, 3, 4, 5, 6, 7};


#define SimpleQueueTest(queueName) namespace {                      \
    TEST(SimpleQueueTest, Test##queueName) {                        \
        EXPECT_EQ(EXPECTED_ARRAY, testQueueHelper<queueName>());    \
    }                                                               \
}


SimpleQueueTest(ArrayCircularQueue);


SimpleQueueTest(ListQueue);


SimpleQueueTest(ListCircularQueue);


SimpleQueueTest(DequeueCostlyTwoStackQueue);


SimpleQueueTest(DequeueCostlyOneStackQueue);


SimpleQueueTest(HeapQueue);
#endif
