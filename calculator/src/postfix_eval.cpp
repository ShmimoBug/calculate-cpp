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

        if (eq_stack.size() < 2) {
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
            case '^':
                result = pow(val1, val2);
                break;
            default:
                std::cerr << "ERROR: Invalid Operator\n";
                return -1;
        }

        eq_stack.push(result);
    }

    if (eq_stack.size() > 1) {
        std::cerr << "ERROR: Too Many Operands\n";
        return -1;
    }

    return eq_stack.top();
}
