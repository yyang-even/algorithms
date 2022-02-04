#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Crawler Log Folder
 *
 * @reference   https://leetcode.com/problems/crawler-log-folder/
 *
 * The Leetcode file system keeps a log each time some user performs a change folder
 * operation.
 * The operations are described below:
 *  "../" : Move to the parent folder of the current folder. (If you are already in the
 *      main folder, remain in the same folder).
 *  "./" : Remain in the same folder.
 *  "x/" : Move to the child folder named x (This folder is guaranteed to always exist).
 * You are given a list of strings logs where logs[i] is the operation performed by the
 * user at the ith step.
 * The file system starts in the main folder, then the operations in logs are performed.
 * Return the minimum number of operations needed to go back to the main folder after the
 * change folder operations.
 */
auto CrawlerLogFolder(const ArrayType &logs) {
    int stack_size = 0;
    for (const auto &l : logs) {
        if (l == "../") {
            stack_size = std::max(0, stack_size - 1);
        } else if (l != "./") {
            ++stack_size;
        }
    }

    return stack_size;
}


/**
 * @reference   Maximum Nesting Depth of the Parentheses
 *              https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/
 *
 * A string is a valid parentheses string (denoted VPS) if it meets one of the following:
 *  It is an empty string "", or a single character not equal to "(" or ")",
 *  It can be written as AB (A concatenated with B), where A and B are VPS's, or
 *  It can be written as (A), where A is a VPS.
 * We can similarly define the nesting depth depth(S) of any VPS S as follows:
 *  depth("") = 0
 *  depth(C) = 0, where C is a string with a single character not equal to "(" or ")".
 *  depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's.
 *  depth("(" + A + ")") = 1 + depth(A), where A is a VPS.
 * For example, "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1, and 2),
 * and ")(" and "(()" are not VPS's.
 * Given a VPS represented as string s, return the nesting depth of s.
 */

}//namespace


const ArrayType SAMPLE1 = {"d1/", "d2/", "../", "d21/", "./"};
const ArrayType SAMPLE2 = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
const ArrayType SAMPLE3 = {"d1/", "../", "../", "../"};


THE_BENCHMARK(CrawlerLogFolder, SAMPLE1);

SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE3, 0, SAMPLE3);
