#include <ImageProcess.hpp>

const Cell shifts[4] = 
{
    {0, -1},
    {0,  1},
    {1,  0},
    {-1, 0}
};

const Cell ERROR_CELL{-1, -1};