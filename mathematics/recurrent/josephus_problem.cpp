#include "common_header.h"

#include "data_structure/linked_list/linked_list.h"
#include "data_structure/linked_list/singly_list/singly_circular_linked_list.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Josephus Problem
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1.3.
 * @reference   Josephus problem | Set 2 (A Simple Solution when k = 2)
 *              https://www.geeksforgeeks.org/josephus-problem-set-2-simple-solution-k-2/
 * @reference   Find last element after deleting every second element in array of n integers
 *              https://www.geeksforgeeks.org/find-last-element-deleting-every-second-element-array-n-integers/
 * @reference   Puzzle 81 | 100 people in a circle with gun puzzle
 *              https://www.geeksforgeeks.org/puzzle-100-people-in-a-circle-with-gun-puzzle/
 *
 * A variant of Josephus Problem. Start with n people numbered 1 to n around a circle, and we eliminate
 * every second remaining person until only one survives. For n = 10, the elimination order is 2, 4, 6,
 * 8, 10, 3, 7, 1, 9, so 5 survives.
 * The problem: Determine the survivor’s number, J(n).
 */
/**
 * J(1) = 1;
 * J(2n) = 2J(n) - 1,      for n >= 1;
 * J(2n + 1) = 2J(n) + 1,  for n >= 1.
 */
inline constexpr unsigned JosephusProblem2_Recursive(const unsigned n) {
    if (n == 1) {
        return 1;
    } else if ((n & 1) == 1) { //odd
        return (JosephusProblem2_Recursive(n / 2) << 1) + 1;
    } else { //even
        return (JosephusProblem2_Recursive(n / 2) << 1) - 1;
    }
}


/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1.3.
 * @reference   Josephus Problem Using Bit Magic
 *              https://www.geeksforgeeks.org/josephus-problem-using-bit-magic/
 * @reference   Lucky alive person in a circle | Set – 2
 *              https://www.geeksforgeeks.org/lucky-alive-person-in-a-circle-set-2/
 *
 * J(2^m + l) = 2l + 1, for m >= 0 and 0 <= l < 2^m.
 */
constexpr unsigned JosephusProblem2_Closedform(const unsigned n) {
    unsigned m = 1 << (BitsNumber<decltype(n)> - 1);

    while (m and !(m & n)) {
        m /= 2;
    }
    return ((m ^ n) << 1) + 1;
}


/** Penultimate Survivor
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1, Exercises 15.
 *
 * Josephus had a friend who was saved by getting into the next-to-last position. What is I(n), the
 * number of the penultimate survivor when every second person is executed?
 */
/**
 * I(n) = I(3*2^m + l) = 2l + 1.
 */
constexpr unsigned PenultimateSurvivor_Closedform(const unsigned n) {
    if (n == 2) {
        return 2;
    }
    unsigned m = 3 << (BitsNumber<decltype(n)> - 2);

    while (n < m) {
        m /= 2;
    }
    return ((n - m) << 1) + 1;
}


/** Authentic Josephus Problem
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 3.3.
 *
 * Authentic Josephus Problem in which every third person is eliminated, instead of every second.
 */
constexpr unsigned JosephusProblem3(const unsigned n) {
    double D = 1.0;
    const double BOUND = n * 2.0;
    while (D <= BOUND) {
        D = std::ceil(1.5 * D);
    }
    return 3 * n + 1 - static_cast<unsigned>(D);
}


/** Kth Josephus problem
 *
 * @reference https://www.geeksforgeeks.org/josephus-problem-set-1-a-on-solution/
 *
 * There are n people standing in a circle waiting to be executed. The counting out begins at some point
 * in the circle and proceeds around the circle in a fixed direction. In each step, a certain number of
 * people are skipped and the next person is executed. The elimination proceeds around the circle (which
 * is becoming smaller and smaller as the executed people are removed), until only the last person
 * remains, who is given freedom. Given the total number of persons n and a number k which indicates
 * that k-1 persons are skipped and kth person is killed in circle. The task is to choose the place in
 * the initial circle so that you are the last one remaining and so survive.
 */
/**
 * josephus(n, k) = (josephus(n - 1, k) + k-1) % n + 1;
 * josephus(1, k) = 1.
 *
 * After the first person (kth from begining) is killed, n-1 persons are left. So we call josephus(n -
 * 1, k) to get the position with n-1 persons. But the position returned by josephus(n - 1, k) will
 * consider the position starting from k%n + 1. So, we must make adjustments to the position returned by
 * josephus(n - 1, k).
 */
inline constexpr unsigned JosephusK_Recursive(const unsigned n, const unsigned k) {
    if (n == 1) {
        return 1;
    } else {
        return (JosephusK_Recursive(n - 1, k) + k - 1) % n + 1;
    }
}


