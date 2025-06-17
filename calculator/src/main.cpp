#include "calculator.hpp"
#include "gui_calc.hpp"
#include <cstring>

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "cmd")==0) {
        return Calc::main_loop();
    } else if (strcmp(argv[1], "gui")==0) {
        return GuiCalc::main_loop();
    }

    return 0;
}
