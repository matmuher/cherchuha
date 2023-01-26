#pragma once

#include <LaButton.hpp>
#include <Texture.hpp>
#include <SFML/Graphics.hpp>

class DecoButton : public Button
{
    Button& _btn;

public:

    DecoButton(Button& btn) : _btn{btn} {};

    virtual void set_center(Point new_center) { _btn.set_center(new_center); }

    virtual pixel_color get_color() { return _btn.get_color(); }

    virtual void press() { _btn.press(); }

    virtual void unpress() { _btn.unpress(); }

    virtual bool is_in_area(const Point& pnt) { return _btn.is_in_area(pnt); }

    virtual void proc_click(const Point& pnt) { _btn.proc_click(pnt); }

    virtual void draw(Drawer& drwr, Canvas& cnvs) const { _btn.draw(drwr, cnvs); }

    virtual Rectangle get_rect() const { return _btn.get_rect(); }
};

class TexturedButton : public DecoButton
{
    Texture _texture;

public:

    TexturedButton(Button& btn, const std::string& texture_name)
    :
        DecoButton{btn}, 
        _texture{texture_name, Point{get_rect().width(), get_rect().height()}}
    {}

    virtual void draw(Drawer& drwr, Canvas& cnvs) const
    {
        drwr.draw(to_window_coords(cnvs, DecoButton::get_rect()), _texture);
    }
};

class TextButton : public DecoButton
{
    const std::string _text;

public:

    TextButton(Button& btn, const std::string& text) : DecoButton{btn}, _text{text} {};

    virtual void draw(Drawer& drwr, Canvas& cnvs) const
    {
        DecoButton::draw(drwr, cnvs);
        drwr.draw(to_window_coords(cnvs, DecoButton::get_rect()), _text);
    }
};