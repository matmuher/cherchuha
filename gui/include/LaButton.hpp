#pragma once

/*
Ok, patterns are nice, but overwhelming
*/

#include <WidgetManager.hpp>
#include <Rectangle.hpp>
#include <list>
#include <chrono>
#include <CoolDowner.hpp>

enum ButtonMask
{
    PRESS    = 0x000000FF,
    UN_PRESS = 0xFFFFFF55,
};

enum BarMode
{
    H, // Horizontal
    V  // Vertical
};

class Button : public Widget
{

public:

    virtual void set_center(Point new_center) = 0;

    virtual pixel_color get_color() = 0;

    virtual Rectangle get_rect() const = 0;

    virtual void press() = 0;

    virtual void unpress() = 0;

    virtual bool is_in_area(const Point& pnt) = 0;

    virtual void proc_click(const Point& pnt) = 0;

    virtual void draw(Drawer& drwr, Canvas& cnvs) const = 0;
};

// ConcreteButton0x000000FF
class LaButton : public Button
{
protected:

    Rectangle _rect;

private:

    CoolDowner cooldowner;

    bool is_pressed = false;
    pixel_color _clr;

public:

    LaButton(Point center, Point size, pixel_color clr) :
        _rect{center, size.x(), size.y(), static_cast<Colors>(clr)},
        _clr{clr}
    {
        unpress();
    }

    LaButton(Point center, float height, size_t symbols_num, pixel_color clr)
    :
        LaButton{center, Point{compute_width_for_text(height, symbols_num), height}, clr}
    {}

    LaButton(Point size, pixel_color clr) :
        LaButton{Point{0, 0}, size, clr}
    {}

    void set_center(Point new_center) 
    {
        _rect.set_edges(new_center, _rect.width(), _rect.height());
    }

    pixel_color get_color() { return _clr; }

    virtual Rectangle get_rect() const { return _rect; }

    float get_width() const { return _rect.width();}
    float get_height() const { return _rect.height();}

    static float compute_width_for_text (float height, size_t symbols_num)
    {
        return height/2 * symbols_num;
    }

    Point right_center() const { return _rect.center() + Point{_rect.width() / 2, 0 }; }
    Point left_center()  const { return _rect.center() - Point{_rect.width() / 2, 0 }; }
    Point up_center()    const { return _rect.center() + Point{0, _rect.height() / 2}; }
    Point down_center()  const { return _rect.center() - Point{0, _rect.height() / 2}; }

    virtual void press() 
    {
        // upd model
        is_pressed = true;
        _rect.set_color(static_cast<Colors>(_clr | ButtonMask::PRESS));
    }

    virtual void unpress() 
    {
        is_pressed = false;
        _rect.set_color(static_cast<Colors>(_clr & ButtonMask::UN_PRESS));
    }

    bool is_in_area(const Point& pnt) override
    {
        return _rect.is_in_area(pnt);
    }

    virtual void proc_click(const Point& pnt) override
    {
        if (cooldowner.is_valid_action())
        {
            is_pressed ? unpress() : press(); // HOWTOFIX
        }
    }

    virtual void draw(Drawer& drwr, Canvas& cnvs) const override
    {
        drwr.draw(to_window_coords(cnvs, _rect));
    }

    bool get_press_status() {return is_pressed;}
};

// TODO optimize
class ButtonManagerMutex : public WidgetManager
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
                    dynamic_cast<Button*>(*it)->unpress();
                }
                else
                {
                    dynamic_cast<Button*>(*it)->press();
                }
            }

        return clicked_btn != m_children.end() ? true : false;
    }
};

class ButtonBar : public ButtonManagerMutex
{
    Point _start, _size, begunok;
    BarMode _mode;
    int _shift;

public:

    ButtonBar(Point start, Point size, BarMode mode = BarMode::H, int shift = 0) :
        _start{start},
        _size{size},
        begunok{start},
        _mode{mode},
        _shift{shift}
    {}
    // TODO set button size = bar icon size
    void add_button(Button* btn)
    {
        std::cout << "begunok is " << begunok << std::endl;
        if (_mode == BarMode::V)
            
            begunok = begunok - Point{0.0, _size.y() + _shift};
        
        else if (_mode == BarMode::H) 
        
            begunok = begunok + Point{_size.x() + _shift, 0.0};

        btn->set_center(begunok);
        
        addChild(btn);
    }

    ~ButtonBar()
    {
        for (auto it = m_children.begin(); it != m_children.end(); it++)
            delete *it;
    }
};
