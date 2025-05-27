#ifndef JOURNAL
#define JOURNAL

#include <sstream>
#include <vector>

#include "token.hpp"

class Journal {
public:
    void append_eq(const std::vector<Token>& tokens, double result);
    std::string get_previous_eq() const;
    std::string get_journal_total() const;
private:
    std::stringstream m_previous;
    std::stringstream m_total;
};

#endif // JOUNRAL
