#pragma once

#include <Point.hpp>
#include <Drawer.hpp>

class Widget
{
private:

    Widget* m_parent = nullptr; // convinient for events handling [chain of responsibility?]

public:

    virtual bool is_in_area(const Point& pnt) {return false;}

    virtual bool proc_click(const Point& pnt) {}; // TODO: need bool here?

    virtual void draw(Drawer& drwr, Canvas& cnvs) const = 0;

    // Will be used by terminal widgets
    // In manager they will be overriden
    virtual bool catch_click(const Point& pnt)
    {
        bool click_is_here = is_in_area(pnt); 

        if (click_is_here)
        {
            proc_click(pnt);
        }
        
        return click_is_here;
    }

    virtual ~Widget() {}; // to not make leaks when polymorphism happens

    void setParent(Widget* parent)
    {
        m_parent = parent;
    }

    Widget* getParent() const
    {
        return m_parent;
    }

};
