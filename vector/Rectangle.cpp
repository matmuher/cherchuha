#include <Rectangle.hpp>

Rectangle::Rectangle(const Point& left_up, const Point& right_down, Colors color) :
    m_edges{set_edges(left_up, right_down)},
    m_color{color}
{}

edge_type Rectangle::set_edges(const Point& left_up, const Point& right_down)
{
    edge_type edges{};

    edges.left_up = left_up;
    edges.right_down = right_down;
    edges.left_down = Point(left_up.get_x(), right_down.get_y());
    edges.right_up = Point(right_down.get_x(), left_up.get_y());

    return edges;
}

edge_type Rectangle::get_edges() const
{
    return m_edges;
}

Colors Rectangle::get_color() const
{
    return m_color;
}