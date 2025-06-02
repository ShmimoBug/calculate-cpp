#ifndef POSTFIX_EVAL_H
#define POSTFIX_EVAL_H

#include <vector>

struct Token;

namespace PostFix {
    /*
     * Given a list of tokens, evaluates them as if they were a postfix mathematical expression.
     * The function will check if the tokens are in the correct format, and the expression put 
     * in can be evaluated. If the user inputs an invalid expression, the function alerts the user
     * and returns -1
     * */
    double evaluate(const std::vector<Token>& tokens);
};

#endif // POSTFIX_EVAL_H
