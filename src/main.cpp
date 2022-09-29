#include <Chertila.hpp>

int main()
{
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

    // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }

    return 0;
}