#include <Drawer.hpp>

Drawer::Drawer () : 
    m_window{sf::VideoMode(defaultSize, defaultSize), "Drawer window"} // redundant? can use default value
{
    if (!font.loadFromFile(std_font_path))
    {
        std::cout << "Font error\n";
    }

    m_window.setKeyRepeatEnabled(false);
}

Drawer::Drawer(Point &screenSize) :
    m_window{sf::VideoMode(screenSize.get_x(), screenSize.get_y()), "Drawer window"} // redundant? can use default value
{
    if (!font.loadFromFile(std_font_path))
    {
        std::cout << "Font error\n";
    }

    m_window.setKeyRepeatEnabled(false);
}

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
    rect_graphic.setPosition(edges.right_down.get_x(), edges.right_down.get_y());
    m_window.draw(rect_graphic);
}

void Drawer::draw(const Canvas& gui_cnvs, const PixeledCanvas& pxl_canvas)
{
    sf::Texture pxl_canvas_texture;
    pxl_canvas_texture.create(pxl_canvas.get_width(), pxl_canvas.get_height());
    pxl_canvas_texture.update((const sf::Uint8*) pxl_canvas.get_array());
    sf::Sprite pintura_sprite{pxl_canvas_texture};
    
    // Sprite init
    pintura_sprite.setOrigin(pxl_canvas.get_width() / 2, pxl_canvas.get_height() / 2);

    Point pintura_center = to_window_coords(gui_cnvs, pxl_canvas.get_center());
    pintura_sprite.setPosition(pintura_center.get_x(), pintura_center.get_y());

    m_window.draw(pintura_sprite);

    // sf::Font font;
    // if (!font.loadFromFile("fonts/default.ttf"))
    // {
    //     std::cout << "Font error\n";
    // }

    // sf::Text text;
    // text.setString("Meow");
    // text.setFont(font);
    // text.setCharacterSize(25);
    // m_window.draw(text);
}

void Drawer::draw(const Rectangle& rect, const Texture& rect_texture)
{
    edge_type edges = rect.get_edges();
    float width  = fabs(edges.left_up.get_x() - edges.right_down.get_x());
    float height = fabs(edges.left_up.get_y() - edges.right_down.get_y());

    sf::RectangleShape rect_graphic(sf::Vector2f(width, height));
    rect_graphic.setFillColor(sf::Color((unsigned) rect.get_color()));
    rect_graphic.setPosition(edges.right_down.get_x(), edges.right_down.get_y());
    rect_graphic.setTexture(&rect_texture.get());
    m_window.draw(rect_graphic);
}

void Drawer::draw(const Rectangle& rect, const std::string& str)
{
    int len = str.length();

    int char_size = std::min<int>(rect.width() / len, rect.height());
    std::cout << "h: " << rect.iheight() << " w: " << rect.iwidth() << '\n';

    sf::Text sf_text;
    sf_text.setString(str);
    sf_text.setFont(font);
    sf_text.setCharacterSize(char_size);

    sf::FloatRect global_bounds = sf_text.getLocalBounds();
    sf_text.setOrigin(global_bounds.width / 2, char_size / 2.0);

    sf_text.setPosition(rect.center().x(), rect.center().y());
    m_window.draw(sf_text);
    draw(rect.center());
    std::cout << "Char size is " << char_size  << '\n';
}

bool Drawer::is_opened ()
{
    return m_window.isOpen();
}

bool Drawer::poll_event (Event& event)
{
    return m_window.pollEvent(event);
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

Point Drawer::get_mouse_pos()
{
    sf::Vector2i sfml_mouse_pos = sf::Mouse::getPosition(m_window);
    return Point(sfml_mouse_pos.x, sfml_mouse_pos.y);
}

std::queue<EventGUI> Drawer::EventsQueue;

void Drawer::push_gui_event(const EventGUI& event)
{
    EventsQueue.push(event);
}

bool Drawer::poll_gui_event(EventGUI& event)
{
    if (!EventsQueue.empty())
    {
        event = EventsQueue.front();
        EventsQueue.pop();
        return true;
    }
    
    return false;
}
