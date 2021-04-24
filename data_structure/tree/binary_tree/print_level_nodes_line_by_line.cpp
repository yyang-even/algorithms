#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"


namespace {

using ArrayType = std::vector<BinaryTree::ArrayType>;

/** Print level order traversal line by line | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/print-level-order-traversal-line-line/
 * @reference   Level order traversal line by line | Set 2 (Using Two Queues)
 *              https://www.geeksforgeeks.org/level-order-traversal-line-line-set-2-using-two-queues/
 * @reference   Level order traversal line by line | Set 3 (Using One Queue)
 *              https://www.geeksforgeeks.org/level-order-traversal-line-line-set-3-using-one-queue/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.4.
 */
auto PrintLevelOrderLineByLine(const BinaryTree::Node::PointerType root_node) {
    ArrayType results;
    LevelOrderTraversal_LevelAware_Helper(root_node,
    [&results](const auto & node) {
        results.back().push_back(node.value);
        return true;
    },
    [&results]() {
        results.emplace_back();
        return true;
    });

    return results;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const ArrayType EXPECTED1 = {
    {1},
    {2, 3},
    {4, 5}
};


THE_BENCHMARK(PrintLevelOrderLineByLine, SAMPLE1);

SIMPLE_TEST(PrintLevelOrderLineByLine, TestSAMPLE1, EXPECTED1, SAMPLE1);
