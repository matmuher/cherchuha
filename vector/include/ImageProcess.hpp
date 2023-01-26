#pragma once

struct Cell
{
    int x;
    int y;

    Cell (float fx, float fy) : x{static_cast<int>(fx)}, y{static_cast<int>(fy)} {};
};

extern const Cell shifts[4];
extern const Cell ERROR_CELL;

inline bool operator!= (const Cell lhs, const Cell rhs)
{
    if (lhs.x != rhs.x && lhs.y != rhs.y) return true;

    return false;
}

inline bool operator== (const Cell lhs, const Cell rhs)
{
    if (lhs.x == rhs.x && lhs.y == rhs.y) return true;

    return false;
}