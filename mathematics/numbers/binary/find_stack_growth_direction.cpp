#include "common_header.h"


namespace {

/** C Program to find direction of growth of stack
 *
 * @reference   https://www.geeksforgeeks.org/c-program-find-direction-growth-stack/
 * @reference   How does a C program executes?
 *              https://www.geeksforgeeks.org/how-does-a-c-program-executes/
 * @reference   How to compile 32-bit program on 64-bit gcc in C and C++
 *              https://www.geeksforgeeks.org/compile-32-bit-program-64-bit-gcc-c-c/
 * @reference   Write a C program that won’t compile in C++
 *              https://www.geeksforgeeks.org/write-c-program-wont-compiler-c/
 * @reference   Memory Layout of C Programs
 *              https://www.geeksforgeeks.org/memory-layout-of-c-program/
 * @reference   Compiling a C program:- Behind the Scenes
 *              https://www.geeksforgeeks.org/compiling-a-c-program-behind-the-scenes/
 * @reference   Static and Dynamic Libraries | Set 1
 *              https://www.geeksforgeeks.org/static-vs-dynamic-libraries/
 * @reference   Working with Shared Libraries | Set 1
 *              https://www.geeksforgeeks.org/working-with-shared-libraries-set-1/
 * @reference   Working with Shared Libraries | Set 2
 *              https://www.geeksforgeeks.org/working-with-shared-libraries-set-2/
 * @reference   Difference between Loading and Linking
 *              https://www.geeksforgeeks.org/difference-between-loading-and-linking/
 * @reference   Stack vs Heap Memory Allocation
 *              https://www.geeksforgeeks.org/stack-vs-heap-memory-allocation/
 * @reference   Heap overflow and Stack overflow
 *              https://www.geeksforgeeks.org/heap-overflow-stack-overflow/
 * @reference   Stack Unwinding in C++
 *              https://www.geeksforgeeks.org/stack-unwinding-in-c/
 */
inline constexpr auto
IsStackGrowthDownward(const int *const parent_local_address) {
    constexpr int local = 0;
    return parent_local_address > &local;
}

}//namespace


#ifdef WANT_TERMINAL_APP
int main(int, char **) {
    constexpr int local = 0;
    if (IsStackGrowthDownward(&local)) {
        std::cout << "Stack grows downward" << std::endl;
    } else {
        std::cout << "Stack grows upward" << std::endl;
    }

    return EXIT_SUCCESS;
}
#endif
