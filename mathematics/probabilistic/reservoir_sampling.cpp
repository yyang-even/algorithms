#include "reservoir_sampling.h"


namespace {

template <std::size_t N>
using ArrayType = std::array<int, N>;


/** Select a random number from stream, with O(1) space
 *
 * @reference   https://www.geeksforgeeks.org/select-a-random-number-from-stream-with-o1-space/
 *
 * Given a stream of numbers, generate a random number from the stream. You are allowed
 * to use only O(1) space and the input is in the form of stream, so can't store the
 * previously seen numbers.
 */
template <typename Container>
inline constexpr auto RandomNumberFromStream(const Container &stream) {
    return ReservoirSampling(stream, 1).back();
}

}//namespace


ArrayType<8> VALUES = {1, 2, 3, 4, 5, 6, 7, 8};


THE_BENCHMARK(ReservoirSampling, VALUES, 3);


THE_BENCHMARK(RandomNumberFromStream, VALUES);


#ifdef WANT_TERMINAL_APP
int main(int, char **) {
    std::cout << "Selected Samples: " << ReservoirSampling(VALUES, 3) << std::endl;
    std::cout <<
              "Selected Random Number from Stream: " <<
              RandomNumberFromStream(VALUES) << std::endl;

    return EXIT_SUCCESS;
}
#endif
