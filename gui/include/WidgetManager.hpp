#pragma once

#include <Widget.hpp>
#include <list> // may be replaced with my implemantation of
                // some std container

class WidgetManager : public Widget
{

protected:

    std::list<Widget*> m_children;

public:

    void addChild(Widget* child)
    {
        m_children.push_back(child);
        child->setParent(this);
    }

    void removeChild(Widget* child)
    {
        m_children.remove(child);
        child->setParent(nullptr); // why not NULL?
    }

    bool is_in_area(const Point& pnt) const override
    {
        for (auto it = m_children.begin(); it != m_children.end(); it++)
        {
            if ((*it)->is_in_area(pnt)) return true;    
        }

        return false;
    }

    void draw(Drawer& drwr, Canvas& cnvs) const override
    {
        for (auto it = m_children.begin(); it != m_children.end(); it++)
        {
            (*it)->draw(drwr, cnvs);    
        }
    }

};