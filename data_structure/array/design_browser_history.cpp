#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Design Browser History
 *
 * @reference   https://leetcode.com/problems/design-browser-history/
 *
 * You have a browser of one tab where you start on the homepage and you can visit another url, get back
 * in the history number of steps or move forward in the history number of steps.
 * Implement the BrowserHistory class:
 *  BrowserHistory(string homepage) Initializes the object with the homepage of the browser.
 *  void visit(string url) Visits url from the current page. It clears up all the forward history.
 *  string back(int steps) Move steps back in history. If you can only return x steps in the history and
 *  steps > x, you will return only x steps. Return the current url after moving back in history at most
 *  steps.
 *  string forward(int steps) Move steps forward in history. If you can only forward x steps in the
 *  history and steps > x, you will forward only x steps. Return the current url after forwarding in
 *  history at most steps.
 */
class BrowserHistory {
    std::vector<std::string> history;
    int i = 0;

public:
    BrowserHistory(std::string homepage) : history({std::move(homepage)}) {
    }

    void visit(std::string url) {
        history.resize(++i);
        history.push_back(std::move(url));
    }

    auto back(const int steps) {
        i = std::max(0, i - steps);
        return history[i];
    }

    auto forward(const std::size_t steps) {
        i = std::min(history.size() - 1, i + steps);
        return history[i];
    }
};

} //namespace


#ifdef WANT_TESTS
TEST(BrowserHistory, TestSanity) {
    BrowserHistory history {"leetcode.com"};

    history.visit("google.com");
    history.visit("facebook.com");
    history.visit("youtube.com");

    EXPECT_EQ("facebook.com", history.back(1));
    EXPECT_EQ("google.com", history.back(1));
    EXPECT_EQ("facebook.com", history.forward(1));

    history.visit("linkedin.com");

    EXPECT_EQ("linkedin.com", history.forward(2));
    EXPECT_EQ("google.com", history.back(2));
    EXPECT_EQ("leetcode.com", history.back(7));
}
#endif
