#include "common_header.h"


namespace {

struct Box {
    int height = 0;
    int width = 0;
    int depth = 0;
};

using ArrayType = std::vector<Box>;

static inline auto &operator<<(std::ostream &out, const Box &a_box) {
    return out << "(" << a_box.height << ", " <<
           a_box.width << ", " <<
           a_box. depth << ")";

}

/** Box Stacking Problem | DP-22
 *
 * @reference   https://www.geeksforgeeks.org/box-stacking-problem-dp-22/
 *
 * You are given a set of n types of rectangular 3-D boxes, where the i^th box has height
 * h(i), width w(i) and depth d(i) (all real numbers). You want to create a stack of boxes
 * which is as tall as possible, but you can only stack a box on top of another box if the
 * dimensions of the 2-D base of the lower box are each strictly larger than those of the
 * 2-D base of the higher box. Of course, you can rotate a box so that any side functions
 * as its base. It is also allowable to use multiple instances of the same type of box.
 *
 * Note: The Box Stacking problem is a variation of LIS problem.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.10.
 *
 * You have a stack of n boxes, with widths w, heights h, and depths d. The boxes cannot
 * be rotated and can only be stacked on top of one another if each box in the stack is
 * strictly larger than the box above it in width, height, and depth. Implement a method
 * to build the tallest stack possible, where the height of a stack is the sum of the
 * heights of each box.
 */
auto MaxStackHeight(const ArrayType &boxes) {
    ArrayType rotated_boxes;
    for (const auto &[height, width, depth] : boxes) {
        rotated_boxes.push_back(Box{height, std::min(width, depth), std::max(width, depth)});
        rotated_boxes.push_back(Box{width, std::min(height, depth), std::max(height, depth)});
        rotated_boxes.push_back(Box{depth, std::min(width, height), std::max(width, height)});
    }

    std::sort(rotated_boxes.begin(), rotated_boxes.end(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.width * lhs.depth > rhs.width * rhs.depth;
    });

    std::vector<int> max_stack_heights;
    for (const auto &a_box : rotated_boxes) {
        max_stack_heights.push_back(a_box.height);
    }

    for (std::size_t i = 1; i < rotated_boxes.size(); ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            if (rotated_boxes[i].width < rotated_boxes[j].width and
                rotated_boxes[i].depth < rotated_boxes[j].depth) {
                if (const auto new_max_height = max_stack_heights[j] + rotated_boxes[i].height;
                    max_stack_heights[i] < new_max_height) {
                    max_stack_heights[i] = new_max_height;
                }
            }
        }
    }

    return *std::max_element(max_stack_heights.cbegin(), max_stack_heights.cend());
}

}//namespace


const ArrayType SAMPLE1 = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };


THE_BENCHMARK(MaxStackHeight, SAMPLE1);

SIMPLE_TEST(MaxStackHeight, TestSAMPLE1, 60, SAMPLE1);
