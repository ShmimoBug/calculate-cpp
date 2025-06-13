#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <string>

class Button {
public:
    Button(const Rectangle& bounds={0}, 
            const Color& reg_color=LIGHTGRAY, 
            const Color& hover_color=GRAY, 
            const Color& pressed_color=DARKGRAY, 
            const std::string& text="");

    void set_position(float x, float y);
    void set_size(float width, float height);

    const Vector2 get_position() const;
    const Vector2 get_size() const;
    const std::string& get_text() const;

    bool hover();
    bool is_pressed();

    void render();

private:
    Rectangle m_bounds = { 0 };
    Color m_current_color = BLACK;
    Color m_reg_color = BLACK;
    Color m_hover_color = BLACK;
    Color m_presed_color = BLACK;
    std::string m_text = "";
};

#endif // BUTTON_H
