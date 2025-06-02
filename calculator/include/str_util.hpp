#ifndef STR_UTIL_H
#define STR_UTIL_H

#include <string>

namespace str_util {
    // Removes leading and trailing whitespace
    std::string trim(const std::string& str);
    // Replaces all of a given character with another
    std::string replace_all_of(const std::string& str, char to_replace, char replace_with);
    // Removes all the whitespace in a string; used for infix expressions which don't require percise spacing
    std::string remove_whitespace(const std::string& str);
} // namespace str_util

#endif // STR_UTIL_H
