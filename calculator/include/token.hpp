#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
    kOperator=0,
    kVal
};

struct Token {
    union {
        char op;
        double val;
    };

    TokenType type;
};

#endif // TOKEN_H
