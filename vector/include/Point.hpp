#pragma once

#include <iostream>

class FreeVector;
class Point // I have hesitations about class naming, cause all operations belong to radius Vector class
{
    float m_x {}, m_y {}, m_z{};

public:

    // Ctors
    Point (float x, float y);
    Point (float x, float y, float z);
    Point ();
    Point (const Point& pnt);
    Point (FreeVector vec);

    // Dtor
    ~Point ();

    // Overload
    friend std::ostream& operator<< (std::ostream &cout, const Point& pnt);
    friend Point operator- (const Point& pnt1, const Point& pnt2);  // more logical minus operation can be performed
                                                                    // with freevector traslation
    friend Point operator+ (const Point& pnt1,const Point& pnt2);                                                                
    Point& operator= (const Point& pnt);
    Point& operator+= (const Point& other);
    Point& operator*= (float k);

    // Interface: both variants are left for reverse compatibility
    float get_x() const;
    float get_y() const;
    float get_z() const;

    static Point horizontal_shift(float x) { return Point{x, 0}; }
    static Point vertical_shift(float y) { return Point{0, y}; }

    float x() const;
    float y() const;
    float z() const;
};