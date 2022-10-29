#include <Button.hpp>

Button::Button(const Point& button_center, float width, float height, Colors button_color) :
    Rectangle(button_center, width, height, button_color)
{}

Button::Button() :
    Button(Point(0, 0), kStdSize, kStdSize, kStdColor)
{}

void Button::change_color()
{
    if (m_is_pressed)
    { 
        set_color(Colors((unsigned) get_color() & PRESS));
    }
    else
    {
        set_color(Colors((unsigned) get_color() | UN_PRESS));
    }
}

bool Button::click()
{
    m_is_pressed = m_is_pressed ? false : true;
    change_color(); // May be transfer color change to draw function?

    return m_is_pressed;
}

void Button::press()
{
    m_is_pressed = true;
    change_color();
}

void Button::unpress()
{
    m_is_pressed = false;
    change_color();
}

bool Button::is_pressed()
{
    return m_is_pressed;
}