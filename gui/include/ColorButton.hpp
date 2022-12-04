#pragma once

#include <LaButton.hpp>
#include <Molbert.hpp>

class ManualColorButtonManager : public LaButtonManagerMutex
{
    Molbert& _mlbrt;
    pixel_color active_color = Colors::GREEN; // TODO Hexspeak for default colors

public:

    ManualColorButtonManager(Molbert& mlbrt) : _mlbrt{mlbrt} {}

    void set_color(pixel_color color) { _mlbrt.set_color(color); }
};

class ColorButton : public LaButton
{

public:

    ColorButton(Point center, Point size, pixel_color clr) :
        LaButton{center, size, clr}
    {}

    bool proc_click(const Point& pnt) 
    {
        ManualColorButtonManager* mngr = static_cast<ManualColorButtonManager*>(getParent());

        std::cout << "Set color: " << get_color() << std::endl;

        if (mngr) mngr->set_color(get_color());
        else std::cout << "[ERROR] Forget to bind color button to manager" << std::endl;
    };

};

class ColorButtonManager : public ManualColorButtonManager
{
    Point _start, _size, begunok;

public:

    ColorButtonManager(Molbert& mlbrt, Point start, Point size) :
        ManualColorButtonManager{mlbrt},
        _start{start},
        _size{size},
        begunok{start}
    {}

    void add_color_button(pixel_color color)
    {
        // TODO shared_ptr?
        ColorButton* clr_btn = new ColorButton{begunok, _size, color};
        begunok = begunok + Point{_size.x(), 0.0};
        
        addChild(clr_btn);
    }

    ~ColorButtonManager()
    {
        for (auto it = m_children.begin(); it != m_children.end(); it++)
            delete *it;
    }
};