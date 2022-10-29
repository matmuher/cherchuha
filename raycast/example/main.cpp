#include <Chertila.hpp>
#include <cmath>

/*
Work on painting a sphere:
- Paint an image of speher with color gradation accroding to z component

Create an class of colored canvas with which I will be able to interact
as with array.

Okay now I need to add Z argument to my Vector class to make scalar multiplication 
look beautiful

May be inherit ConcreteVector from FreeVector?
It seem to be easier to add Z-coord
*/

bool is_close(int a, int b)
{
    const float EPS = 100;
    if (fabs(b - a) < EPS)
        return true;
    return false;
}

sf::Color black_white_range(float coef) // coef [0,1]
{
    if (coef > 1 || coef < 0)
    {
        std::cout << "Black-white coefficient [" << coef << "] is out of range\n";
        return sf::Color(255, 0, 0);
    }

    size_t max_white = 255;
    size_t black_white_range = max_white * coef;

    return sf::Color(black_white_range, black_white_range, black_white_range, 255); // opaque
}

float square(float val)
{
    return val*val;
}

void put_color(sf::Uint8* pixel_ptr, sf::Color color)
    {
        pixel_ptr[0] = color.r;
        pixel_ptr[1] = color.g;
        pixel_ptr[2] = color.b;
        pixel_ptr[3] = color.a;
    }

void put_color(sf::Uint32* pixels, sf::Color color)
    {
        sf::Uint8* pixel_ptr = (sf::Uint8*) pixels;

        put_color(pixel_ptr, color);
    }

Point to_canvas_coords(Canvas cnvs, size_t pixel_id) // from associated with this canvas pixel buffer
{
    size_t width = cnvs.get_width();
    // std::cout << width << std::endl;

    float x_id = 0;
    float y_id = 0;

    if (width)
    {
        x_id = pixel_id % width;
        y_id = pixel_id / width; // how much are there completed rows?
    }
    else
    {
        std::cout << "NULL width\n";
    }

    edge_type edges = cnvs.get_edges();
    Point left_up = edges.left_up;

    return to_canvas_coords(cnvs, Point(left_up.get_x() + x_id, left_up.get_y() + y_id));
}

FreeVector get_normal_to_sphere(float sph_radius, Point sph_center, Point sph_pnt)
{
    return FreeVector{sph_pnt.get_x() - sph_center.get_x(), sph_pnt.get_y() - sph_center.get_y()};
}

int main()
{
    // Set coords in user system
    Point pnt{0, 0};
    FreeVector vec{0.5, 0.5};
    ConcreteVector cvec{pnt, vec};
    
    // Set coord system
    Point real_size{2,2};

    float screen_width = 1280;
    float screen_height = 720;

    size_t canvas_width = 500;
    size_t canvas_height = 500;

    Point pixel_resolution{canvas_width, canvas_height};
    Point window_resolution{screen_width, screen_height};

    Point cnvs_center{screen_width / 2, screen_height / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};

    // Lets make a texture
    sf::Texture texture;
    texture.create(canvas_width, canvas_height);

    size_t canvas_resolution = canvas_height * canvas_width;
    sf::Uint8* pixels = new sf::Uint8[canvas_resolution * 4]; // RGBA
    sf::Uint32* pixels_ptr = (sf::Uint32*) pixels;

    int x = 0, y = 0;

    sf::Color g(0, 255, 0, 255);
    sf::Color r(255, 0, 0, 255);

    float sphere_radius = 1;

    for (int pixel_id = 0; pixel_id < canvas_resolution; pixel_id++)
    {
        Point pixel_point = to_canvas_coords(cnvs, pixel_id);
        float x = pixel_point.get_x();
        float y = pixel_point.get_y();
        // std::cout << pixel_point << std::endl;

        float z_square = square(sphere_radius) - square(x) - square(y);

        // std::cout << z_square << std::endl;
        if (z_square < 0)
        {
            put_color(pixels_ptr++, black_white_range(0));
        }
        else 
        {
            // std::cout << "paint it red\n";
            // std::cout << z_square / square(sphere_radius) << std::endl;
            put_color(pixels_ptr++, black_white_range(z_square / square(sphere_radius)));
        }
    }

    texture.update(pixels);
    sf::Sprite sprite(texture);
    
    // Sprite init
    sprite.setOrigin(canvas_width / 2, canvas_height / 2);
    sprite.setPosition(cnvs_center.get_x(), cnvs_center.get_y());

    Drawer drwr{window_resolution};
    sf::RenderWindow& window = drwr.get_window(); 

    while (drwr.is_opened())
    {
        // Events
        Event event;
        drwr.poll_event(event);
        switch (event.type)
        {
            case Event::EventType::Closed:
                drwr.close();
                break;
            default:
                break;
        }

        // Draw
        drwr.clear();
        drwr.draw(cnvs);
        drwr.draw(to_window_coords(cnvs, pnt));

        window.draw(sprite);

        drwr.display();
    }

    delete [] pixels;

    return 0;
}
