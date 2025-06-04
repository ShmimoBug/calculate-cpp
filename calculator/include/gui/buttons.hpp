#ifndef BUTTONS_H
#define BUTTONS_H

#include <vector>
#include <cstddef>

struct Token;
class Journal;

namespace Buttons {

    void init(int win_width, int win_height);
    void update(char input[256], size_t &in_len, std::vector<Token>& tokens, double &result, Journal &journal);
    void render(char *input);

} // namespace Buttons

#endif // BUTTONS_H
