#include "common_header.h"


/** Deque
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.1-5.
 * @reference   Deque | Set 1 (Introduction and Applications)
 *              https://www.geeksforgeeks.org/deque-set-1-introduction-applications/
 * @reference   Implementation of Deque using circular array
 *              https://www.geeksforgeeks.org/implementation-deque-using-circular-array/
 */
class CircularArrayDeque {
    using BufferType = std::vector<int>;

    BufferType::size_type CAPACITY;
    BufferType buffer;
    BufferType::size_type size = 0;
    BufferType::size_type front = 0;
    BufferType::size_type rear = 0;

    void advance(BufferType::size_type &index, const int step) const {
        index = (index + step + CAPACITY) % CAPACITY;
    }

    auto next(BufferType::size_type index) const {
        advance(index, 1);
        return index;
    }

    auto prev(BufferType::size_type index) const {
        advance(index, -1);
        return index;
    }


public:
    CircularArrayDeque(const BufferType::size_type cap = 1024):
        CAPACITY(cap), buffer(cap, 0), rear(cap - 1) {}

    auto Full() const {
        return size >= CAPACITY;
    }

    auto Empty() const {
        return size == 0;
    }

    void EndequeRear(const BufferType::value_type v) {
        assert(not Full());

        rear = next(rear);
        buffer[rear] = v;
        ++size;
    }

    void EndequeFront(const BufferType::value_type v) {
        assert(not Full());

        front = prev(front);
        buffer[front] = v;
        ++size;
    }

    auto Front() const {
        assert(not Empty());

        return buffer[front];
    }

    auto Rear() const {
        assert(not Empty());

        return buffer[rear];
    }

    auto DedequeFront() {
        const auto elem = Front();
        front = next(front);
        --size;
        return elem;
    }

    auto DedequeRear() {
        const auto elem = Rear();
        rear = prev(rear);
        --size;
        return elem;
    }
};


/**
 * @reference   Implementation of Deque using doubly linked list
 *              https://www.geeksforgeeks.org/implementation-deque-using-doubly-linked-list/
 */
class DoublyListDeque {
    using BufferType = std::list<int>;

    BufferType buffer;

public:
    auto Empty() const {
        return buffer.empty();
    }

    void EndequeRear(const BufferType::value_type v) {
        buffer.push_back(v);
    }

    void EndequeFront(const BufferType::value_type v) {
        buffer.push_front(v);
    }

    auto Front() const {
        assert(not Empty());

        return buffer.front();
    }

    auto Rear() const {
        assert(not Empty());

        return buffer.back();
    }

    auto DedequeFront() {
        const auto v = Front();
        buffer.pop_front();
        return v;
    }

    auto DedequeRear() {
        const auto v = Rear();
        buffer.pop_back();
        return v;
    }
};


/** Implement Stack and Queue using Deque
 *
 * @reference   https://www.geeksforgeeks.org/implement-stack-queue-using-deque/
 */


namespace {

template <typename Deque>
auto testDequeHelper() {
    Deque deque;

    deque.EndequeFront(-1);
    deque.DedequeRear();
    deque.EndequeRear(0);
    deque.EndequeFront(1);
    deque.EndequeFront(2);
    deque.EndequeFront(3);
    deque.EndequeRear(4);
    deque.EndequeFront(5);
    deque.DedequeRear();
    deque.DedequeRear();
    deque.DedequeFront();
    deque.EndequeRear(6);
    deque.EndequeRear(7);
    deque.EndequeFront(8);

    std::vector<int> output;
    while (not deque.Empty()) {
        output.push_back(deque.DedequeFront());
    }

    return output;
}

}//namespace


#ifdef WANT_TESTS
const std::vector<int> EXPECTED_ARRAY {8, 3, 2, 1, 6, 7};


#define SimpleDequeTest(dequeName) namespace {                      \
    TEST(SimpleDequeTest, Test##dequeName) {                        \
        EXPECT_EQ(EXPECTED_ARRAY, testDequeHelper<dequeName>());    \
    }                                                               \
}


SimpleDequeTest(CircularArrayDeque);


SimpleDequeTest(DoublyListDeque);
#endif
