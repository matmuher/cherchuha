#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Point
{
    float m_x {}, m_y {};

public:

    // Ctors
    Point (float x, float y) : m_x{x}, m_y{y} {std::cout << "[CALL] Float ctor:" << m_x << ' ' << m_y << std::endl;}
    Point () : m_x{}, m_y{} {std::cout << "[CALL] Default ctor\n";}
    Point (const Point& pnt) : m_x{pnt.m_x}, m_y{pnt.m_y} {std::cout << "[CALL] Copy ctor\n";} // const here express our wish not to change donor object

    // Dtor
    ~Point () {std::cout << "[CALL] Dtor:" << m_x << ' ' << m_y << std::endl;}

    // Overload
    friend std::ostream& operator<< (std::ostream &cout, Point &pnt);
    friend Point operator- (Point &pnt1, Point &pnt2);
    Point& operator= (const Point& pnt);
};

 Point& Point::operator= (const Point& pnt)
 {
    m_x = pnt.m_x;
    m_y = pnt.m_y;

    return *this;   // Dereference of current object -> but ret type is refrence and
                    // casting will happen
 }

Point operator- (Point &pnt1, Point &pnt2)
{
    return Point(pnt1.m_x - pnt2.m_x, pnt1.m_y - pnt2.m_y);
}

std::ostream& operator<< (std::ostream &cout, Point &pnt)
{
    return cout << '(' << pnt.m_x << ',' << pnt.m_y << ')';
}

class Vector
{
    Point m_start {}, m_end {};
    float m_len {};

    void update_len ();

public:

    // Ctors
    Vector (Point &start, Point &end) : m_start {start}, m_end {end} {}

    // Overload
    friend std::ostream& operator<< (std::ostream &cout, Vector &vec);

    // Functionality
    void to_center ();
};

void Vector::to_center (void)
{
    m_end = m_end - m_start;
    m_start = Point(0.f, 0.f);
}

std::ostream& operator<< (std::ostream &cout, Vector &vec)
{
    return cout << vec.m_start << "--->" << vec.m_end << std::endl;
}

void Vector::update_len ()
{
    m_len = sqrt(1);
}

int main()
{
    Point pnt1{-1,-1}, pnt2{2,2};

    Point dif_pnt {pnt2 - pnt1};

    // dif_pnt = pnt1 - pnt2;

    // std::cout << dif_pnt << std::endl; // But here Point&

    // std::cout << pnt2 - pnt1 << std::endl; // why here Point

    // std::cout << pnt1 << ' ' << pnt2 << std::endl;
    
    Vector vec{pnt1, pnt2};
    std::cout << vec << std::endl;

    vec.to_center();
    std::cout << vec << std::endl;

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