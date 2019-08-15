#include "common_header.h"


namespace {

/** Remove spaces from a given string
 *
 * @reference   https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
 * @reference   C++ Program to remove spaces from a string
 *              https://www.geeksforgeeks.org/c-program-remove-spaces-string/
 *
 * Given a string, remove all spaces from the string and return it.
 * Expected time complexity is O(n) and only one traversal of string.
 */
auto RemoveSpaces(std::string input) {
    auto output_iter = input.begin();
    for (auto input_iter = input.begin(); input_iter != input.end(); ++input_iter) {
        if (not std::isspace(*input_iter)) {
            *output_iter++ = *input_iter;
        }
    }

    input.resize(output_iter - input.begin());
    return input;
}


/**
 * @reference   Removing spaces from a string using Stringstream
 *              https://www.geeksforgeeks.org/removing-spaces-string-using-stringstream/
 */
auto RemoveSpaces_StringStream(std::string input) {

    std::stringstream ss(input);
    for (input.clear(); ss;) {
        std::string word;
        ss >> word;
        input.append(std::move(word));
    }

    return input;
}


template <typename UnaryPredicate>
auto RemoveCharacters_Partition(std::string input, const UnaryPredicate p) {
    const auto end = std::stable_partition(input.begin(), input.end(), p);
    return input.substr(0, std::distance(input.begin(), end));
}

auto RemoveSpaces_Partition(const std::string &input) {
    return RemoveCharacters_Partition(input, ToNegationLambda(std::isspace));
}


/**
 * @reference   Move spaces to front of string in single traversal
 *              https://www.geeksforgeeks.org/move-spaces-front-string-single-traversal/
 */


/** Remove all occurrences of a character in a string
 *
 * @reference   https://www.geeksforgeeks.org/remove-all-occurrences-of-a-character-in-a-string/
 */
auto RemoveCharactersByKey_Partition(const std::string &input, const std::string::value_type key) {
    return RemoveCharacters_Partition(input, [key](const auto c) {
        return key != c;
    });
}


/** Removing punctuations from a given string
 *
 * @reference   https://www.geeksforgeeks.org/removing-punctuations-given-string/
 */
auto RemovePunctuations_Partition(const std::string &input) {
    return RemoveCharacters_Partition(input, ToNegationLambda(std::ispunct));
}


/** Remove characters from the first string which are present in the second string
 *
 * @reference   https://www.geeksforgeeks.org/remove-characters-from-the-first-string-which-are-present-in-the-second-string/
 */
auto RemoveCharactersPresentInTheSecond_Partition(const std::string &input,
        const std::string &mask) {
    std::unordered_set<std::string::value_type> counter;
    for (const auto c : mask) {
        counter.insert(c);
    }

    return RemoveCharacters_Partition(input, [&counter](const auto c) {
        return counter.find(c) == counter.cend();
    });
}

}//namespace


SIMPLE_BENCHMARK(RemoveSpaces, "g  eeks   for ge  eeks  ");

SIMPLE_TEST(RemoveSpaces, TestSAMPLE1, "geeksforgeeeks", "g  eeks   for ge  eeks  ");


SIMPLE_BENCHMARK(RemoveSpaces_StringStream, "g  eeks   for ge  eeks  ");

SIMPLE_TEST(RemoveSpaces_StringStream, TestSAMPLE1, "geeksforgeeeks", "g  eeks   for ge  eeks  ");


SIMPLE_BENCHMARK(RemoveSpaces_Partition, "g  eeks   for ge  eeks  ");

SIMPLE_TEST(RemoveSpaces_Partition, TestSAMPLE1, "geeksforgeeeks", "g  eeks   for ge  eeks  ");


SIMPLE_BENCHMARK(RemoveCharactersByKey_Partition, "g  eeks   for ge  eeks  ", ' ');

SIMPLE_TEST(RemoveCharactersByKey_Partition, TestSAMPLE1, "geeksforgeeeks",
            "g  eeks   for ge  eeks  ", ' ');
SIMPLE_TEST(RemoveCharactersByKey_Partition, TestSAMPLE2, "gksforgks", "geeksforgeeks", 'e');
SIMPLE_TEST(RemoveCharactersByKey_Partition, TestSAMPLE3, "eeksforeeks", "geeksforgeeks", 'g');


SIMPLE_BENCHMARK(RemovePunctuations_Partition, "%welcome' to @geeksforgeek<s");

SIMPLE_TEST(RemovePunctuations_Partition, TestSAMPLE1, "welcome to geeksforgeeks",
            "%welcome' to @geeksforgeek<s");
SIMPLE_TEST(RemovePunctuations_Partition, TestSAMPLE2, "Hello he said and went",
            "Hello!!!, he said ---and went.");


SIMPLE_BENCHMARK(RemoveCharactersPresentInTheSecond_Partition, "geeksforgeeks", "mask");

SIMPLE_TEST(RemoveCharactersPresentInTheSecond_Partition, TestSAMPLE1, "geeforgee",
            "geeksforgeeks", "mask");
