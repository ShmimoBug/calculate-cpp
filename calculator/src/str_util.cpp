#include "str_util.hpp"

#include <algorithm>
#include <iostream>

std::string str_util::trim(const std::string& str) {
    const auto str_begin = str.find_first_not_of(" \t");
    if (str_begin == std::string::npos) {
        return ""; // no content
    }

    const auto str_end = str.find_last_not_of(" \t");
    const auto str_range = str_end-str_begin+1;
    return str.substr(str_begin, str_range);
}

std::string str_util::replace_all_of(const std::string& str, char to_replace, char replace_with) {
    std::string new_str = str;
    size_t pos = 0;
    while ((pos = new_str.find(to_replace)) != std::string::npos) {
        new_str[pos] = replace_with;
    }

    return new_str;
}

std::string str_util::remove_whitespace(const std::string& str) {
    std::string new_str = str;
    new_str.erase(std::remove_if(new_str.begin(), new_str.end(), ::iswspace), new_str.end());
    return new_str;
}

