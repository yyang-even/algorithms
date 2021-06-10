#pragma once


template <typename UnaryPredicate>
static inline constexpr auto
RemoveCharacters_TwoPointers(std::string input, const UnaryPredicate p) {
    auto output_iter = input.begin();
    for (auto input_iter = input.begin(); input_iter != input.end(); ++input_iter) {
        if (p(*input_iter)) {
            *output_iter++ = *input_iter;
        }
    }

    input.resize(std::distance(input.begin(), output_iter));
    return input;
}
