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
        _rect{center, size.x(), size.y(), static_cast<Colors>(clr)},
        _clr{clr}
    {}

    pixel_color get_color() {return _clr;}

    void press() 
    {
        // upd model
        is_pressed = true;
        _rect.set_color(static_cast<Colors>(_clr & BTN_MASK::PRESS));
    }

    void unpress() 
    {
        is_pressed = false;
        _rect.set_color(static_cast<Colors>(_clr | BTN_MASK::UN_PRESS));
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
        std::_List_iterator<Widget *> clicked_btn = m_children.end();

        for (auto it = m_children.begin(); it != m_children.end(); it++)
        {
            if ((*it)->catch_click(pnt))
            {
                clicked_btn = it;
                break;
            }
        }

        if (clicked_btn != m_children.end())
            for (auto it = m_children.begin(); it != m_children.end(); it++)
            {
                if (it == clicked_btn)
                {
                    dynamic_cast<LaButton*>(*it)->press();  
                }
                else
                {
                    dynamic_cast<LaButton*>(*it)->unpress();
                }
            }

        return clicked_btn != m_children.end() ? true : false;
    }
};