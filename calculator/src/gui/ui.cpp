#include "gui/ui.hpp"

#include <raylib.h>
#include <string>
#include <cstring>
#include <iostream>

#include "gui/button.hpp"
#include "journal.hpp"
#include "postfix_eval.hpp"
#include "tokenizer.hpp"
#include "token.hpp"

#define INPUT_MAX 128

struct Layout {
    int row, column;
    std::string label;
};

#define REG_COLOR LIGHTGRAY
#define HOVER_COLOR GRAY
#define PRESSED_COLOR DARKGRAY

#define NUM_BUTTONS 20
static Button buttons[NUM_BUTTONS];
static Layout layout[NUM_BUTTONS] = {
    {0, 0, "("}, {0, 1, ")"}, {0, 2, "^"}, {0, 3, "AC"},
    {1, 0, "7"}, {1, 1, "8"}, {1, 2, "9"}, {1, 3, "/"},
    {2, 0, "4"}, {2, 1, "5"}, {2, 2, "6"}, {2, 3, "*"},
    {3, 0, "1"}, {3, 1, "2"}, {3, 2, "3"}, {3, 3, "+"},
    {4, 0, "0"}, {4, 1, "."}, {4, 2, "="}, {4, 3, "-"},
                                           
};
static bool evaluated = false;

void UI::init(int win_width, int win_height) {
    float button_width = (static_cast<float>(win_width)/4.f);
    float button_height = ((static_cast<float>(win_height)-50.f)/5.f);

    for (int i = 0; i < NUM_BUTTONS; i++) {
        Button &button = buttons[i];
        button = Button((Rectangle){
                .x = (button_width*layout[i].column),
                .y = (button_height*layout[i].row)+50.f,
                .width=button_width,
                .height=button_height
                }, 
                REG_COLOR, 
                HOVER_COLOR, 
                PRESSED_COLOR, 
                layout[i].label);
    }
}

void UI::update(std::string& input, std::vector<Token>& tokens, double &result, Journal &journal) {
    int key = GetCharPressed();
    while (key > 0) {
        if (evaluated) {
            input.clear();
            evaluated = false;
        }

        if ((key > 32) && (key <= 125) && (input.length() < INPUT_MAX)) {
            input += static_cast<char>(key);
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (input == "list") {
            std::cout << journal.get_journal_total();
            input.clear();
        } else {
            tokens = Tokenizer::infix_tokenize(input);
            result = PostFix::evaluate(tokens);
            input.clear();
            input += std::to_string(result);
            journal.append_eq(tokens, result);
            evaluated = true;
        }

    }

    for (Button &button : buttons) {
        if (button.is_pressed()) {
            if (button.get_text() != "=" && button.get_text() != "AC" && input.length() < INPUT_MAX) {
                if (evaluated) {
                    input.clear();
                    evaluated = false;
                }
                input += button.get_text();
            } else {
                if (button.get_text() == "AC") {
                    input.clear();
                } else {
                    tokens = Tokenizer::infix_tokenize(input);
                    result = PostFix::evaluate(tokens);
                    input.clear();
                    input = std::to_string(result);
                    journal.append_eq(tokens, result);
                    evaluated = true;
                }
            }
        }
    }
}

void UI::render(const std::string& input) {
    DrawText(input.c_str(), 0, 0, 20, BLACK);
    for (Button &button : buttons) {
        button.render();
    }
}
