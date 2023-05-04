#include "common_header.h"


namespace {

/** Dota2 Senate
 *
 * @reference   https://leetcode.com/problems/dota2-senate/
 *
 * In the world of Dota2, there are two parties: the Radiant and the Dire.
 * The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a
 * change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each
 * senator can exercise one of the two rights:
 *  Ban one senator's right: A senator can make another senator lose all his rights in this and all the
 *  following rounds.
 *  Announce the victory: If this senator found the senators who still have rights to vote are all from
 *  the same party, he can announce the victory and decide on the change in the game.
 * Given a string senate representing each senator's party belonging. The character 'R' and 'D'
 * represent the Radiant party and the Dire party. Then if there are n senators, the size of the given
 * string will be n.
 * The round-based procedure starts from the first senator to the last senator in the given order. This
 * procedure will last until the end of voting. All the senators who have lost their rights will be
 * skipped during the procedure.
 * Suppose every senator is smart enough and will play the best strategy for his own party.  Predict
 * which party will finally announce the victory and change the Dota2 game. The output should be
 * "Radiant" or "Dire".
 */
std::string Dota2Senate(const std::string_view senate) {
    std::queue<char> q;
    int radiant_count = 0;
    int dire_count = 0;

    for (const auto s : senate) {
        q.push(s);
        if (s == 'R') {
            ++radiant_count;
        } else {
            ++dire_count;
        }
    }

    int radiant_floating_ban = 0;
    int dire_floating_ban = 0;

    while (radiant_count and dire_count) {
        const auto s = q.front();
        q.pop();

        if (s == 'D') {
            if (dire_floating_ban) {
                --dire_floating_ban;
                --dire_count;
            } else {
                ++radiant_floating_ban;
                q.push('D');
            }
        } else {
            if (radiant_floating_ban) {
                --radiant_floating_ban;
                --radiant_count;
            } else {
                ++dire_floating_ban;
                q.push('R');
            }
        }
    }

    return radiant_count ? "Radiant" : "Dire";
}

} //namespace


THE_BENCHMARK(Dota2Senate, "RD");

SIMPLE_TEST(Dota2Senate, TestSAMPLE1, "Radiant", "RD");
SIMPLE_TEST(Dota2Senate, TestSAMPLE2, "Dire", "RDD");
