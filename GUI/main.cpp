#include <iostream>
#include <Chertila.hpp>
#include "Button.hpp"

/*
Version 1: MaPaint

features:
-canvas: user can draw on it with set color
-color buttons: clickable, set color (mutual exception)

buttons:
    make button class with 
        methods:
            draw, click
        member variables:
            is_pressed
            color

canvas:
    make canvas class 
*/

/*
Button:

    draw rectangle
    make wrapper around this rectangle to catch clicks
    on first click change rectangle's color
    create event(??) -> catch it from another button

*/

int main()
{
    // Set button
    Colors button_color = Colors::GREEN;
    Point size{80, 40};
    Point button_center{0, 0};
    Button btn{button_center, size.get_x(), size.get_y(), button_color};

    // Set user system
    Point real_size{200,200};
    float screen_width = 1280;
    Point pixel_resolution{screen_width / 2, screen_width / 2};
    Point window_resolution{screen_width, 720};

    Point cnvs_center{window_resolution.get_x() / 2, window_resolution.get_y() / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};

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

        // Draw
        drwr.clear();
        drwr.draw(cnvs);
        drwr.draw(to_window_coords(cnvs, btn));
        drwr.display();
    }

    return 0;
    // two_vectors();
}