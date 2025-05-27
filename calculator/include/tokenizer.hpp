#ifndef TOKENIZER
#define TOKENIZER

#include <vector>
#include <string>

struct Token;

namespace Tokenizer {
    std::vector<Token> tokenize(std::string &input);
};

#endif // Tokenizer
