#include <Chertila.hpp>
#include <cmath>
#include <assert.h>

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

/*
    Clamp value to [0;1] range
*/
double clamp(double val)
{
    if  (val < 0)
    {
        return 0;
    }
    else if (val <= 1) 
    {
        return val;
    }

    return 1;
}

FreeVector reflect_surface (FreeVector surface_norm, FreeVector ray)
{
    return ray - 2.0 * (ray * surface_norm) * surface_norm;
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
    // pxl_cnvs.make_dot({-0.5, -0.5}, Colors::RED);
    Point prop_coefs = cnvs.get_prop_coefs();

    float dx = 1 / prop_coefs.get_x();
    float dy = 1 / prop_coefs.get_y();

    Sphere sphr{{0, 0}, 0.5}; // as our light is like light wall 

    // it doesnt make any sense to choose specific z-coord
    // float z_shift = 1; // really in this case there is no sense in z-shit
    // we dont feel it when look upwards
    float t = 0;
    float dt = 0.01;

    Drawer drwr{window_resolution};


    FreeVector light{{-1, 0}};
    light.norm();
    double ambient_light = 0.2;
    double material_exp = 17;
    double diffuse_coef = 0.5;
    FreeVector view_point{{0, 0, 1}};

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



    light.set_end({-1, -0.7, -1});
    light.norm();
    t += dt;
    float skip_factor = 3;
    for (float y =  -real_size.get_y() / 2; y <  real_size.get_y() / 2; y += skip_factor*dy)
        for (float x =  -real_size.get_x() / 2; x <  real_size.get_x() / 2; x += skip_factor*dx)
            {

                ParsedColor pixel_color = Colors::GREEN;

                // we concider that sphere is placed above XY plane in direction of positive Z
                float z = sphr.m_R*sphr.m_R - x*x - y*y; // without shift
                float z_closest = sphr.m_R * sphr.m_R;
                float closeness_coef = z / z_closest;
                float intensity = 0;

                if (z > 0) // --> <---; kiss)
                {
                    z = sqrt(z);
                    Point pnt{x, y, z};
                    FreeVector vec{pnt};
                    FreeVector vec_norm = sphr.get_norm(pnt);
                    float illumination = vec_norm * light;
                    FreeVector view_dir = view_point - vec;
                    float specular_light = view_dir.norm() * reflect_surface(vec_norm, light);
                    
                    if (specular_light < 0)
                        specular_light = 0;
                    specular_light = powf(specular_light, material_exp);

                    intensity += clamp(ambient_light);

                    if (illumination <= 0)
                    {
                        //std::cout << illumination << std::endl;
                        intensity += clamp(specular_light);
                        intensity += diffuse_coef * clamp(-illumination);
                        // pixel_color = whitescale(clamp(-illumination + ambient_light + specular_light));
                    }

                    pixel_color = whitescale(clamp(intensity));
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