/**
 * @reference   Josephus Problem | (Iterative Solution)
 *              https://www.geeksforgeeks.org/josephus-problem-iterative-solution/
 */
constexpr auto JosephusK_Iterative(const unsigned n, const unsigned k) {
    unsigned sword = 0;
    for (unsigned i = 2; i <= n; ++i) {
        sword = (sword + k) % i;
    }

    return sword + 1;
}


/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 3.3.
 */
constexpr unsigned JosephusK_Closedform(const unsigned n, const unsigned k) {
    double D = 1.0;
    const double K_MINUS_ONE = static_cast<double>(k - 1);
    const double BOUND = n * K_MINUS_ONE;
    while (D <= BOUND) {
        D = std::ceil(k / K_MINUS_ONE * D);
    }
    return k * n + 1 - static_cast<unsigned>(D);
}


/** Josephus permutation
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 14-2.
 * @reference   Lucky alive person in a circle | Code Solution to sword puzzle
 *              https://www.geeksforgeeks.org/lucky-alive-person-circle/
 * @reference   Josephus Circle using circular linked list
 *              https://www.geeksforgeeks.org/josephus-circle-using-circular-linked-list/
 * @reference   Delete every Kth node from circular linked list
 *              https://www.geeksforgeeks.org/delete-every-kth-node-from-circular-linked-list/
 */
auto JosephusPermutation(const unsigned n, const unsigned k) {
    SinglyCircularLinkedList persons;
    for (unsigned i = 1; i <= n; ++i) {
        persons.PushBack(i);
    }

    auto sword = persons.GetHead();
    ArrayType outputs;
    for (unsigned i = 2; sword != sword->next; i = 1) {
        Advance(sword, k - i);

        outputs.push_back(sword->next->value);
        persons.DeleteAfter(sword);
    }
    outputs.push_back(sword->value);

    return outputs;
}


/**
 * @reference   Reveal Cards In Increasing Order
 *              https://leetcode.com/problems/reveal-cards-in-increasing-order/
 *
 * You are given an integer array deck. There is a deck of cards where every card has a unique integer.
 * The integer on the ith card is deck[i].
 * You can order the deck in any order you want. Initially, all the cards start face down (unrevealed)
 * in one deck.
 * You will do the following steps repeatedly until all cards are revealed:
 *  Take the top card of the deck, reveal it, and take it out of the deck.
 *  If there are still cards in the deck then put the next top card of the deck at the bottom of the
 *  deck.
 *  If there are still unrevealed cards, go back to step 1. Otherwise, stop.
 * Return an ordering of the deck that would reveal the cards in increasing order.
 * Note that the first entry in the answer is considered to be the top of the deck.
 */
auto RevealCardsInIncreasingOrder(ArrayType deck) {
    std::sort(deck.begin(), deck.end());

    const int N = deck.size();
    ArrayType result(N, 0);

    int result_i = 0;
    bool skip = false;
    for (int deck_i = 0; deck_i < N;) {
        if (result[result_i] == 0) {
            if (not skip) {
                result[result_i] = deck[deck_i++];
            }
            skip = not skip;
        }
        result_i = (result_i + 1) % N;
    }

    return result;
}

} //namespace


constexpr unsigned LOWER = 1;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


SIMPLE_BENCHMARK(JosephusProblem2_Recursive, Sample1, LOWER);
SIMPLE_BENCHMARK(JosephusProblem2_Recursive, Sample2, UPPER);
SIMPLE_BENCHMARK(JosephusProblem2_Recursive, Sample3, 15);

