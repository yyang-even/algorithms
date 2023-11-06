#include "common_header.h"


namespace {

/** Seat Reservation Manager
 *
 * @reference   https://leetcode.com/problems/seat-reservation-manager/
 *
 * Design a system that manages the reservation state of n seats that are numbered from 1 to n.
 * Implement the SeatManager class:
 *  SeatManager(int n) Initializes a SeatManager object that will manage n seats numbered from 1 to n.
 *  All seats are initially available.
 *  int reserve() Fetches the smallest-numbered unreserved seat, reserves it, and returns its number.
 *  void unreserve(int seatNumber) Unreserves the seat with the given seatNumber.
 */
class SeatManager {
    int m_marker;
    std::set<int> m_availables;

public:
    explicit SeatManager(const int) {
        m_marker = 1;
    }

    auto reserve() {
        if (not m_availables.empty()) {
            const auto result = *m_availables.cbegin();
            m_availables.erase(m_availables.cbegin());
            return result;
        }

        return m_marker++;
    }

    void unreserve(const int seatNumber) {
        m_availables.insert(seatNumber);
    }
};

} //namespace


#ifdef WANT_TESTS
TEST(SeatManagerTests, TestSanity) {
    SeatManager manager {5};

    EXPECT_EQ(1, manager.reserve());
    EXPECT_EQ(2, manager.reserve());
    manager.unreserve(2);
    EXPECT_EQ(2, manager.reserve());
    EXPECT_EQ(3, manager.reserve());
    EXPECT_EQ(4, manager.reserve());
    EXPECT_EQ(5, manager.reserve());
    manager.unreserve(5);
}
#endif
