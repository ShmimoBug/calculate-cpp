#ifndef POSTFIX_EVAL
#define POSTFIX_EVAL

#include <vector>

struct Token;

namespace PostFix {
    double evaluate(const std::vector<Token>& tokens);
};

#endif // POSTFIX_EVAL
