#pragma once

#include <Point.hpp>
#include <VectorService.hpp>

class Rectangle
{
    edge_type m_edges{};
    Colors m_color{Colors::RED};
    
public:

    // [Ctors]
    Rectangle(const Point& left_up, const Point& right_down, Colors color = Colors::RED);
    Rectangle(const Point& rect_center, float width, float height, Colors color = Colors::GREEN);

    // [Setters]
    edge_type set_edges(const Point& rect_center, float width, float height);
    edge_type set_edges(const Point& left_up, const Point& right_down);
    void set_color(Colors color);
    
    // [Getters]
    edge_type get_edges() const;
    Colors get_color() const;
};