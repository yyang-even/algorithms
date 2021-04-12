#pragma once

#include "common_header.h"

/** Reservoir Sampling
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 5.3. Exercises 5.3-7.
 *
 *              https://www.geeksforgeeks.org/reservoir-sampling/
 *
 * Reservoir sampling is a family of randomized algorithms for randomly choosing k samples
 * from a list of n items, where n is either a very large or unknown number. Typically n
 * is large enough that the list doesn't fit into main memory. For example, a list of
 * search queries in Google and Facebook.
 *
 * So we are given a big array (or stream) of numbers (to simplify), and we need to write
 * an efficient function to randomly select k numbers where 1 <= k <= n. Let the input
 * array be stream[].
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.3.
 *
 * @complexity  O(n)
 */
template <typename Container>
auto ReservoirSampling(const Container &stream, const typename Container::size_type k) {
    std::vector<typename Container::value_type> samples;
    auto iter = stream.cbegin();
    typename Container::size_type i = 0ul;
    for (; i < k; ++i, ++iter) {
        samples.push_back(*iter);
    }

    for (; iter != stream.cend(); ++i, ++iter) {
        const auto j = Random_Number(0, i);
        if (j < k) {
            samples[j] = *iter;
        }
    }

    return samples;
}
