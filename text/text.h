#pragma once


static inline constexpr auto
StartsWith(const std::string_view str, const std::string_view prefix) {
    return str.rfind(prefix, 0) == 0;
}
