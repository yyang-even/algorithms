#pragma once


/** Check if given number is perfect square
 *
 * @reference   https://www.geeksforgeeks.org/check-if-given-number-is-perfect-square-in-cpp/
 * @reference   Check whether the number can be made perfect square after adding 1
 *              https://www.geeksforgeeks.org/check-whether-the-number-can-be-made-perfect-square-after-adding-1/
 * @reference   Check whether the number can be made perfect square after adding K
 *              https://www.geeksforgeeks.org/check-whether-the-number-can-be-made-perfect-square-after-adding-k/
 */
static constexpr inline auto IsPerfectSquare(const double x) {
    const auto square_root = std::sqrt(x);
    return square_root == std::floor(square_root);
}
