#include <Rectangle.hpp>

class Button : public Rectangle
{
    const unsigned PRESS    = 0x11111155;
    const unsigned UN_PRESS = 0x111111FF;

    bool m_is_pressed = false;

    void change_color();

public:

    Button(const Point& button_center, float width, float height, Colors button_color = Colors::RED);
};
