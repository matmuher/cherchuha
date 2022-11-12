#include <Chertila.hpp>
#include <cmath>

/*
Roadmap:
- Light like flashlight
- DIffused light

*/

class Sphere
{
public:
    // why use getters if i can make variables const?
    Point m_center;
    const float m_R;

    Sphere(const Point& center, float R) : m_center{center}, m_R{R} {};
    FreeVector get_norm(const Point& pnt); // no belong check
};

FreeVector Sphere::get_norm(const Point& pnt)
{
    FreeVector vec{pnt - m_center};
    vec.norm();

    return vec;
}

ParsedColor whitescale (float coef) // 1 - totally white, 0 - totally black
{
    char grayscale = 255.0 * (coef);
    return ParsedColor{grayscale, grayscale, grayscale, (char) 0xFF};
}

int main()
{    
    // Set coord system
    Point real_size{2,2};

    float screen_width = 1280;
    float screen_height = 720;

    float canvas_width = 500;
    float canvas_height = 500;

    Point pixel_resolution{canvas_width, canvas_height};
    Point window_resolution{screen_width, screen_height};

    Point cnvs_center{screen_width / 2, screen_height / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};
    PixeledCanvas pxl_cnvs{cnvs, 1};
    // pxl_cnvs.make_dot({-0.5, -0.5}, Colors::RED);
    Point prop_coefs = cnvs.get_prop_coefs();

    float dx = 1 / prop_coefs.get_x();
    float dy = 1 / prop_coefs.get_y();

    FreeVector light{{0, 1, -1}};
    light.norm();
    Sphere sphr{{0, 0}, 0.5}; // as our light is like light wall 

    // it doesnt make any sense to choose specific z-coord
    // float z_shift = 1; // really in this case there is no sense in z-shit
    // we dont feel it when look upwards
    float t = 0;
    float dt = 0.01;

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



    light.set_end({sin(t), -0.4, cos(t)});
    light.norm();
    t += dt;
    for (float y =  -real_size.get_y() / 2; y <  real_size.get_y() / 2; y += 3*dy)
        for (float x =  -real_size.get_x() / 2; x <  real_size.get_x() / 2; x += 3*dx)
            {

                ParsedColor pixel_color = Colors::GREEN;

                // we concider that sphere is placed above XY plane in direction of positive Z
                float z = sphr.m_R*sphr.m_R - x*x - y*y; // without shift
                float z_closest = sphr.m_R * sphr.m_R;
                float closeness_coef = z / z_closest;
                
                if (z > 0) // --> <---; kiss)
                {
                    z = sqrt(z);
                    Point pnt{x, y, z};
                    FreeVector vec_norm = sphr.get_norm(pnt);
                    float illumination = vec_norm * light;
                    // std::cout << vec_norm << std::endl;
                    // std::cout << light << std::endl;
                    // std::cout << illumination << std::endl;
                    if (illumination <= 0)
                    {
                        //std::cout << illumination << std::endl;
                        pixel_color = whitescale(-illumination);
                    }
                    else
                    {
                        pixel_color = whitescale(0);
                    }
                }
                else
                {
                    pixel_color = Colors::BLACK;
                }

                pxl_cnvs.make_dot({x, y}, pixel_color);
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
