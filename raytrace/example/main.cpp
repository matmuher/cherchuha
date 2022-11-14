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
    static float t = 0;
    t += 0.1;

    Point view_point{};

    Point real_size  = pxl_cnvs.get_real_size();
    Point pixel_size = pxl_cnvs.get_pixel_size();
    
    float dx = real_size.x() / pixel_size.x();
    float dy = real_size.y() / pixel_size.y();

    FreeVector light{{sin(t), 0.1, cos(t)}};
    light.norm();

    // float t1{}, t2{};
    // sphr.ray_intersect({0, -0.47, -1.33}, t1, t2);
    // std::cout << "Intersections are: " << t1 << " " << t2 << std::endl;
    // std::cout << "norm in bottom point " << sphr.get_norm({0, 0.5, -1.5}) << std::endl;
    // exit(1);

    float skip_factor = 4;
    for (float y = -real_size.y() / 2; y < real_size.y() / 2; y+= skip_factor * dy)
        for (float x = -real_size.x() / 2; x < real_size.x() / 2; x+= skip_factor * dx)
        {   
            float t1{}, t2{};
            FreeVector ray = create_ray(view_point, {x, y, -1});
            ray.norm();

            if (sphr.ray_intersect(ray, t1, t2))
            {
                // std::cout << get_len(ray * t1 - FreeVector(sphr.m_center)) << std::endl;
                FreeVector n = sphr.get_norm(ray * t1);
                float intensity_coef = clamp((-1) * (n * light));
                //std::cout << x << " " << y << " " << n << " " << intensity_coef << std::endl;
                // std::cout << intensity_coef << std::endl;
                ParsedColor pixel_color = sphr.material;
                pxl_cnvs.make_dot({x, y}, pixel_color.set_intensity(intensity_coef));
            }
            else
            {
                pxl_cnvs.make_dot({x, y}, Colors::RED);
            }
        }
}

int main()
{    
    // Set coord system
    Point real_size{1,1};

    float screen_width = 1280;
    float screen_height = 720;

    float canvas_width = 700;
    float canvas_height = 700;

    Point pixel_resolution{canvas_width, canvas_height};
    Point window_resolution{screen_width, screen_height};

    Point cnvs_center{screen_width / 2, screen_height / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};
    PixeledCanvas pxl_cnvs{cnvs, 1};

    Sphere sphr{{0, 0, -1.5}, 0.5, Colors::GREEN};

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
        //exit(1);
    }

    return 0;
}
