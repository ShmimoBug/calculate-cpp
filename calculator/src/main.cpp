#include <iostream>

#include "journal.hpp"
#include "postfix_eval.hpp"
#include "tokenizer.hpp"
#include "str_util.hpp"

void print_options() {
    std::cout << "=== C++ Calculator ===\n";
    std::cout << " [e]xit\n";
    std::cout << " [l]ist - List out previous expression and result\n";
    std::cout << " [t]otal - List out the entire list of previous expressions and results\n";
}

enum LoopResponse {
    kExit=-1,
    kContinue=0,
    kExpression
};

int handle_non_expression(const std::string& input, const Journal& journal) {
    if (input.empty()) return LoopResponse::kContinue;

    int response = LoopResponse::kContinue;
    switch (input[0]) {
        case 'e':
            response = LoopResponse::kExit;
            break;
        case 'l':
            std::cout << journal.get_previous_eq();
            response = LoopResponse::kContinue;
            break;
        case 't':
            std::cout << journal.get_journal_total();
            response = LoopResponse::kContinue;
            break;
        default:
            response = LoopResponse::kExpression;
    }

    return response;
}

int main(int argc, char* argv[]) {
    std::string input;
    double result = -1.0f;
    std::vector<Token> tokens;
    Journal journal;

    print_options();
    while (1) {
        std::cout << "Enter postfix expression: ";
        std::getline(std::cin, input);
        input = trim(input);

        int response = handle_non_expression(input, journal);
        if (response == LoopResponse::kExit) {
            break;
        } else if (response == LoopResponse::kContinue) {
            continue;
        } 

        std::cout << "Expression: " << input << "\n";
        tokens = Tokenizer::tokenize(input);
        result = PostFix::evaluate(tokens);
        std::cout << "Result: " << result << "\n";

        journal.append_eq(tokens, result);
    }
    return 0;
}
