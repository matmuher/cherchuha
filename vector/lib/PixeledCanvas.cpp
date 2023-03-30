#include <PixeledCanvas.hpp>
#include <cmath>
#include <assert.h>
#include <ImageProcess.hpp>

#include <SFML/Graphics.hpp>

PixeledCanvas::PixeledCanvas(const Canvas& cnvs, int DotSize) :

    m_DotSize{DotSize},
    m_cnvs{cnvs},
    m_real_size{cnvs.get_real_size()},
    m_pixel_size{cnvs.get_pixel_size()},
    m_resolution{static_cast<size_t>(m_pixel_size.x() * m_pixel_size.y())}
{
    std::cout << "Ordinary constructor" << std::endl;

    try
    {
        m_pixels = new ParsedColor[m_resolution];
    }
    catch(const std::exception& e)
    {
        std::cerr << "PixeledCanvas array allocation error: " << e.what() << '\n';
        throw;
    }
}

PixeledCanvas::~PixeledCanvas()
{
    delete [] m_pixels;
}

Cell PixeledCanvas::get_cell(Point dot)
{
    edge_type edges = m_cnvs.get_edges();
    m_cnvs.set_center(m_cnvs.get_center() - edges.left_up);
    Point dot_wc = to_window_coords(m_cnvs, dot);
    m_cnvs.set_center(m_cnvs.get_center() + edges.left_up);

    int x = dot_wc.x();
    int y = dot_wc.y();

    if (0 <= x && x < iwidth() &&
        0 <= y && y < iheight())
        return Cell(x, y);
    
    return ERROR_CELL;
}

int PixeledCanvas::get_pixel_id(Point dot)
{
    Cell cell = get_cell(dot);

    if (cell != ERROR_CELL)
    {
        int pixel_id = cell.y * m_cnvs.get_width() + cell.x;
        return pixel_id;
    }
    
    return -1;
}

// for easier coords traslation let's assume
// put "windows center" in left up edge of canvas
// now we can use to_window_coords(...) for this purpose

void PixeledCanvas::make_dot(const Point& dot, ParsedColor color)
    {
        int pixel_id = get_pixel_id(dot);

        // TODO edge cases
        if(pixel_id > -1)
            for (int dot_y_shift = -m_DotSize; dot_y_shift <= m_DotSize; dot_y_shift++)
                for (int dot_x_shift = -m_DotSize; dot_x_shift <= m_DotSize; dot_x_shift++)
                {
                    int pixel_pos = pixel_id + dot_y_shift * m_cnvs.get_width() + dot_x_shift;

                    if (0 <= pixel_pos && pixel_pos < m_resolution)
                        m_pixels[pixel_pos] = color;
                }
    }

void PixeledCanvas::load_from_file(const std::string& filename)
{
        sf::Texture texture;
        bool is_success =
            texture.loadFromFile(filename, sf::IntRect{0, 0, m_pixel_size.x(), m_pixel_size.y()});

        if (!is_success)
        {
            std::cout << "Failed to load: " << filename << '\n'; 
            return;
        }

        // std::cout << m_pixel_size.x() << ' ' << m_pixel_size.y() << '\n';

        sf::Image image = texture.copyToImage();
        // std::cout << image.getSize().x << ' ' << image.getSize().y << '\n';
        
        auto pixels = (const sf::Uint32*) image.getPixelsPtr();

        int height = image.getSize().y;
        int width  = image.getSize().x;

        // std::cout << height << ' ' << width << '\n';

        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
            {
                // std::cout << y << ' ' << x << '\n'; 
                ParsedColor color = ParsedColor(pixels[y * width + x]);
                int index = y * m_pixel_size.x() + x;
                m_pixels[index] = color.vice_versa();

                // if (x == 30 && y == 30)
                // {
                //     std::cout << "Load color: " << color << '\n';
                //     // exit(1);
                // }
            }
}

// [GETTERS]


Point PixeledCanvas::get_center() const
{
    return m_cnvs.get_center();
}

float PixeledCanvas::get_width() const
{
    return m_cnvs.get_width();
}

float PixeledCanvas::get_height() const
{
    return m_cnvs.get_height();
}

const ParsedColor* PixeledCanvas::get_array() const
{
    return m_pixels;
}

Canvas PixeledCanvas::get_canvas()
{
    return m_cnvs;
}

Point PixeledCanvas::get_real_size()
{
    return m_real_size;
}

Point PixeledCanvas::get_pixel_size()
{
    return m_pixel_size;
}