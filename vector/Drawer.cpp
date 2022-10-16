#include <Drawer.hpp>

Drawer::Drawer () : 
    m_window{sf::VideoMode(defaultSize, defaultSize), "Drawer window"} // redundant? can use default value
{}

Drawer::Drawer(Point &screenSize) :
    m_window{sf::VideoMode(screenSize.get_x(), screenSize.get_y()), "Drawer window"} // redundant? can use default value
{}

void Drawer::draw (ConcreteVector cvec)
{
    Point start_pnt = cvec.get_start();
    Point end_pnt = cvec.get_end();

    sf::RectangleShape line;

    sf::Vertex line_vertex[] = 
    {
        sf::Vertex(sf::Vector2f(start_pnt.get_x(), start_pnt.get_y())),
        sf::Vertex(sf::Vector2f(end_pnt.get_x(), end_pnt.get_y()))
    };

    m_window.draw(line_vertex, 2, sf::Lines);

    // draw(cvec.get_start());
	draw(cvec.get_end());
}

void Drawer::draw (Point pnt)
{
    sf::CircleShape pnt_graphic(pointRadius); // graphic implementation of point

    pnt_graphic.setFillColor(sf::Color::Green);
    pnt_graphic.setOrigin(pointRadius/2, pointRadius/2);
    pnt_graphic.setPosition(pnt.get_x(), pnt.get_y());

    m_window.draw(pnt_graphic);
}

void Drawer::draw (Canvas cnvs)
{
    edge_type edges = cnvs.get_edges();

    // draw({edges.left_up, edges.right_up}); // It ot okey to ignore type which i cast to?
    draw(ConcreteVector{edges.left_up, edges.right_up});
    draw(ConcreteVector{edges.right_up, edges.right_down});
    draw(ConcreteVector{edges.right_down, edges.left_down});
    draw(ConcreteVector{edges.left_down, edges.left_up});
}

void Drawer::draw(const Rectangle& rect)
{
    edge_type edges = rect.get_edges();
    float width  = fabs(edges.left_up.get_x() - edges.right_down.get_x());
    float height = fabs(edges.left_up.get_y() - edges.right_down.get_y());

    sf::RectangleShape rect_graphic(sf::Vector2f(width, height));
    rect_graphic.setFillColor(sf::Color((unsigned) rect.get_color()));
    rect_graphic.setPosition(edges.left_up.get_x(), edges.left_up.get_y());
    m_window.draw(rect_graphic);
}

bool Drawer::is_opened ()
{
    return m_window.isOpen();
}

void Drawer::poll_event (Event& event)
{
    m_window.pollEvent(event);
}

void Drawer::close ()
{
    m_window.close();
}

void Drawer::display()
{
    m_window.display();
}

void Drawer::clear()
{
    m_window.clear();
}

sf::RenderWindow& Drawer::get_window()
{
    return m_window;
}