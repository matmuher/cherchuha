#pragma once

#include <Widget.hpp>
#include <PixeledCanvas.hpp>

class Molbert : public Widget
{
    PixeledCanvas pxld_cnvs;
    pixel_color active_color;

public:

    // [Getters]
    Point get_center() const { return pxld_cnvs.get_center(); }
    float get_width()  const { return pxld_cnvs.get_width(); }
    float get_height() const { return pxld_cnvs.get_height(); }

    const ParsedColor* get_array() const;

    Point get_size() { return pxld_cnvs.get_pixel_size(); }

    Molbert(Point center, Point size, int dot_size) :
        pxld_cnvs{Canvas(center, size, size), dot_size},
        active_color{Colors::GREEN}
    {}

    virtual bool is_in_area(const Point& pnt) 
    {
        Rectangle tmp_rect{get_center(), get_width(), get_height()};
        return tmp_rect.is_in_area(pnt);
    }

    virtual bool proc_click(const Point& pnt)
    {
        pxld_cnvs.make_dot(pnt, active_color);
    }

    virtual void draw(Drawer& drwr, Canvas& cnvs) const
    {
        drwr.draw(cnvs, pxld_cnvs);
    }
};