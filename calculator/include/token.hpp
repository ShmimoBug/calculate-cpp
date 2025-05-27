#ifndef TOKEN
#define TOKEN

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

#endif // TOKEN
