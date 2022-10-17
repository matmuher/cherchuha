#include "Button.hpp"

Button::Button(const Point& button_center, float width, float height, Colors button_color) :
    Rectangle(button_center, width, height, button_color)
{}

void Button::change_color()
{
    if (m_is_pressed)
    {
        set_color(Colors((unsigned) get_color() & PRESS));
    }
    else
    {
        set_color(Colors((unsigned) get_color() & UN_PRESS));
    }
}