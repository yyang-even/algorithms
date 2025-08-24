#pragma once


template<typename T>
using MatrixTypeTemplate = std::vector<std::vector<T>>;

using MatrixType = MatrixTypeTemplate<int>;


template<typename MatrixType>
static inline constexpr auto ValidPoint(const MatrixType &screen, const int x, const int y) {
    return not(x < 0 or x >= static_cast<int>(screen.size()) or y < 0 or
               y >= static_cast<int>(screen.front().size()));
}


const std::vector<std::pair<int, int>> DIRECTIONS {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};


static inline auto ForEachDirection(const int M,
                                    const int N,
                                    const int row,
                                    const int column,
                                    const std::function<void(int, int)> visitor) {
    for (const auto &[delta_r, delta_c] : DIRECTIONS) {
        const auto new_r = row + delta_r;
        const auto new_c = column + delta_c;
        if (new_r >= 0 and new_c >= 0 and new_r < M and new_c < N) {
            visitor(new_r, new_c);
        }
    }
}


/**
 * @reference   Number of Laser Beams in a Bank
 *              https://leetcode.com/problems/number-of-laser-beams-in-a-bank/
 *
 * Anti-theft security devices are activated inside a bank. You are given a 0-indexed binary string
 * array bank representing the floor plan of the bank, which is an m x n 2D matrix. bank[i] represents
 * the ith row, consisting of '0's and '1's. '0' means the cell is empty, while'1' means the cell has a
 * security device.
 * There is one laser beam between any two security devices if both conditions are met:
 *  The two devices are located on two different rows: r1 and r2, where r1 < r2.
 *  For each row i where r1 < i < r2, there are no security devices in the ith row.
 * Laser beams are independent, i.e., one beam does not interfere nor join with another.
 * Return the total number of laser beams in the bank.
 *
 * @tags    #matrix
 */
