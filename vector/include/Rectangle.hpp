#pragma once

#include <Point.hpp>
#include <VectorService.hpp>

class Rectangle
{
    edge_type m_edges{};
    Colors m_color{Colors::RED};
    float _width, _height;
    
public:

    // [Ctors]
    Rectangle(const Point& left_up, const Point& right_down, Colors color = Colors::RED);
    Rectangle(const Point& rect_center, float width, float height, Colors color = Colors::RED);

    // [Setters]
    edge_type set_edges(const Point& rect_center, float width, float height);
    edge_type set_edges(const Point& left_up, const Point& right_down);
    void set_color(Colors color);
    
    // [Getters]
    edge_type get_edges() const;
    Colors get_color() const;
    pixel_color clr() const { return pixel_color(m_color); };
    float width() const {return _width;}
    float height() const {return _height;}
    int iwidth() const { return static_cast<int>(std::floor(_width)); }
    int iheight() const { return static_cast<int>(std::floor(_height)); }
    Point left_up() const { return m_edges.left_up; }
    Point right_down() const { return m_edges.right_down; }


    bool is_in_area(const Point& pnt) const;
};