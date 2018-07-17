#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

template <std::size_t N>
using ArrayType = std::array<int, N>;

/** Reservoir Sampling
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 5.3. Exercises 5.3-7.
 *
 *              https://www.geeksforgeeks.org/reservoir-sampling/
 *
 * Reservoir sampling is a family of randomized algorithms for randomly choosing k samples
 * from a list of n items, where n is either a very large or unknown number. Typically n
 * is large enough that the list doesn’t fit into main memory. For example, a list of search
 * queries in Google and Facebook.
 *
 * So we are given a big array (or stream) of numbers (to simplify), and we need to write
 * an efficient function to randomly select k numbers where 1 <= k <= n.
 * Let the input array be stream[]. 
 *
 * @complexity  O(n)
 */
template <std::size_t N>
auto ReservoirSampling(const ArrayType<N> &stream, const typename ArrayType<N>::size_type k){
    assert (k < stream.size());

    std::vector<typename ArrayType<N>::value_type> samples {stream.cbegin(), stream.cbegin() + k};
    for(auto i = k; i < stream.size(); ++i) {
        const auto j = Random_Number<typename ArrayType<N>::size_type>(0, i);
        if (j < k)
            samples[j] = stream[i];
    }

    return samples;
}


ArrayType<8> VALUES = {1, 2, 3, 4, 5, 6, 7, 8};
SIMPLE_BENCHMARK(ReservoirSampling, VALUES, 3);


#ifdef WANT_TERMINAL_APP
int main(int argc, char **argv) {
    std::cout << "Selected Samples: " << ReservoirSampling(VALUES, 3) << std::endl;

    return EXIT_SUCCESS;
}
#endif
