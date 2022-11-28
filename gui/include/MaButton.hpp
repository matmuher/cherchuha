#pragma once

#include <WidgetManager.hpp>
#include <Rectangle.hpp>
// #include <Request.hpp>
#include <Observer.hpp>

class MaButton : public Observable
{
    bool is_pressed = false;

public:

    void press()
    {   
        std::cout << "Change state\n";
        is_pressed = !is_pressed;
        notify_observers();
    }

    bool get_state() const {return is_pressed;}
};

// class ButtonReq : public Req
// {
//     ButtonReq() : Req{ReqType::BUTTON_PRESS} {};
// };

/*
Seems like I'll need to create Request class. In this step
I need to transfer signal to Controller and to avoid passing
100500 arguments I'll pass Request object.
*/
class MaButtonCntrl
{
    MaButton& _mdl;

public:

    MaButtonCntrl(MaButton& mdl) : _mdl{mdl} {};

    void press()
        {
            _mdl.press();
        }
};


/*
For now I assign duties of handling user interaction on View,
cause I can have several views and they would be placed in different parts of
screen. And have to handle user input differently. So it's most straightforward
way to place user interaction handling module in View.
*/

enum BTN_MASK
{
    PRESS    = 0xFFFFFF55,
    UN_PRESS = 0x000000FF,
};

class MaButtonView : public Widget, public Observer
{
    Rectangle _rect;
    MaButtonCntrl& _ctrl;
    const MaButton& _mdl;
    // bool on = true; // this state can be useful for multiple views situation

public:

    MaButtonView( const MaButton& mdl, MaButtonCntrl& ctrl,
                Point cntr, Point size, Colors clr) :
        _rect{cntr, size.x(), size.y(), clr},
        _ctrl{ctrl},
        _mdl{mdl}
    {
        const_cast<MaButton&>(_mdl).add_observer(this);
    }

// [Declare Widgets' virtual functions]

    // I leave them virtual as this button seems based enough
    // to be inherited from
    virtual void draw(Drawer& drwr, Canvas& cnvs) const
    {
        drwr.draw(to_window_coords(cnvs, _rect));
    }

    // use global is_in_area for reactangels
    virtual bool is_in_area(const Point& pnt) const
    {
        return _rect.is_in_area(pnt);
    }

// [Declare Observers' virtual functions]

    void update()
    {
        std::cout << "Update\n";
        Colors new_color = _rect.get_color();

        if (_mdl.get_state())
        {
            std::cout << "Press\n";
            new_color = static_cast<Colors>(new_color & BTN_MASK::PRESS); 
        }
        else
        {
            std::cout << "UNpress\n";
            new_color = static_cast<Colors>(new_color | BTN_MASK::UN_PRESS); 
        }

        _rect.set_color(new_color);
    }

// [Proc events]

    void proc_click()
        {
            std::cout << "Proc click\n";
            _ctrl.press();
        }
};
