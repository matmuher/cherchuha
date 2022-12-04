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
    GRAY  = 0x7D7D7DFF
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
        r{r_arg}, g{g_arg}, b{b_arg}, a{a_arg} {};

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
};

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