#pragma once

#include <Point.hpp>

// Implements transforamtion from user's coord system to window's

class Canvas
{
    Point m_center {}; // In windows coords
    Point m_prop_coefs{1, 1}; // Proportion coefs for x&y axes
    
public:

    Canvas(Point &center);
    Canvas(Point &center, Point &real_size, Point &pixel_size);
    Canvas();
    Point get_center();
    Point get_prop_coefs();
};

Point apply_canvas(Canvas &cnvs, Point &pnt);
ConcreteVector apply_canvas(Canvas &cnvs, ConcreteVector &cvec);