#include <Chertila.hpp>
#include <cmath>

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
    PixeledCanvas pxl_cnvs{cnvs, 10};
    pxl_cnvs.make_dot({-0.5, -0.5}, Colors::RED);
    Drawer drwr{window_resolution};

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
        // drwr.draw(cnvs);
        drwr.draw(pxl_cnvs);
        // drwr.draw(to_window_coords(cnvs, pnt));
        drwr.display();
    }

    return 0;
}
