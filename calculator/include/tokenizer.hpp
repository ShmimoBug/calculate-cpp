#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

struct Token;

namespace Tokenizer {
    std::vector<Token> tokenize(std::string &input);
};

#endif // TOKENIZER_H
