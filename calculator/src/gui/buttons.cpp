#include "gui/buttons.hpp"

#include <raylib.h>
#include <string>
#include <cstring>
#include <iostream>

#include "journal.hpp"
#include "postfix_eval.hpp"
#include "tokenizer.hpp"
#include "token.hpp"

struct Button {
    Rectangle bounds;
    Color color;
    Color reg_color;
    Color hover_color;
    Color pressed_color;
    std::string text;

    bool Hover() {
        if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
            color = hover_color;
            return true;
        }

        color = reg_color;
        return false;
    }

    bool IsPressed() {
        if (Hover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            color = pressed_color;
            return true;
        }

        return false;
    }

    void Render() {
        DrawRectangleRec(bounds, color);
        DrawText(text.c_str(), bounds.x+(bounds.width/2.f), bounds.y+(bounds.height/2.f), bounds.width*0.1, BLACK);
    }
};

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

void Buttons::init(int win_width, int win_height) {
    float button_width = (static_cast<float>(win_width)/4.f);
    float button_height = ((static_cast<float>(win_height)-50.f)/5.f);
    float y_offset = 0.0f;

    std::cout << "button_width: " << button_width << "\n";
    std::cout << "button_height: " << button_height << "\n";

    for (int i = 0; i < NUM_BUTTONS; i++) {
        Button &button = buttons[i];
        button.bounds = (Rectangle){
            .x = (button_width*layout[i].column),
            .y = (button_height*layout[i].row)+50.f,
            .width = button_width,
            .height = button_height
        };

        std::cout << "x: " << button.bounds.x << " y: " << button.bounds.y << "\n";

        button.reg_color = REG_COLOR;
        button.hover_color = HOVER_COLOR;
        button.pressed_color = PRESSED_COLOR;
        button.text = layout[i].label;
    }
}

void Buttons::update(char *input, std::vector<Token>& tokens, double &result, Journal &journal) {
    for (Button &button : buttons) {
        if (button.IsPressed()) {
            if (button.text != "=" && button.text != "AC") {
                if (evaluated) {
                    input[0] = '\0';
                    evaluated = false;
                }
                strcat(input, button.text.c_str());
            } else {
                if (button.text == "AC") {
                    input[0] = '\0';
                    evaluated = false;
                } else {
                    std::string input_str = input;
                    tokens = Tokenizer::infix_tokenize(input_str);
                    result = PostFix::evaluate(tokens);
                    sprintf(input, "%lf", result);
                    journal.append_eq(tokens, result);
                    evaluated = true;
                }
            }
        }
    }
}

void Buttons::render(char *input) {
    DrawText(input, 0, 0, 20, BLACK);
    for (Button &button : buttons) {
        button.Render();
    }
}
