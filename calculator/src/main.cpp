#include <iostream>

#include "journal.hpp"
#include "postfix_eval.hpp"
#include "tokenizer.hpp"

std::string trim(const std::string& str) {
    const auto str_begin = str.find_first_not_of(" \t");
    if (str_begin == std::string::npos) {
        return ""; // no content
    }

    const auto str_end = str.find_last_not_of(" \t");
    const auto str_range = str_end-str_begin+1;
    return str.substr(str_begin, str_range);
}

void print_options() {
    std::cout << "=== C++ Calculator ===\n";
    std::cout << " [e]xit\n";
    std::cout << " [l]ist - List out previous expression and result\n";
    std::cout << " [t]otal - List out the entire list of previous expressions and results\n";
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
        if (input[0] == 'e') break;
        if (input[0] == 'l') {
            std::cout << journal.get_previous_eq();
            continue;
        } 
        if (input[0] == 't') {
            std::cout << journal.get_journal_total();
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
