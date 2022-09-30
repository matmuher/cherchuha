#include <Drawer.hpp>

Drawer::Drawer () : 
    m_window{sf::VideoMode(defaultSize, defaultSize), "Drawer window"} // redundant? can use default value
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
    sf::CircleShape pnt_graphic(pointRadius);

    pnt_graphic.setFillColor(sf::Color::Green);
    pnt_graphic.setOrigin(pointRadius/2, pointRadius/2);
    pnt_graphic.setPosition(pnt.get_x(), pnt.get_y());

    m_window.draw(pnt_graphic);
}

bool Drawer::is_opened()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
            return false;
        }
    }
    return true;
}

void Drawer::display()
{
    m_window.display();
}

void Drawer::clear()
{
    m_window.clear();
}

// void Vector::correct_rotation(sf::Vector2f start_point, sf::Vector2f end_point)
// {
// 	sf::Vector2f diff = end_point - start_point; // normalize to use switch? can i switch on structs?

// 	float angle = atan(diff.x / diff.y);

// 	if (diff.x > 0 && diff.y > 0)
// 	{
// 		angle *= -1;
// 	}
// 	else if (diff.x < 0 && diff.y > 0)
// 	{
// 		angle *= -1;
// 	}
// 	else if (diff.x < 0 && diff.y < 0)
// 	{
// 		angle *= -1;
// 		angle += M_PI;
// 	}
// 	else if (diff.x > 0 && diff.y < 0)
// 	{
// 		angle *= -1;
// 		angle += M_PI;
// 	}

// 	angle = angle / M_PI * 180.f; // to degress
// 	m_line_body.setRotation(angle);
// }