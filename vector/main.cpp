#include <Chertila.hpp>

/*
Nearest roadmap:

- [OK] Change Canvas class to get pixels and real sizes
    - [OK] Draw Canvas borders
- [OK] Make the second canvas with interactive vector
- Make a cat from arrow side of vector
- README
*/

/*
Usecase for Canvas update:

Point cnvs_center{100, 100};
Point real_size{3,2}; // {x,y}: from -1 to 1, from -1.5 to 1.5
Poinr pixel_size{1280, 720}; // {x,y}: 1280 x 720
Canvas cnvs{cnvs_center, real_size, pixel_size};
*/

int main()
{
    #if 0
        FreeVector vec1{1, 1}, vec2{1, -1};

        // "(1,1)"
        std::cout << vec1 << std::endl;

        FreeVector vec3{vec1 + vec2}; // cpy ctor
        vec3 = vec3 + vec3; // assignment
        // expected: "(4,0) 0 2"
        std::cout << vec3 << ' ' << vec1 * vec2 << ' ' << vec1 * vec1 << std::endl;

        float k = 4;
        // expected: "(4, 4)"
        FreeVector vec4{k * vec1};

        std::cout << vec4 + vec1 << std::endl;
    #endif

    // Set coords in user system
    Point pnt{0, 0};
    FreeVector vec{0.5, 0.5};
    ConcreteVector cvec_click{pnt, vec};
    ConcreteVector cvec_rotate{pnt, vec};
    
    // Set user system
    Point real_size{2,2};

    float screen_width = 1280;
    float prop_coef = 1.f / 11.f;

    Point pixel_resolution{(4 * prop_coef) * screen_width, screen_width * (4 * prop_coef)};
    Point window_resolution{screen_width, 720};

    Point cnvs_rotate_center{(3 * prop_coef) * screen_width, window_resolution.get_y() / 2};
    Canvas cnvs_rotate{cnvs_rotate_center, real_size, pixel_resolution};

    Point cnvs_click_center{(8 * prop_coef) * screen_width, window_resolution.get_y() / 2};
    Canvas cnvs_click{cnvs_click_center, real_size, pixel_resolution};

    Drawer drwr{window_resolution};
    float t = 0;
    float dt = 1E-2;
    const float R = 0.5;

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

            case Event::EventType::MouseButtonPressed:
                {
                    Point click_pnt{(float) event.mouseButton.x, (float) event.mouseButton.y};
                    cvec_click.set_fvec(to_canvas_coords(cnvs_click, click_pnt));
                    break;
                }

            default:
                break;
        }

        // Rotation
        cvec_rotate.set_fvec(FreeVector{R * (float) sin(t), R * (float) cos(t)});
        t += dt;

        // Draw
        drwr.clear();
        // drwr.draw(pnt);
        drwr.draw(cnvs_click);
        drwr.draw(cnvs_rotate);
        drwr.draw(to_window_coords(cnvs_click, cvec_click));
        drwr.draw(to_window_coords(cnvs_rotate, cvec_rotate));
        drwr.display();
    }

    return 0;
}