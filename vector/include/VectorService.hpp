#pragma once

#include <Point.hpp>
#include <FreeVector.hpp>

// in RGBA

typedef unsigned pixel_color;

enum Colors
{
    RED   = 0xFF0000FF,
    GREEN = 0x00FF00FF,
    BLUE  = 0x0000FFFF,
    WHITE = 0xFFFFFFFF,
    BLACK = 0x000000FF,
    GRAY  = 0x7D7D7DFF,
    CYAN  = 0x00FFFFFF,
    YELLOW = 0xFFFF00FF,
    LAVENDER = 0xE6E6FAFF
};

struct Material
{
    Colors diffuse_color{};

    Material(Colors color) : diffuse_color{color} {};
    Material() : diffuse_color{Colors::BLUE} {};
};

typedef unsigned char color_component;
class ParsedColor
{
public:
    color_component r, g, b, a;

    operator pixel_color()
    {
        unsigned int bit_shift = sizeof(color_component) * 8;
        return  a + 
                (b << bit_shift) +
                (g << (bit_shift * 2)) +
                (r << (bit_shift * 3));
    }

    ParsedColor operator= (const ParsedColor& clr)
    {
        r = clr.r;
        g = clr.g;
        b = clr.b;
        a = clr.a;

        return clr;
    }

    ParsedColor& operator+= (const ParsedColor& other)
    {
        r += other.r;
        g += other.g;
        b += other.b;

        return *this;
    }

    ParsedColor& operator*= (const float k)
    {
        r *= k;
        g *= k;
        b *= k;

        return *this;
    }

    bool operator== (const ParsedColor& clr)
    {
        return
            r == clr.r &&
            g == clr.g &&
            b == clr.b &&
            a == clr.a;
    }

    bool operator!= (const ParsedColor& clr)
    {
        return !(*this == clr);
    }

    ParsedColor(pixel_color color)
    {

        color_component* color_ptr = (color_component*) &color;
        a = color_ptr[0];
        b = color_ptr[1];
        g = color_ptr[2];
        r = color_ptr[3];

    }

    ParsedColor(Colors color)
    {
        color_component* color_ptr = (color_component*) &color;
        a = color_ptr[0];
        b = color_ptr[1];
        g = color_ptr[2];
        r = color_ptr[3];
    }

    ParsedColor (char r_arg, char g_arg, char b_arg, char a_arg) :
        r{static_cast<color_component>(r_arg)},
        g{static_cast<color_component>(g_arg)},
        b{static_cast<color_component>(b_arg)},
        a{static_cast<color_component>(a_arg)}
    {};

    // It is important for right Molbert Init Color!
    ParsedColor () : ParsedColor(Colors::WHITE) {};

    ParsedColor (Material m) : ParsedColor{m.diffuse_color} {};

    ParsedColor (FreeVector vec);

    ParsedColor& set_intensity(float coef) 
    {
        a = 255 * coef;
        return *this;
    }

    ParsedColor& invert_color()
    {
        r = 255 - r;
        g = 255 - g;
        b = 255 - b;

        return *this;
    }

    ParsedColor vice_versa()
    {
        return ParsedColor{a, b, g, r};
    }
};


ParsedColor operator* (const ParsedColor& other, float k);

std::ostream& operator<< (std::ostream& cout, ParsedColor clr);

// Implements transforamtion from user's coord system to window's

struct edge_type
    {
    Point   left_up, 
            left_down, 
            right_up, 
            right_down;
    };

double clamp(double val);

ParsedColor whitescale (float coef);