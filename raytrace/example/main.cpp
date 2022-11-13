#include <Chertila.hpp>
#include <cmath>
#include <assert.h>

FreeVector create_ray(Point start, Point end)
{
    FreeVector ray{end-start};
    ray.norm();

    return ray;
}

void render(Sphere sphr, PixeledCanvas& pxl_cnvs)
{
    Point view_point{};

    Point real_size  = pxl_cnvs.get_real_size();
    Point pixel_size = pxl_cnvs.get_pixel_size();
    
    float dx = real_size.x() / pixel_size.x();
    float dy = real_size.y() / pixel_size.y();

    for (float y = -real_size.y() / 2; y < real_size.y() / 2; y+=dy)
        for (float x = -real_size.x() / 2; x < real_size.x() / 2; x+=dx)
        {   
            FreeVector ray = create_ray(view_point, {x, y, 1});

            if (sphr.ray_intersect(ray))
                pxl_cnvs.make_dot({x, y}, Colors::BLUE);
        }
}

int main()
{    
    // Set coord system
    Point real_size{1,1};

    float screen_width = 1280;
    float screen_height = 720;

    float canvas_width = 500;
    float canvas_height = 500;

    Point pixel_resolution{canvas_width, canvas_height};
    Point window_resolution{screen_width, screen_height};

    Point cnvs_center{screen_width / 2, screen_height / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};
    PixeledCanvas pxl_cnvs{cnvs, 1};

    Sphere sphr{{0, 0, 2}, 0.5};

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

        render(sphr, pxl_cnvs);

        // Draw
        drwr.clear();
        // drwr.draw(cnvs);
        drwr.draw(pxl_cnvs);
        // drwr.draw(to_window_coords(cnvs, pnt));
        drwr.display();
    }

    return 0;
}
