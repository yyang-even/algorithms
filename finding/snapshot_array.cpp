#include "common_header.h"


namespace {

/** Snapshot Array
 *
 * @reference   https://leetcode.com/problems/snapshot-array/
 *
 * Implement a SnapshotArray that supports the following interface:
 *  SnapshotArray(int length) initializes an array-like data structure with the given length. Initially,
 *  each element equals 0.
 *  void set(index, val) sets the element at the given index to be equal to val.
 *  int snap() takes a snapshot of the array and returns the snap_id: the total number of times we
 *  called snap() minus 1.
 *  int get(index, snap_id) returns the value at the given index, at the time we took the snapshot with
 *  the given snap_id
 */
class SnapshotArray {
    int m_snap_id = 0;
    std::vector<std::map<int, int>> m_snaps;

public:
    SnapshotArray(const int length) : m_snaps(length, std::map<int, int> {{0, 0}}) {
    }

    void set(const int index, const int v) {
        m_snaps[index][m_snap_id] = v;
    }

    auto snap() {
        return m_snap_id++;
    }

    auto get(const int index, const int snap_id) const {
        const auto iter = m_snaps[index].upper_bound(snap_id);
        return std::prev(iter)->second;
    }
};

} //namespace


#ifdef WANT_TESTS
TEST(SnapshotArrayTest, TestSanity) {
    SnapshotArray s_a {3};

    s_a.set(0, 5);
    EXPECT_EQ(0, s_a.snap());
    s_a.set(0, 6);
    EXPECT_EQ(5, s_a.get(0, 0));
}
#endif
