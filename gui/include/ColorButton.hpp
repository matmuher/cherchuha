#pragma once

#include <LaButton.hpp>
#include <Molbert.hpp>

class ColorButtonManager : public LaButtonManagerMutex
{
    Molbert& _mlbrt;
    pixel_color active_color = Colors::GREEN; // TODO Hexspeak for default colors

public:

    ColorButtonManager(Molbert& mlbrt) : _mlbrt{mlbrt} {}

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
        ColorButtonManager* mngr = static_cast<ColorButtonManager*>(getParent());

        std::cout << "Set color: " << get_color() << std::endl;

        if (mngr) mngr->set_color(get_color());
        else std::cout << "[ERROR] Forget to bind color button to manager" << std::endl;
    };

};
