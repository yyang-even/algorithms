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


/**
 * @reference   Baseball Game
 *              https://leetcode.com/problems/baseball-game/
 *
 * You are keeping score for a baseball game with strange rules. The game consists of several
 * rounds, where the scores of past rounds may affect future rounds' scores.
 * At the beginning of the game, you start with an empty record. You are given a list of
 * strings ops, where ops[i] is the ith operation you must apply to the record and is one
 * of the following:
 *  An integer x - Record a new score of x.
 *  "+" - Record a new score that is the sum of the previous two scores. It is guaranteed
 *      there will always be two previous scores.
 *  "D" - Record a new score that is double the previous score. It is guaranteed there will
 *      always be a previous score.
 *  "C" - Invalidate the previous score, removing it from the record. It is guaranteed
 *      there will always be a previous score.
 * Return the sum of all the scores on the record.
 */


/**
 * @reference   Simplify Path
 *              https://leetcode.com/problems/simplify-path/
 *
 * Given a string path, which is an absolute path (starting with a slash '/') to a file
 * or directory in a Unix-style file system, convert it to the simplified canonical path.
 * In a Unix-style file system, a period '.' refers to the current directory, a double
 * period '..' refers to the directory up a level, and any multiple consecutive slashes
 * (i.e. '//') are treated as a single slash '/'. For this problem, any other format of
 * periods such as '...' are treated as file/directory names.
 * The canonical path should have the following format:
 *  The path starts with a single slash '/'.
 *  Any two directories are separated by a single slash '/'.
 *  The path does not end with a trailing '/'.
 *  The path only contains the directories on the path from the root directory to the
 *      target file or directory (i.e., no period '.' or double period '..')
 * Return the simplified canonical path.
 */
auto SimplifyPath(const std::string &path) {
    std::vector<std::string> path_stack;
    std::stringstream ss(path);
    std::string component;
    while (std::getline(ss, component, '/')) {
        if (component.empty() or component == ".") {
            continue;
        }

        if (component == "..") {
            if (not path_stack.empty()) {
                path_stack.pop_back();
            }
        } else {
            path_stack.push_back(component);
        }
    }

    std::string result;
    for (auto &&c : path_stack) {
        result += "/" + std::move(c);
    }

    return result.empty() ? "/" : result;
}

}//namespace


const ArrayType SAMPLE1 = {"d1/", "d2/", "../", "d21/", "./"};
const ArrayType SAMPLE2 = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
const ArrayType SAMPLE3 = {"d1/", "../", "../", "../"};


THE_BENCHMARK(CrawlerLogFolder, SAMPLE1);

SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE3, 0, SAMPLE3);


THE_BENCHMARK(SimplifyPath, "/home/");

SIMPLE_TEST(SimplifyPath, TestSAMPLE1, "/home", "/home/");
SIMPLE_TEST(SimplifyPath, TestSAMPLE2, "/", "/../");
SIMPLE_TEST(SimplifyPath, TestSAMPLE3, "/home/foo", "/home//foo/");
SIMPLE_TEST(SimplifyPath, TestSAMPLE4, "/home", "/home");
SIMPLE_TEST(SimplifyPath, TestSAMPLE5, "/", "/..");
SIMPLE_TEST(SimplifyPath, TestSAMPLE6, "/home/foo", "/home//foo");
SIMPLE_TEST(SimplifyPath, TestSAMPLE7, "/c", "/c//.//");
SIMPLE_TEST(SimplifyPath, TestSAMPLE8, "/...", "/...");
