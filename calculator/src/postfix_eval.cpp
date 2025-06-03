#include <cmath>
#include <iostream>
#include <stack>

#include "postfix_eval.hpp"
#include "token.hpp"

double PostFix::evaluate(const std::vector<Token>& tokens) {
    double result;
    std::stack<double> eq_stack;

    if (tokens.empty()) return -1;

    for (const auto& t : tokens) {
        if (t.type == TokenType::kVal) {
            eq_stack.push(t.val);
            continue;
        } 

        /*
         * In Postfix notation, whenever an operator is reached, there should be no less
         * than two values on the stack, if there is, the user has not followed proper
         * notation, and should be alerted of such.
         * */
        if (eq_stack.size() < 2) {
            if (t.op == '-' && !eq_stack.empty()) {
                eq_stack.top() *= -1.0;
                continue;
            }

            std::cerr << "ERROR: too many operators\n";
            return -1;
        }

        double val2 = eq_stack.top(); eq_stack.pop();
        double val1 = eq_stack.top(); eq_stack.pop();
        switch (t.op) {
            case '+':
                result = val1 + val2;
                break;
            case '-':
                result = val1 - val2;
                break;
            case '*':
                result = val1 * val2;
                break;
            case '/':
                result = val1 / val2;
                break;
            case '^':
                result = pow(val1, val2);
                break;
            default:
                std::cerr << "ERROR: Invalid Operator\n";
                return -1;
        }

        eq_stack.push(result);
    }

    /* if the stack has more then the final result, it means there weren't enough operators for all the operands.
     * Rather than return whatever is on the top of the stack, alert the user of their error.
     * */ 
    if (eq_stack.size() > 1) {
        std::cerr << "ERROR: Too Many Operands\n";
        return -1;
    }

    return eq_stack.top();
}
