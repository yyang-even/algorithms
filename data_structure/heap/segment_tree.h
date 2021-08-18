#pragma once


static inline constexpr auto LeftChild(const std::size_t i) {
    return i * 2;
}

static inline constexpr auto RightChild(const std::size_t i) {
    return LeftChild(i) + 1;
}

static inline constexpr auto Parent(const std::size_t i) {
    return i / 2;
}

static inline constexpr auto isLeftChild(const std::size_t i) {
    return i % 2 == 0;
}

static constexpr std::size_t ST_root = 1;
