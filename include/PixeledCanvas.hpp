#pragma once

#include <Canvas.hpp>
#include <VectorService.hpp>

/*

Ordinary Canvas allows to make transformation of different
shapes from user coord system to window coord system.

What should PixeledCanvas do?
How will I use it?

I wanna make dots on it. Possible usage:

    Point pnt{0.5, 0.5};
    pxld_cnvs.draw(pnt);


*/

class PixeledCanvas
{

    int m_DotSize; // in pixels

    Canvas m_cnvs;

    ParsedColor* m_pixels;
    size_t m_resolution;

public:

    PixeledCanvas(const Canvas& cnvs, int DotSize = 20);
    ~PixeledCanvas();

    // [Getters]
    Point get_center() const;
    float get_width() const;
    float get_height() const;
    const ParsedColor* get_array() const;

    void make_dot(const Point& dot, Colors color);
};