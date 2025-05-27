#include <algorithm>
#include <iostream>
#include <regex>

#include "token.hpp"
#include "tokenizer.hpp"

static std::vector<std::string> tokenize_str(std::string& input) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    while ((pos = input.find(" ")) != std::string::npos) {
        token = input.substr(0, pos);
        tokens.push_back(token);
        input.erase(0, pos+1);
    }
    tokens.push_back(input);

    return tokens;
}

std::vector<Token> Tokenizer::tokenize(std::string& input) {
    std::vector<Token> tokens;
    static const std::regex OPS{"[-+*/]"};

    std::vector<std::string> str_tok = tokenize_str(input);
    Token token;

    for (const auto& st : str_tok) {
        if (std::find_if(st.begin(), st.end(), ::isdigit) != st.end()) {
            token.val = std::stod(st);
            token.type = TokenType::kVal;
            tokens.push_back(token);
        } else {
            std::smatch m;
            if (std::regex_match(st, m , OPS)) {
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

