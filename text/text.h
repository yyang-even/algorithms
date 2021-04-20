#pragma once

static inline std::string_view sub_string(const std::string_view sv,
                                          std::size_t pos,
                                          std::size_t len = std::string_view::npos) {
    return sv.substr(pos, len);
}
