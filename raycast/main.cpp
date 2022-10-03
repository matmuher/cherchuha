#include <Chertila.hpp>
#include <cmath>

bool is_close(int a, int b)
{
    const float EPS = 100;
    if (fabs(b - a) < EPS)
        return true;
    return false;
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

    sf::Uint8* pixels = new sf::Uint8[canvas_height * canvas_width * 4];

    int x = 0, y = 0;

    for (int pixel_id = 0; pixel_id < canvas_height * canvas_width * 4; pixel_id += 4)
    {
        x = (pixel_id / 4) % canvas_width;
        y = (pixel_id / 4) / canvas_height;
        //std::cout << x << ' ' << y << std::endl;

        if (is_close(x*x + y*y, 100 * 100))
        {
            pixels[pixel_id]        = 255; // r
            pixels[pixel_id + 1]    = 0;   // g
            pixels[pixel_id + 2]    = 0;   // b
            pixels[pixel_id + 3]    = 255; // a
        }
        else
        {
            pixels[pixel_id]        = 0; // r
            pixels[pixel_id + 1]    = 0;   // g
            pixels[pixel_id + 2]    = 0;   // b
            pixels[pixel_id + 3]    = 0; // a   
        }

    }

    texture.update(pixels);
    sf::Sprite sprite(texture);

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
