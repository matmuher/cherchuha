#pragma once

#include <Point.hpp>

enum class Colors : unsigned
{
    RED   = 0xFF0000FF,
    GREEN = 0x00FF00FF,
    BLUE  = 0x0000FFFF,
    WHITE = 0xFFFFFFFF,
    BLACK = 0x000000FF
};


// Implements transforamtion from user's coord system to window's

struct edge_type // How to incapsulate it in class?
    {
    Point   left_up, 
            left_down, 
            right_up, 
            right_down;
    }; 