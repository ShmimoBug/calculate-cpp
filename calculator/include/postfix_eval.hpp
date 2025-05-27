#ifndef POSTFIX_EVAL_H
#define POSTFIX_EVAL_H

#include <vector>

struct Token;

namespace PostFix {
    double evaluate(const std::vector<Token>& tokens);
};

#endif // POSTFIX_EVAL_H
