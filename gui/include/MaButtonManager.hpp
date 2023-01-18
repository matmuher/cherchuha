#pragma once

#include <MaButton.hpp>

class MutexMaButtonManager : public WidgetManager
{
    bool catch_click(const Point& pnt) override
    {
        bool is_clicked = false;
        std::_List_iterator<Widget*> clicked_it;

        for (auto it = m_children.begin(); it != m_children.end(); it++)
        {
            if ((*it)->catch_click(pnt))
            {
                is_clicked = true;
                clicked_it = it;
                dynamic_cast<MaButtonView*>(*it)->proc_click();  
            }
        }

        if (is_clicked)
        {
            for (auto it = m_children.begin(); it != m_children.end(); it++)
            {
                dynamic_cast<MaButtonView*>(*it)->unpress();  
            }

            dynamic_cast<MaButtonView*>(*clicked_it)->proc_click(); 
        }

        return is_clicked;
    }
};