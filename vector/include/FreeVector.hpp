#pragma once

#include <Point.hpp>
#include <cmath>

/*
Usability:

FreeVector vec1{1, 1}, vec2{1, -1};

// "(1,1)"
std::cout << vec1 << std::endl;

FreeVector vec3{vec1 + vec2}; // cpy ctor
vec3 = vec3 + vec3; // assignment
expected: "(4,0) 0 2"
std::cout << vec3 << ' ' << vec1 * vec2 << vec1 * vec1;

flaot k = 4;
// expected: "(4, 4)"
std::cout << vec4{k * vec1} << std::endl;

Point pnt{5,5};
ConcreteVector cvec1{pnt, vec4};

Point cnvs_center{100, 100}; // these coords are tied to the screen
Canvas cnvs{cnvs_center};

draw(cnvs, cvek1); // we can implement striaght interaction with window object only here
*/

class ParsedColor;

class FreeVector
{
    Point m_end {};
    float m_len {};

public:

    FreeVector ();
    FreeVector (Point end); // by end point
    FreeVector (float x, float y); // by end point coords
    FreeVector (const FreeVector &vec); // cpy ctor
    FreeVector (float x, float y, float z); // by end point coords
    FreeVector (const ParsedColor& color);

    // Overload
    friend std::ostream& operator<< (std::ostream &cout, FreeVector vec); // output: check shitty_error.txt

    friend float operator* (FreeVector vec1, FreeVector vec2); // scalar mlt
    friend FreeVector operator* (float k, FreeVector vec); 
    friend FreeVector operator* (FreeVector vec, float k); 
    friend FreeVector operator+ (FreeVector vec1, FreeVector vec2); // sum
    friend FreeVector operator- (FreeVector vec1, FreeVector vec2);
    FreeVector& operator+= (const FreeVector& other);
    FreeVector& operator*= (float k);

    FreeVector& operator-()
        {
            *this = *this * (-1);
            return *this;
        }

    // Functionality
    FreeVector& norm();
    void set_end(const Point& end);
    float get_len ();
    Point get_pos ();
    ParsedColor to_color() const;
    float x() const {return m_end.get_x();}
    float y() const {return m_end.get_y();}
    float z() const {return m_end.get_z();}
};

FreeVector reflect_surface (FreeVector surface_norm, FreeVector ray);
float get_len (FreeVector vec);
