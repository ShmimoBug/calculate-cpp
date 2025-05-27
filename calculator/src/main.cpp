#include <algorithm>
#include <iostream>
#include <vector>
#include <regex>
#include <stack>

#include "postfix_eval.hpp"
#include "tokenizer.hpp"

std::string trim(const std::string &str);

std::vector<std::string> InputGetTokens(std::string& str) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(" ")) != std::string::npos) {
        token = trim(str.substr(0, pos));
        tokens.push_back(token);
        str.erase(0, pos+1);
    }
    tokens.push_back(str);

    return tokens;
}

enum TokenType {
    kOperator=0,
    kValue
};

struct Token {
    union {
        char op;
        double val;
    };

    TokenType type;
};

std::vector<Token> StrToTokens(const std::vector<std::string>& str_tok) {
    std::vector<Token> tokens;
    static const std::regex OPS{"[-+*/]"};

    for (const auto& st : str_tok) {
        if (std::find_if(st.begin(), st.end(), ::isdigit) != st.end()) {
            Token token;
            token.val = std::stod(st);
            token.type = TokenType::kValue;
            tokens.push_back(token);
        } else {
            std::smatch m;
            if (std::regex_match(st, m, OPS)) {
                Token token;
                token.op = st[0];
                token.type = TokenType::kOperator;
                tokens.push_back(token);
            } else {
                std::cerr << "Invalid syntax!\n";
                return {};
            }
        }
    }

    return tokens;
}

double EqEvalPostfix(const std::vector<Token>& tokens) {
    double result;
    std::stack<double> eq_stack;

    if (tokens.empty()) {
        return -1.0;
    }

    for (const auto& token : tokens) {
        if (token.type == TokenType::kValue) {
            eq_stack.push(token.val);
        } else if (token.type == TokenType::kOperator) {
            if (eq_stack.size() < 2) {
                std::cerr << "Invalid Syntax!\n";
                return -1.0;
            }

            double val2 = eq_stack.top(); eq_stack.pop();
            double val1 = eq_stack.top(); eq_stack.pop();
            switch (token.op) {
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
                default:
                    std::cerr << "Invalid operator!\n";
                    return -1.0;
                    break;
            }

            eq_stack.push(result);
        }
    }

    return eq_stack.top();
}

std::string trim(const std::string& str) {
    const auto str_begin = str.find_first_not_of(" \t");
    if (str_begin == std::string::npos) {
        return ""; // no content
    }

    const auto str_end = str.find_last_not_of(" \t");
    const auto str_range = str_end-str_begin+1;
    return str.substr(str_begin, str_range);
}

int main(int argc, char* argv[]) {
    std::string input;
    double result = -1.0f;
    std::vector<Token> tokens;

    while (1) {
        std::cout << "Enter postfix expression: ";
        std::getline(std::cin, input);
        input = trim(input);
        if (input[0] == 'e') break;
        if (input[0] == 'l') {
            for (const Token& t : tokens) {
                if (t.type == TokenType::kOperator) {
                    std::cout << "OP: " << t.op << "\n";
                } else {
                    std::cout << "VAL: " << t.val << "\n";
                }
            }

            continue;
        }

        std::cout << "Expression: " << input << "\n";
        tokens = Tokenizer::tokenize(input);
        result = PostFix::evaluate(tokens);
        std::cout << "Result: " << result << "\n";
    }
    return 0;
}
