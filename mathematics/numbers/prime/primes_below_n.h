#pragma once

auto SieveOfEratosthenes(const unsigned long N) {
    std::vector<unsigned long> output;
    if (N > 2) {
        std::vector<bool> numbers(N, true);
        unsigned long j;
        for (unsigned long i = 2; i < N; ++i) {
            if (numbers[i]) {
                output.push_back(i);
                for (j = i * 2; j < N; j += i) {
                    numbers[j] = false;
                }
            }
        }
    }
    return output;
}
