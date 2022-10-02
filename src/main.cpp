#include <Chertila.hpp>

/*
Nearest roadmap:

- Change Canvas class to get pixels and real sizes
- Make a cat from arrow side of vector
- Make the second canvas with interactive vector
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
    FreeVector vec{-3, 2};
    ConcreteVector cvec{pnt, vec};
    
    // Set user system
    Point cnvs_center{1280 / 2, 720 / 2};
    Point real_size{6,4};
    Point pixel_size{1280, 720};
    Canvas cnvs{cnvs_center, real_size, pixel_size};

    Drawer drwr{pixel_size};
    // float t = 0;
    // float dt = 1E-2;
    // const float R = 200;

    while (drwr.is_opened())
    {
        // cvec.set_fvec(FreeVector{R * sin(t), R * cos(t)});
        // t += dt;

        drwr.clear();
        // drwr.draw(pnt);
        drwr.draw(apply_canvas(cnvs, cvec));
        drwr.display();
    }

    return 0;
}