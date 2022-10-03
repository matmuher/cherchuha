#pragma once

#include <iostream>

class Point // I have hesitations about class naming, cause all operations belong to radius Vector class
{
    float m_x {}, m_y {};

public:

    // Ctors
    Point (float x, float y);
    Point ();
    Point (const Point& pnt);

    // Dtor
    ~Point ();

    // Overload
    friend std::ostream& operator<< (std::ostream &cout, Point pnt);
    friend Point operator- (Point &pnt1, Point &pnt2);
    Point& operator= (const Point& pnt);

    // Interface
    float get_x();
    float get_y();
};