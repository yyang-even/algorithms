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

}//namespace


const ArrayType SAMPLE1 = {"d1/", "d2/", "../", "d21/", "./"};
const ArrayType SAMPLE2 = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
const ArrayType SAMPLE3 = {"d1/", "../", "../", "../"};


THE_BENCHMARK(CrawlerLogFolder, SAMPLE1);

SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(CrawlerLogFolder, TestSAMPLE3, 0, SAMPLE3);
