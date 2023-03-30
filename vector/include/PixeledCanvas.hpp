#pragma once

#include <Canvas.hpp>
#include <VectorService.hpp>
#include <ImageProcess.hpp>

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

    Point m_real_size{};
    Point m_pixel_size{};

    ParsedColor* m_pixels;
    size_t m_resolution;

public:

    PixeledCanvas(const Canvas& cnvs, int DotSize = 1);
    ~PixeledCanvas();

    // [Getters]
    Point get_center() const;
    float get_width() const;
    float get_height() const;
    int iwidth() const { return static_cast<int>(m_pixel_size.x()); }
    int iheight() const { return static_cast<int>(m_pixel_size.y()); }
    const ParsedColor* get_array() const;
    Canvas get_canvas();

    Point get_real_size(); // const
    Point get_pixel_size(); // const

    int get_pixel_id(Point dot); // const
    Cell get_cell(Point dot);

    ParsedColor* operator[] (int k)
        { return m_pixels + k * static_cast<int>(m_pixel_size.x()); }

    // [Setters]
    PixeledCanvas& set_dot_size(int dot_size)
    {
        m_DotSize = dot_size;
        return *this;
    }

    // [Functions]
    void make_dot(const Point& dot, ParsedColor color);
    void load_from_file(const std::string& filename);
};