#include <LaPintura.hpp>
#include <cmath>

LaPintura::LaPintura(const Point& pintura_center, float width, float height, 
                     Colors pintura_color, Colors pen_color) :

    m_pen_color{pen_color},
    m_pintura_color{pintura_color},

    m_pintura_resolution{width * height},
    m_width{width},
    m_height{height},
    m_edges{set_edges(pintura_center, width, height)},

    m_pintura_center{pintura_center},

    m_pixels{NULL}
{
    std::cout << "Ordinary constructor" << std::endl;

    try
    {
        m_pixels = new pixel_color[m_pintura_resolution];
    }
    catch(const std::exception& e)
    {
        std::cerr << "Pintura array allcoation error: " << e.what() << '\n';
        throw;
    }

    fill(pintura_color);
}

LaPintura::LaPintura(const LaPintura& pintura) :

    m_pen_color{pintura.m_pen_color},
    m_pintura_color{pintura.m_pintura_color},

    m_pintura_resolution{pintura.m_width * pintura.m_height},
    m_width{pintura.m_width},
    m_height{pintura.m_height},
    m_edges{set_edges(pintura.m_pintura_center, pintura.m_width, pintura.m_height)},

    m_pintura_center{pintura.m_pintura_center},

    m_pixels{NULL}
{
    std::cout << "Copy ctor" << std::endl;
    try
    {
        m_pixels = new pixel_color[m_pintura_resolution];
    }
    catch(const std::exception& e)
    {
        std::cerr << "Pintura array allcoation error: " << e.what() << '\n';
        throw;
    }

    for (size_t pixel_id = 0; pixel_id < m_pintura_resolution; pixel_id++)
    {
        m_pixels[pixel_id] = pintura.m_pixels[pixel_id];
    }

    // fill(pintura.m_pintura_color);
}

LaPintura::~LaPintura()
{
    delete [] m_pixels;
}

void LaPintura::fill(Colors fill_color)
{
    pixel_color* pixels_begunok = m_pixels;
    for (int pixel_id = 0; pixel_id < m_pintura_resolution; pixel_id++)
    {
        put_color(pixels_begunok++, fill_color);
    }
}

void LaPintura::put_color(pixel_color* pixel, Colors color)
    {
        ParsedColor parsed_color{color};
        color_component* pixel_component = (color_component*) pixel;

        pixel_component[0] = parsed_color.r;
        pixel_component[1] = parsed_color.g;
        pixel_component[2] = parsed_color.b;
        pixel_component[3] = parsed_color.a;
    }

size_t LaPintura::get_pixel_id(const Point& pnt)
{
    size_t pixel_x = floor(fabs(m_edges.left_up.get_x() - pnt.get_x()));
    size_t pixel_y = floor(fabs(m_edges.left_up.get_y() - pnt.get_y()));
    std::cout << std::dec << "Click on pintura: " << pixel_x << ' ' << pixel_y << std::endl;

    return (pixel_y - 1) * floor(m_width) + pixel_x;
}

void LaPintura::paint_dot(const Point& pnt)
{
    std::cout << "Paint dot" << std::endl;
    const size_t DotSize = 50;
    size_t pixel_id = get_pixel_id(pnt);
    std::cout << "Got pixel with id: " << pixel_id << std::endl;

    for (size_t i = 0; i < DotSize; i++)
        for (size_t j = 0; j < DotSize; j++)
            {
                put_color(m_pixels + pixel_id + i + j * ((size_t) m_width), m_pen_color);
            }
}

Point LaPintura::get_center() const
{
    return m_pintura_center;
}

float LaPintura::get_width() const
{
    return m_width;
}

float LaPintura::get_height() const
{
    return m_height;
}

const pixel_color* LaPintura::get_array() const
{
    return m_pixels;
}

edge_type LaPintura::get_edges() const
{
    return m_edges;
}

void LaPintura::set_center(const Point& new_center)
{
    m_pintura_center = new_center;
}


edge_type LaPintura::set_edges(const Point& pintura_center,  float width, float height)
{
    edge_type edges{};
    
    edges.left_up    = Point(pintura_center.get_x() - width / 2, pintura_center.get_y() + height / 2);
    edges.left_down  = Point(pintura_center.get_x() - width / 2, pintura_center.get_y() - height / 2);
    edges.right_up   = Point(pintura_center.get_x() + width / 2, pintura_center.get_y() + height / 2);
    edges.right_down = Point(pintura_center.get_x() + width / 2, pintura_center.get_y() - height / 2);

    return edges;
}

void LaPintura::set_pen_color(Colors color)
{
    m_pen_color = color;
}