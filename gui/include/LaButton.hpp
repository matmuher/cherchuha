#pragma once

/*
Ok, patterns are nice, but overwhelming
*/

#include <WidgetManager.hpp>
#include <Rectangle.hpp>
#include <list>

enum BTN_MASK
{
    PRESS    = 0xFFFFFF55,
    UN_PRESS = 0x000000FF,
};

class LaButton : public Widget
{
    bool is_pressed = false;
    Rectangle _rect;
    pixel_color _clr;

public:

    LaButton(Point center, Point size, pixel_color clr) :
        is_pressed{false},
        _rect{center, size.x(), size.y(), static_cast<Colors>(clr)},
        _clr{clr}
    {

    }

    void press() 
    {
        // upd model
        is_pressed = true;
        _clr = _clr & BTN_MASK::PRESS;

        // upd view
        _rect.set_color(static_cast<Colors>(_clr));
    }

    void unpress() 
    {
        is_pressed = false;
        _clr = _clr | BTN_MASK::UN_PRESS;

        _rect.set_color(static_cast<Colors>(_clr));
    }

    bool is_in_area(const Point& pnt) override
    {
        return _rect.is_in_area(pnt);
    }

    // virtual bool proc_click(const Point& pnt) override
    // {
    //     is_pressed ? unpress() : press();
    // }

    virtual void draw(Drawer& drwr, Canvas& cnvs) const override
    {
        drwr.draw(to_window_coords(cnvs, _rect));
    }
};

// TODO optimize
class LaButtonManagerMutex : public WidgetManager
{
public:

    bool catch_click(const Point& pnt)
    {
        bool is_clicked = false;

        for (auto it = m_children.begin(); it != m_children.end(); it++)
        {
            if ((*it)->catch_click(pnt))
            {
                is_clicked = true;
            }
        }

        if (is_clicked)
            for (auto it = m_children.begin(); it != m_children.end(); it++)
            {
                if ((*it)->catch_click(pnt))
                {
                    dynamic_cast<LaButton*>(*it)->press();  
                }
                else
                {
                    dynamic_cast<LaButton*>(*it)->unpress();
                }
            }

        return is_clicked;
    }
};