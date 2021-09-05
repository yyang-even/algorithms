#pragma once


static inline constexpr auto Parent(const std::size_t i) {
    assert(i);
    return (i - 1) / 2;
}

static inline constexpr auto LeftChild(const std::size_t i) {
    return 2 * i + 1;
}

static inline constexpr auto RightChild(const std::size_t i) {
    return 2 * i + 2;
}
