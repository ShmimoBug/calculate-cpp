#include "gui/button.hpp"

Button::Button(const Rectangle& bounds, const Color& reg_color, const Color& hover_color, const Color& pressed_color, const std::string& text) :
    m_bounds(bounds), m_current_color(reg_color), m_reg_color(reg_color), m_hover_color(hover_color), m_presed_color(pressed_color), m_text(text) {}


void Button::set_position(float x, float y) {
    m_bounds.x = x;
    m_bounds.y = y;
}

void Button::set_size(float width, float height) {
    m_bounds.width = width;
    m_bounds.height = height;
}

const Vector2 Button::get_position() const {
    return (Vector2){m_bounds.x, m_bounds.y};
}

const Vector2 Button::get_size() const {
    return (Vector2){m_bounds.width, m_bounds.height};
}

const std::string& Button::get_text() const {
    return m_text;
}

bool Button::hover() {
    if (CheckCollisionPointRec(GetMousePosition(), m_bounds)) {
        m_current_color = m_hover_color;
        return true;
    }

    m_current_color = m_reg_color;
    return false;
}

bool Button::is_pressed() {
    if (hover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        m_current_color = m_presed_color;
        return true;
    }

    return false;
}

void Button::render() {
    DrawRectangleRec(m_bounds, m_current_color);
    DrawText(m_text.c_str(), m_bounds.x+(m_bounds.width/2.f), m_bounds.y+(m_bounds.height/2.f), m_bounds.width*0.1f, BLACK);
}
