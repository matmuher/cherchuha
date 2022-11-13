#pragma once

#include <Rectangle.hpp>

class Button : public Rectangle
{
    const unsigned PRESS    = 0xFFFFFF55;
    const unsigned UN_PRESS = 0x000000FF;
    const float kStdSize = 100;
    const Colors kStdColor = Colors::RED;

    bool m_is_pressed = false;

    void change_color();

public:

    Button(const Point& button_center, float width, float height, Colors button_color = Colors::RED);
    Button();

    bool is_pressed();

    Button& operator= (const Button& btn);
    bool click();
    void press();
    void unpress();
};
