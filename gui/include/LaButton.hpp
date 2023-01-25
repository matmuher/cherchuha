#pragma once

/*
Ok, patterns are nice, but overwhelming
*/

#include <WidgetManager.hpp>
#include <Rectangle.hpp>
#include <list>

enum ButtonMask
{
    PRESS    = 0xFFFFFF55,
    UN_PRESS = 0x000000FF,
};

enum BarMode
{
    H, // Horizontal
    V  // Vertical
};

class LaButton : public Widget
{
    bool is_pressed = false;
    pixel_color _clr;

protected:

    Rectangle _rect;

public:

    LaButton(Point center, Point size, pixel_color clr) :
        _rect{center, size.x(), size.y(), static_cast<Colors>(clr)},
        _clr{clr}
    {}

    LaButton(Point size, pixel_color clr) :
        LaButton{Point{0, 0}, size, clr}
    {}

    void set_center(Point new_center) 
    {
        _rect.set_edges(new_center, _rect.width(), _rect.height());
    }

    pixel_color get_color() {return _clr;}

    void press() 
    {
        // upd model
        is_pressed = true;
        _rect.set_color(static_cast<Colors>(_clr & ButtonMask::PRESS));
    }

    void unpress() 
    {
        is_pressed = false;
        _rect.set_color(static_cast<Colors>(_clr | ButtonMask::UN_PRESS));
    }

    bool is_in_area(const Point& pnt) override
    {
        return _rect.is_in_area(pnt);
    }

    virtual bool proc_click(const Point& pnt) override
    {
        // is_pressed ? unpress() : press(); HOWTOFIX
        press();
    }

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

        // Provide mutex: unpress others
        if (clicked_btn != m_children.end())
            for (auto it = m_children.begin(); it != m_children.end(); it++)
            {
                if (it != clicked_btn)
                {
                    dynamic_cast<LaButton*>(*it)->unpress();
                }
                else
                {
                    dynamic_cast<LaButton*>(*it)->press();
                }
            }

        return clicked_btn != m_children.end() ? true : false;
    }
};

class LaButtonBar : public LaButtonManagerMutex
{
    Point _start, _size, begunok;
    BarMode _mode;
    int _shift;

public:

    LaButtonBar(Point start, Point size, BarMode mode = BarMode::H, int shift = 0) :
        _start{start},
        _size{size},
        begunok{start},
        _mode{mode},
        _shift{shift}
    {}
    // TODO set button size = bar icon size
    void add_button(LaButton* btn)
    {
        std::cout << "begunok is " << begunok << std::endl;
        if (_mode == BarMode::V)
            
            begunok = begunok - Point{0.0, _size.y() + _shift};
        
        else if (_mode == BarMode::H) 
        
            begunok = begunok + Point{_size.x() + _shift, 0.0};

        btn->set_center(begunok);
        
        addChild(btn);
    }

    ~LaButtonBar()
    {
        for (auto it = m_children.begin(); it != m_children.end(); it++)
            delete *it;
    }
};
