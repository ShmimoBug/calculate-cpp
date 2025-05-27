#include "str_util.hpp"

std::string trim(const std::string& str) {
    const auto str_begin = str.find_first_not_of(" \t");
    if (str_begin == std::string::npos) {
        return ""; // no content
    }

    const auto str_end = str.find_last_not_of(" \t");
    const auto str_range = str_end-str_begin+1;
    return str.substr(str_begin, str_range);
}

