#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

struct Token;

namespace Tokenizer {
    /*
     * Given a user inputted string, turn the string into tokens representing either 
     * a number value or a mathematical operator, this list is what gets evaluated to a final result.
     * The tokens should be in the order of a postfix expression, although that depends on proper
     * user input.
     * */
    std::vector<Token> postfix_tokenize(std::string &input);
    
    /*
     * Given a user inputted string, turn the string into tokens representing either 
     * a number value or a mathematical operator, this function transforms 
     * the user input, which is assumed to be in infix notation, to a postfix list
     * of tokens. 
     * */
    std::vector<Token> infix_tokenize(std::string &input);
};

#endif // TOKENIZER_H
