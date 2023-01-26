#include <Molbert.hpp>
#include <MolbertTools.hpp>

void Molbert::proc_click(const Point& pnt) 
    {
        // make_dot(pnt, active_color);
        if (active_tool) active_tool->apply(pnt);
    }
