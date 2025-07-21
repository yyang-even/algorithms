#include "common_header.h"


namespace {

using PathType = std::vector<std::string>;
using ArrayType = std::vector<PathType>;
using TestOutputType = std::multiset<PathType>;

/** Delete Duplicate Folders in System
 *
 * @reference   https://leetcode.com/problems/delete-duplicate-folders-in-system/
 *
 * Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths,
 * where paths[i] is an array representing an absolute path to the ith folder in the file system.
 * For example, ["one", "two", "three"] represents the path "/one/two/three".
 * Two folders (not necessarily on the same level) are identical if they contain the same non-empty set
 * of identical subfolders and underlying subfolder structure. The folders do not need to be at the root
 * level to be identical. If two or more folders are identical, then mark the folders as well as all
 * their subfolders.
 * Once all the identical folders and their subfolders have been marked, the file system will delete all
 * of them. The file system only runs the deletion once, so any folders that become identical after the
 * initial deletion are not deleted.
 * Return the 2D array ans containing the paths of the remaining folders after deleting all the marked
 * folders. The paths may be returned in any order.
 *
 * @tags    #trie #tree-serialization
 */
struct TrieNode {
    std::string folder_structure_id;
    std::unordered_map<std::string_view, TrieNode> children;
};

void Insert(TrieNode &root, const PathType &path) {
    auto *iter = &root;
    for (const auto &folder : path) {
        iter = &(iter->children[folder]);
    }
}

void CountFolderStructures(TrieNode &node, std::unordered_map<std::string_view, int> &counts) {
    if (node.children.empty()) {
        return;
    }

    std::vector<std::string> subfolder_structures;
    for (auto &[folder, a_child] : node.children) {
        CountFolderStructures(a_child, counts);
        subfolder_structures.push_back(std::string(folder) + "(" + a_child.folder_structure_id +
                                       ")");
    }

    std::sort(subfolder_structures.begin(), subfolder_structures.end());
    for (auto &s : subfolder_structures) {
        node.folder_structure_id += std::move(s);
    }

    ++counts[node.folder_structure_id];
}

void GetUniqueFolders(const TrieNode &node,
                      const std::unordered_map<std::string_view, int> &folder_structure_counts,
                      PathType &path,
                      ArrayType &result) {
    for (const auto &[folder, a_child] : node.children) {
        path.push_back(std::string(folder));
        if (a_child.children.empty() or
            folder_structure_counts.at(a_child.folder_structure_id) == 1) {
            result.push_back(path);
            GetUniqueFolders(a_child, folder_structure_counts, path, result);
        }
        path.pop_back();
    }
}

auto ToTestOutputType(const ArrayType &paths) {
    TestOutputType result;
    for (const auto &a_path : paths) {
        result.insert(a_path);
    }

    return result;
}

auto DeleteDuplicateFolders(const ArrayType &paths) {
    TrieNode root;
    for (const auto &a_path : paths) {
        Insert(root, a_path);
    }

    std::unordered_map<std::string_view, int> folder_structure_counts;
    CountFolderStructures(root, folder_structure_counts);

    std::vector<std::string> path;
    std::vector<std::vector<std::string>> result;
    GetUniqueFolders(root, folder_structure_counts, path, result);

    return ToTestOutputType(result);
}

} //namespace


const ArrayType SAMPLE1 = {{"a"}, {"c"}, {"d"}, {"a", "b"}, {"c", "b"}, {"d", "a"}};
const TestOutputType EXPECTED1 = {{"d"}, {"d", "a"}};

const ArrayType SAMPLE2 = {{"a"},
                           {"c"},
                           {"a", "b"},
                           {"c", "b"},
                           {"a", "b", "x"},
                           {"a", "b", "x", "y"},
                           {"w"},
                           {"w", "y"}};
const TestOutputType EXPECTED2 = {{"c"}, {"c", "b"}, {"a"}, {"a", "b"}};

const ArrayType SAMPLE3 = {{"a", "b"}, {"c", "d"}, {"c"}, {"a"}};
const TestOutputType EXPECTED3 = {{"c"}, {"c", "d"}, {"a"}, {"a", "b"}};

const ArrayType SAMPLE4 = {{"a"},
                           {"a", "c"},
                           {"a", "c", "b"},
                           {"a", "w"},
                           {"a", "w", "y"},
                           {"z", "c"},
                           {"z", "c", "b"},
                           {"z", "c", "w"},
                           {"z", "c", "w", "y"},
                           {"z"}};
const TestOutputType EXPECTED4 = {
    {"a"}, {"z"}, {"a", "c"}, {"z", "c"}, {"a", "c", "b"}, {"z", "c", "b"}};


THE_BENCHMARK(DeleteDuplicateFolders, SAMPLE1);

SIMPLE_TEST(DeleteDuplicateFolders, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(DeleteDuplicateFolders, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(DeleteDuplicateFolders, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(DeleteDuplicateFolders, TestSAMPLE4, EXPECTED4, SAMPLE4);
