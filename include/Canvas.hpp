#pragma once

#include <Point.hpp>

// Implements transforamtion from user's coord system to window's

struct edge_type // How to incapsulate it in class?
    {
    Point   left_up, 
            left_down, 
            right_up, 
            right_down;
    }; 

class Canvas
{
    Point m_center {}; // In windows coords
    Point m_prop_coefs{1, 1}; // Proportion coefs for x&y axes

    edge_type m_edges;
    
    edge_type set_edges(Point &center, Point &pixel_size);

public:

    Canvas(Point &center);
    Canvas(Point center, Point real_size, Point pixel_size);
    Canvas();
    Point get_center();
    Point get_prop_coefs();
    edge_type get_edges();
};

Point to_window_coords(Canvas cnvs, Point pnt);
ConcreteVector to_window_coords(Canvas cnvs, ConcreteVector cvec);
Point to_canvas_coords(Canvas cnvs, Point pnt);