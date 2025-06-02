#include <algorithm>
#include <iostream>
#include <stack>

#include "str_util.hpp"
#include "token.hpp"
#include "tokenizer.hpp"

static bool char_is_operator(char ch) {
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
    };

    return false;
}

static std::vector<std::string> infix_tokenize_str(std::string& input) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    size_t i = 0;
    for (;i < input.size(); i++) {
        if (char_is_operator(input[i])) {
           token = input.substr(pos, i-pos); // get string before operator
           tokens.push_back(token);
           pos = i;
           token = input.substr(pos, 1); // get operator
           tokens.push_back(token);
           pos++;
        }
    }

    tokens.push_back(input.substr(pos, i-pos));
    return tokens;
}

static std::vector<std::string> postfix_tokenize_str(std::string& input) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    input = str_util::replace_all_of(input, '\t', ' ');
    while ((pos = input.find(" ")) != std::string::npos) {
        token = str_util::trim(input.substr(0, pos));
        tokens.push_back(token);
        input.erase(0, pos+1);
    }
    tokens.push_back(input);

    return tokens;
}

std::vector<Token> Tokenizer::postfix_tokenize(std::string& input) {
    std::vector<Token> tokens;

    std::vector<std::string> str_tok = postfix_tokenize_str(input);
    Token token;

    for (const auto& st : str_tok) {
        if (std::find_if(st.begin(), st.end(), ::isdigit) != st.end()) {
            token.val = std::stod(st);
            token.type = TokenType::kVal;
            tokens.push_back(token);
        } else {
            if (char_is_operator(st[0])) {
                token.op = st[0];
                token.type = TokenType::kOperator;
                tokens.push_back(token);
            } else {
                std::cerr << "Invalid Input\n";
                return {};
            }
        }
    }
    
    return tokens;
}

int precedence(const Token &token) {
    switch (token.op) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
    }

    return -1; // shouldn't get here!
}

std::vector<Token> Tokenizer::infix_tokenize(std::string &input) {
    std::vector<Token> tokens;
    std::vector<std::string> str_toks = infix_tokenize_str(input);
    Token token;

    std::stack<Token> tok_stack;
    for (const auto &st : str_toks) {
        if (std::find_if(st.begin(), st.end(), ::isdigit) != st.end()) {
            token.val = std::stod(st);
            token.type = TokenType::kVal;
            tokens.push_back(token);
        } else {
            if (char_is_operator(st[0])) {
                token.op = st[0];
                token.type = TokenType::kOperator;
                
                while (!tok_stack.empty() && precedence(token) <= precedence(tok_stack.top())) {
                    tokens.push_back(tok_stack.top());
                    tok_stack.pop();
                }
                tok_stack.push(token);
            }
        }
    }

    while (!tok_stack.empty()) {
        tokens.push_back(tok_stack.top());
        tok_stack.pop();
    }

    return tokens;
}
