#include "common_header.h"


namespace {

/**
 * @reference   Seat Reservation Manager
 *              https://leetcode.com/problems/seat-reservation-manager/
 *
 * Design a system that manages the reservation state of n seats that are numbered from 1 to n.
 * Implement the SeatManager class:
 *  SeatManager(int n) Initializes a SeatManager object that will manage n seats numbered from 1 to n.
 *  All seats are initially available.
 *  int reserve() Fetches the smallest-numbered unreserved seat, reserves it, and returns its number.
 *  void unreserve(int seatNumber) Unreserves the seat with the given seatNumber.
 *
 * @tags    #ordered-set
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


/**
 * @reference   Design a Food Rating System
 *              https://leetcode.com/problems/design-a-food-rating-system/
 *
 * Design a food rating system that can do the following:
 *  Modify the rating of a food item listed in the system.
 *  Return the highest-rated food item for a type of cuisine in the system.
 * Implement the FoodRatings class:
 *  FoodRatings(String[] foods, String[] cuisines, int[] ratings) Initializes the system. The food items
 *  are described by foods, cuisines and ratings, all of which have a length of n.
 *      foods[i] is the name of the ith food,
 *      cuisines[i] is the type of cuisine of the ith food, and
 *      ratings[i] is the initial rating of the ith food.
 *  void changeRating(String food, int newRating) Changes the rating of the food item with the name food.
 *  String highestRated(String cuisine) Returns the name of the food item that has the highest rating
 *  for the given type of cuisine.  If there is a tie, return the item with the lexicographically
 *  smaller name.
 * Note that a string x is lexicographically smaller than string y if x comes before y in dictionary
 * order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i], then
 * x[i] comes before y[i] in alphabetic order.
 * All the strings in foods are distinct.
 *
 * @tags    #hash-table #ordered-set
 */


/**
 * @reference   Design Task Manager
 *              https://leetcode.com/problems/design-task-manager/
 *
 * There is a task management system that allows users to manage their tasks, each associated with a
 * priority. The system should efficiently handle adding, modifying, executing, and removing tasks.
 * Implement the TaskManager class:
 *  TaskManager(vector<vector<int>>& tasks) initializes the task manager with a list of
 *      user-task-priority triples. Each element in the input list is of the form [userId, taskId,
 *      priority], which adds a task to the specified user with the given priority.
 *  void add(int userId, int taskId, int priority) adds a task with the specified taskId and priority to
 *      the user with userId. It is guaranteed that taskId does not exist in the system.
 *  void edit(int taskId, int newPriority) updates the priority of the existing taskId to newPriority.
 *      It is guaranteed that taskId exists in the system.
 *  void rmv(int taskId) removes the task identified by taskId from the system. It is guaranteed that
 *      taskId exists in the system.
 *  int execTop() executes the task with the highest priority across all users. If there are multiple
 *      tasks with the same highest priority, execute the one with the highest taskId. After executing,
 *      the taskId is removed from the system. Return the userId associated with the executed task. If
 *      no tasks are available, return -1.
 * Note that a user may be assigned multiple tasks.
 *
 * @tags    #hash-table #ordered-set
 */

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
