cmake_minimum_required(VERSION 3.22.1)

project(calculator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    calculator/src/main.cpp
    calculator/src/tokenizer.cpp
    calculator/src/postfix_eval.cpp
    calculator/src/journal.cpp
    calculator/src/str_util.cpp
    calculator/src/calculator.cpp
    calculator/src/gui_calc.cpp
    calculator/src/gui/ui.cpp
    calculator/src/gui/button.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC calculator/include)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
