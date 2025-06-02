#ifndef STR_UTIL_H
#define STR_UTIL_H

#include <string>

namespace str_util {
    std::string trim(const std::string& str);
    std::string replace_all_of(const std::string& str, char to_replace, char replace_with);
    std::string remove_whitespace(const std::string& str);
} // namespace str_util

#endif // STR_UTIL_H
