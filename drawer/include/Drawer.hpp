#pragma once

#include <SFML/Graphics.hpp>
#include <ConcreteVector.hpp>
#include <Point.hpp>
#include <Canvas.hpp>
#include <Rectangle.hpp>
//#include <ButtonManager.hpp>
#include <queue>
//#include <LaPintura.hpp>
#include <PixeledCanvas.hpp>
#include <Texture.hpp>

/*
OKAY, now it's time to handle my own events.
I wanna handle event created by button. 
For now these kind of events would be located in separate
data structure like queue (because most recent events should be processed firstly).
*/

// Wrapper on SFML's event class
class Event : public sf::Event
{};

class EventGUI
{

public:

    enum EventType
    {
        NoEvent = 0,
        PenColorChange
    };

    EventType type;

    // Content

    typedef Colors ChangePenColor;

    union
    {
        ChangePenColor color;
    };

    // [Member functions]

    EventGUI(EventType type) : type{type} {};
    EventGUI() : type{NoEvent} {};

    // [Member data]

    // Type

};

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
    const std::string std_font_path = "fonts/default.ttf";
    const size_t defaultSize = 1000; // Dont use m_ with consts
    const float pointRadius = 2;    // cause there shouldn't be any mess with assignments
    const float lineWidth = 20;

    static std::queue<EventGUI> EventsQueue;

    sf::RenderWindow m_window{};
    sf::Font font;

public:
    // [Ctors]
    Drawer();
    Drawer(Point &screeSize);

    // [Drawing]
    void draw(ConcreteVector cvec);
    void draw(Point pnt);
    void draw(Canvas cnvs);
    void draw(const Rectangle& rect);
    // void draw(const Canvas& cnvs, const ButtonManager& btn_mngr);
    //void draw(const LaPintura& pintura);
    void draw(const Canvas& gui_cnvs, const PixeledCanvas& pxld_canvas);
    void draw(const Rectangle& rect, const Texture& texture);
    void draw(const Rectangle& rect, const std::string& text);
    void display();
    void clear();

    // [Events]
    bool is_opened();
    void close();
    bool poll_event(Event& event);
    static void push_gui_event(const EventGUI& event);
    static bool poll_gui_event(EventGUI& event);

    // [Getters]
    sf::RenderWindow& get_window();
    Point get_mouse_pos();
};
