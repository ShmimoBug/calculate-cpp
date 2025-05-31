#include "calculator.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "journal.hpp"
#include "postfix_eval.hpp"
#include "tokenizer.hpp"
#include "token.hpp"

#define EXPR 'x'
#define LAST 'l'
#define ALL  'a'
#define OPTS 'o'
#define EXIT 'e'

static std::string input;
static double result = -1;
static std::vector<Token> tokens;
static Journal journal;

#define NUM_OPTIONS 5
static const char *OPTIONS[NUM_OPTIONS] = {
    "E[x]pression - Enter a postfix (Reverse Polish) expression to be evaluated.",
    "[l]ast - Print out the previous expression and result.",
    "[a]ll - Print out the entire list of previous expressions and results.",
    "[o]ptions - List out these options.",
    "[e]xit - Exit the program."
};

static void print_option(const char *option) {
    std::cout << "\t" << option << "\n";
}

static void print_options() {
    std::cout << "=== C++ Calculator ===\n";
    for (size_t i = 0; i < NUM_OPTIONS; i++) {
        print_option(OPTIONS[i]);
    }
}

static void do_postfix() {
    std::cout << "Enter Expression\n";
    std::cout << "> ";
    std::getline(std::cin, input);
    tokens = Tokenizer::tokenize(input);
    result = PostFix::evaluate(tokens);
    std::cout << "Result: " << result << "\n";
    journal.append_eq(tokens, result);
} 

static void do_print_last() {
    std::cout << "Previous Expression:\n";
    std::cout << journal.get_previous_eq();
}

static void do_print_all() {
    std::cout << "All Previous Expressions:\n";
    std::cout << journal.get_journal_total();
}

int Calc::main_loop() {

    print_options();
    while (1) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        switch (input[0]) {
            case EXPR:
                do_postfix();
                break;
            case LAST:
                do_print_last();
                break;
            case ALL:
                do_print_all();
                break;
            case OPTS:
                print_options();
                break;
            case EXIT:
                return 0;
                break;
            default:
                std::cout << "Invalid option, try again!\n";
                break;
        }
    }

    return 1; // shouldn't get here!
}
