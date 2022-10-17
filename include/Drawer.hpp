#pragma once

#include <SFML/Graphics.hpp>
#include <ConcreteVector.hpp>
#include <Point.hpp>
#include <Canvas.hpp>
#include <Rectangle.hpp>

// Wrapper on SFML's event class
class Event : public sf::Event
{};

/*
This class should get geometric primitives and draw it on the screen

The spirit of such architecture is spirit of OOP.
I wanna be able to easily change internals of objects without affectiing
users' programms.

Example of work:

// Window wndw{}; // Default size
// Drawer drwr{wndw}; // Attach to window. It is done to be able to draw in different windows

Drawer drwr{}; // Creates window of default size and allows to draw there

Point pnt{1,1};
drwr.draw(pnt);

ConcreteVector cvec{1,1};
drwr.draw(cvec);
*/

class Drawer
{
    const size_t defaultSize = 1000; // Dont use m_ with consts
    const float pointRadius = 2;    // cause there shouldn't be any mess with assignments
    const float lineWidth = 20;

    sf::RenderWindow m_window{};

public:
    // [Ctors]
    Drawer();
    Drawer(Point &screeSize);

    // [Drawing]
    void draw(ConcreteVector cvec);
    void draw(Point pnt);
    void draw(Canvas cnvs);
    void draw(const Rectangle& rect);
    void display();
    void clear();

    // [Events]
    bool is_opened();
    void close();
    void poll_event(Event& event);

    // [Getters]
    sf::RenderWindow& get_window();
};
