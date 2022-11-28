#pragma once

#include <Point.hpp>
#include <Drawer.hpp>

class Widget
{

private:

    Widget* m_parent = nullptr; // convinient for events handling [chain of responsibility?]

public:

    virtual bool is_in_area(const Point& pnt) const = 0;
    virtual void draw(Drawer& drwr, Canvas& cnvs) const = 0;

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
