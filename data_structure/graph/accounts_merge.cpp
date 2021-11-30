#include "common_header.h"

#include "data_structure/disjoint_set.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Accounts Merge
 *
 * @reference   https://leetcode.com/problems/accounts-merge/
 *
 * Given a list of accounts where each element accounts[i] is a list of strings, where
 * the first element accounts[i][0] is a name, and the rest of the elements are emails
 * representing emails of the account. Now, we would like to merge these accounts. Two
 * accounts definitely belong to the same person if there is some common email to both
 * accounts. Note that even if two accounts have the same name, they may belong to
 * different people as people could have the same name. A person can have any number of
 * accounts initially, but all of their accounts definitely have the same name. After
 * merging the accounts, return the accounts in the following format: the first element
 * of each account is the name, and the rest of the elements are emails in sorted order.
 * The accounts themselves can be returned in any order.
 */
auto MergeAccounts(const std::vector<ArrayType> &accounts) {
    std::unordered_map<std::string_view, int> email_id_map;
    DisjointSet_Array disjoint_set(accounts.size());
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        const auto &an_account = accounts[i];
        for (std::size_t j = 1; j < an_account.size(); ++j) {
            const auto email = an_account[j];
            const auto [iter, inserted] = email_id_map.emplace(email, i);
            if (not inserted) {
                disjoint_set.Union(i, iter->second);
            }
        }
    }

    //ordered map for convenience
    std::map<int, ArrayType> id_accounts_map;
    for (const auto [email, id] : email_id_map) {
        id_accounts_map[disjoint_set.Find(id)].push_back(email);
    }

    std::vector<ArrayType> results;
    for (auto &[id, emails] : id_accounts_map) {
        std::sort(emails.begin(), emails.end());
        const auto account_name = accounts[id].front();
        results.push_back({account_name});
        results.back().insert(results.back().cend(), emails.cbegin(), emails.cend());
    }

    return results;
}

}//namespace


const std::vector<ArrayType> SAMPLE1 = {
    {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
    {"John", "johnsmith@mail.com", "john00@mail.com"},
    {"Mary", "mary@mail.com"},
    {"John", "johnnybravo@mail.com"}
};
const std::vector<ArrayType> EXPECTED1 = {
    {"John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"},
    {"Mary", "mary@mail.com"},
    {"John", "johnnybravo@mail.com"}
};

const std::vector<ArrayType> SAMPLE2 = {
    {"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe1@m.co"},
    {"Kevin", "Kevin3@m.co", "Kevin5@m.co", "Kevin0@m.co"},
    {"Ethan", "Ethan5@m.co", "Ethan4@m.co", "Ethan0@m.co"},
    {"Hanzo", "Hanzo3@m.co", "Hanzo1@m.co", "Hanzo0@m.co"},
    {"Fern", "Fern5@m.co", "Fern1@m.co", "Fern0@m.co"}
};
const std::vector<ArrayType> EXPECTED2 = {
    {"Gabe", "Gabe0@m.co", "Gabe1@m.co", "Gabe3@m.co"},
    {"Kevin", "Kevin0@m.co", "Kevin3@m.co", "Kevin5@m.co"},
    {"Ethan", "Ethan0@m.co", "Ethan4@m.co", "Ethan5@m.co"},
    {"Hanzo", "Hanzo0@m.co", "Hanzo1@m.co", "Hanzo3@m.co"},
    {"Fern", "Fern0@m.co", "Fern1@m.co", "Fern5@m.co"}
};


THE_BENCHMARK(MergeAccounts, SAMPLE1);

SIMPLE_TEST(MergeAccounts, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(MergeAccounts, TestSAMPLE2, EXPECTED2, SAMPLE2);
