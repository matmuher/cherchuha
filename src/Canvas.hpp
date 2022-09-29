#pragma once

#include <Point.hpp>

// Implements transforamtion from user's coord system to window's

class Canvas
{
    Point m_center {}; // In windows coords
    
public:

    Canvas(Point &center);
    Canvas();
    Point get_center();
};

Point apply_canvas(Canvas &cnvs, Point &pnt);