#include "common_header.h"

/************************************************************************/
/*


Following are the steps to find all prime factors.
1) While n is divisible by 2, print 2 and divide n by 2.
2) After step 1, n must be odd. Now start a loop from i = 3 to square root of n. While i divides n, print i and divide n by i, increment i by 2 and continue.
3) If n is a prime number and is greater than 2, then n will not become 1 by above two steps. So print n if it is greater than 2.

*/
/************************************************************************/
/** Prime Factors of N
 * @reference Ronald Graham, Oren Patashnik, Donald Knuth.
 *            Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 4.2.
 * Fundamental Theorem of Arithmetic: There's only one way to write n as a product of primes in
 * nondecreasing order.
 *
 * @reference http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
 * Efficient program to print all prime factors of a given number.
 *
 * Given a number n, write an efficient function to print all prime factors of n.
 * For example, if the input number is 12, then output should be ¡°2 2 3¡å.
 * And if the input number is 315, then output should be ¡°3 3 5 7¡å.
 */
void Print_All_Prime_Factors(unsigned N) {
    if (N > 2) {
        while (N % 2 == 0) {
            cout << 2 << " ";
            N /= 2;
        }

        unsigned square_root = sqrt(double(N));
        for (unsigned i = 3; i <= square_root; i += 2) {
            while (N % i == 0) {
                cout << i << " ";
                N /= i;
            }
        }

        if (N == 1) {
            cout << endl;
            return;
        }
    }
    cout << N << endl;
}
