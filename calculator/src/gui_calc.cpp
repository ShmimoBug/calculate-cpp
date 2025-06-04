#include "gui_calc.hpp"

#include <cstring>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

#include "gui/buttons.hpp"
#include "journal.hpp"
#include "postfix_eval.hpp"
#include "tokenizer.hpp"
#include "token.hpp"

#define WIN_WIDTH  250
#define WIN_HEIGHT 300
#define TITLE "Calculate - C++"

int GuiCalc::main_loop() {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, TITLE);
    SetTargetFPS(60);

    char input[256] = "\0";
    size_t in_len = 0;
    double result = -1;
    std::vector<Token> tokens;
    Journal journal;

    Buttons::init(WIN_WIDTH, WIN_HEIGHT);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            Buttons::update(input, in_len, tokens, result, journal);
            Buttons::render(input);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
