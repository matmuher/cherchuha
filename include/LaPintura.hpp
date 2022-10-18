#pragma once

#include <Rectangle.hpp>

class LaPintura : public Rectangle
{
public:
    LaPintura(const Point& rect_center, float width, float height, Colors color = Colors::WHITE);
}