SIMPLE_TEST(JosephusProblem2_Recursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(JosephusProblem2_Recursive, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(JosephusProblem2_Recursive, TestSample1, 15, 15);
SIMPLE_TEST(JosephusProblem2_Recursive, TestSample2, 3, 5);
SIMPLE_TEST(JosephusProblem2_Recursive, TestSample3, 5, 10);


SIMPLE_BENCHMARK(JosephusProblem2_Closedform, Sample1, LOWER);
SIMPLE_BENCHMARK(JosephusProblem2_Closedform, Sample2, UPPER);
SIMPLE_BENCHMARK(JosephusProblem2_Closedform, Sample3, 15);

SIMPLE_TEST(JosephusProblem2_Closedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(JosephusProblem2_Closedform, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(JosephusProblem2_Closedform, TestSample1, 15, 15);
SIMPLE_TEST(JosephusProblem2_Closedform, TestSample2, 3, 5);
SIMPLE_TEST(JosephusProblem2_Closedform, TestSample3, 5, 10);


MUTUAL_RANDOM_TEST(JosephusProblem2_Recursive, JosephusProblem2_Closedform, LOWER, UPPER);


constexpr unsigned LOWER2 = 2;


SIMPLE_BENCHMARK(PenultimateSurvivor_Closedform, Sample1, LOWER2);
SIMPLE_BENCHMARK(PenultimateSurvivor_Closedform, Sample2, UPPER);
SIMPLE_BENCHMARK(PenultimateSurvivor_Closedform, Sample3, 15);

SIMPLE_TEST(PenultimateSurvivor_Closedform, TestLOWER2, 2, LOWER2);
SIMPLE_TEST(PenultimateSurvivor_Closedform, TestUPPER, UPPER / 2, UPPER);
SIMPLE_TEST(PenultimateSurvivor_Closedform, TestSample1, 7, 15);


SIMPLE_BENCHMARK(JosephusProblem3, Sample1, LOWER);
SIMPLE_BENCHMARK(JosephusProblem3, Sample2, 15);

SIMPLE_TEST(JosephusProblem3, TestLOWER, 1, LOWER);
SIMPLE_TEST(JosephusProblem3, TestSample1, 5, 15);


constexpr unsigned UPPER_K = HYPOTHETIC_MAX_STACK_DEPTH;


THE_BENCHMARK(JosephusK_Recursive, 15, 2);

SIMPLE_TEST(JosephusK_Recursive, TestLOWER2, 1, LOWER, 2);
SIMPLE_TEST(JosephusK_Recursive, TestSample1, 15, 15, 2);
SIMPLE_TEST(JosephusK_Recursive, TestLOWER3, 1, LOWER, 3);
SIMPLE_TEST(JosephusK_Recursive, TestSample2, 5, 15, 3);
SIMPLE_TEST(JosephusK_Recursive, TestSample3, 5, 10, 2);
SIMPLE_TEST(JosephusK_Recursive, TestSample4, 3, 5, 2);
SIMPLE_TEST(JosephusK_Recursive, TestSample5, 2, 7, 4);


THE_BENCHMARK(JosephusK_Closedform, 15, 2);

SIMPLE_TEST(JosephusK_Closedform, TestLOWER2, 1, LOWER, 2);
SIMPLE_TEST(JosephusK_Closedform, TestSample1, 15, 15, 2);
SIMPLE_TEST(JosephusK_Closedform, TestLOWER3, 1, LOWER, 3);
SIMPLE_TEST(JosephusK_Closedform, TestSample2, 5, 15, 3);
SIMPLE_TEST(JosephusK_Closedform, TestSample3, 5, 10, 2);
SIMPLE_TEST(JosephusK_Closedform, TestSample4, 3, 5, 2);
SIMPLE_TEST(JosephusK_Closedform, TestSample5, 2, 7, 4);


THE_BENCHMARK(JosephusK_Iterative, 15, 2);

SIMPLE_TEST(JosephusK_Iterative, TestLOWER2, 1, LOWER, 2);
SIMPLE_TEST(JosephusK_Iterative, TestSample1, 15, 15, 2);
SIMPLE_TEST(JosephusK_Iterative, TestLOWER3, 1, LOWER, 3);
SIMPLE_TEST(JosephusK_Iterative, TestSample2, 5, 15, 3);
SIMPLE_TEST(JosephusK_Iterative, TestSample3, 5, 10, 2);
SIMPLE_TEST(JosephusK_Iterative, TestSample4, 3, 5, 2);
SIMPLE_TEST(JosephusK_Iterative, TestSample5, 2, 7, 4);


const ArrayType EXPECTED1 = {2, 4, 6, 8, 10, 3, 7, 1, 9, 5};
const ArrayType EXPECTED2 = {3, 6, 2, 7, 5, 1, 4};


THE_BENCHMARK(JosephusPermutation, 15, 2);

SIMPLE_TEST(JosephusPermutation, TestSample1, EXPECTED1, 10, 2);
SIMPLE_TEST(JosephusPermutation, TestSample2, EXPECTED2, 7, 3);


const ArrayType SAMPLE1C = {17, 13, 11, 2, 3, 5, 7};
const ArrayType EXPECTED1C = {2, 13, 3, 11, 5, 17, 7};

const ArrayType SAMPLE2C = {1, 1000};
const ArrayType EXPECTED2C = {1, 1000};


THE_BENCHMARK(RevealCardsInIncreasingOrder, SAMPLE1C);

SIMPLE_TEST(RevealCardsInIncreasingOrder, TestSample1, EXPECTED1C, SAMPLE1C);
SIMPLE_TEST(RevealCardsInIncreasingOrder, TestSample2, EXPECTED2C, SAMPLE2C);
