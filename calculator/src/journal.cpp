#include "journal.hpp"

void Journal::append_eq(const std::vector<Token>& tokens, double result) {
    m_previous.clear();
    m_previous.str(" ");

    for (const Token& t : tokens) {
        if (t.type == TokenType::kOperator) {
            m_previous << "OP: " << t.op << "\n";
        } else {
            m_previous << "VAL: " << t.val << "\n";
        }
    }

    m_previous << "RESULT: " << result << "\n";

    m_total << m_previous.str();
}

std::string Journal::get_previous_eq() const {
    return m_previous.str();
}

std::string Journal::get_journal_total() const {
    return m_total.str();
}
