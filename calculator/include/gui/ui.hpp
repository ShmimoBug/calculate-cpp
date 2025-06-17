#ifndef UI_H
#define UI_H

#include <vector>
#include <string>

struct Token;
class Journal;

namespace UI {

    void init(int win_width, int win_height);
    void update(std::string& input, std::vector<Token>& tokens, double &result, Journal &journal);
    void render(const std::string& input);

} // namespace Buttons

#endif // UI_H
