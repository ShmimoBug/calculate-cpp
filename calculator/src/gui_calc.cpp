#include "gui_calc.hpp"

#include <cstring>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

#include "gui/ui.hpp"
#include "journal.hpp"
#include "postfix_eval.hpp"
#include "tokenizer.hpp"
#include "token.hpp"

#define WIN_WIDTH  250
#define WIN_HEIGHT 300
#define TITLE "Calculate - C++"

int GuiCalc::main_loop() {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, TITLE);
    ClearWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMaxSize(WIN_WIDTH, WIN_WIDTH);
    SetTargetFPS(60);

    std::string input = "";
    double result = -1;
    std::vector<Token> tokens;
    Journal journal;

    UI::init(WIN_WIDTH, WIN_HEIGHT);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            UI::update(input, tokens, result, journal);
            UI::render(input);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
