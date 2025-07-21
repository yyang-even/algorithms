#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Remove Sub-Folders from the Filesystem
 *
 * @reference   https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/
 *
 * Given a list of folders folder, return the folders after removing all sub-folders in those folders.
 * You may return the answer in any order.
 * If a folder[i] is located within another folder[j], it is called a sub-folder of it. A sub-folder of
 * folder[j] must start with folder[j], followed by a "/". For example, "/a/b" is a sub-folder of "/a",
 * but "/b" is not a sub-folder of "/a/b/c".
 * The format of a path is one or more concatenated strings of the form: '/' followed by one or more
 * lowercase English letters.
 *  For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string and "/" are
 *  not.
 *
 *  @tags   #sort #starts-with
 */
auto RemoveSubFolders_Sorting(ArrayType folder) {
    std::sort(folder.begin(), folder.end());

    std::vector<std::string_view> result;
    for (std::size_t i = 0; i < folder.size(); ++i) {
        result.push_back(folder[i]);

        auto j = i + 1;
        for (; j < folder.size(); ++j) {
            if (folder[j].starts_with(folder[i]) and folder[j][folder[i].size()] == '/') {
                continue;
            }

            break;
        }
        i = j - 1;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"};
const ArrayType EXPECTED1 = {"/a", "/c/d", "/c/f"};

const ArrayType SAMPLE2 = {"/a", "/a/b/c", "/a/b/d"};
const ArrayType EXPECTED2 = {"/a"};

const ArrayType SAMPLE3 = {"/a/b/c", "/a/b/ca", "/a/b/d"};


THE_BENCHMARK(RemoveSubFolders_Sorting, SAMPLE1);

SIMPLE_TEST(RemoveSubFolders_Sorting, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RemoveSubFolders_Sorting, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(RemoveSubFolders_Sorting, TestSAMPLE3, SAMPLE3, SAMPLE3);
