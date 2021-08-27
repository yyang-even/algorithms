#pragma once


template <typename Container>
static inline constexpr auto
SplitIntoWords_StringStream(const std::string &sentence) {
    std::stringstream ss(sentence);

    Container outputs;
    for (std::string word; ss >> word;) {
        outputs.push_back(std::move(word));
    }

    return outputs;
}
