#ifndef JOURNAL_H
#define JOURNAL_H

#include <sstream>
#include <vector>

#include "token.hpp"

/*
 * Journal
 *
 * Description: Stores the a list of all user inputs that can be requested and 
 * presented back to the user at anytime. great for debuggin!
 * */
class Journal {
public:
    void append_eq(const std::vector<Token>& tokens, double result);
    std::string get_previous_eq() const;
    std::string get_journal_total() const;
private:
    std::stringstream m_previous;
    std::stringstream m_total;
};

#endif // JOUNRAL_H
