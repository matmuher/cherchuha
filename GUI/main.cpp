#include <iostream>
#include <Chertila.hpp>
#include <Button.hpp>
#include <ButtonManager.hpp>
#include <LaPintura.hpp>
#include <bitset>

/*
Version 1: MaPaint

features:
-canvas: user can draw on it with set color
-color buttons: clickable, set color (mutual exception)

buttons:
    make button class with 
        methods:
            draw[OK], click
        member variables:
            is_pressed[OK]
            color[OK]

canvas:
    make canvas class
    draw with fixed color
    intaraction with buttons to get this color 
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
    Point button_size{80, 40};
    Point button_center{550, -50};
    Button btn{button_center, button_size.get_x(), button_size.get_y(), Colors::RED};
    Button btn1{Point{550, 50}, button_size.get_x(), button_size.get_y(), Colors::GREEN};
    Button btn2{Point{550, 0}, button_size.get_x(), button_size.get_y(), Colors::BLUE};

    ButtonManager btn_mngr{3};
    btn_mngr.add_button(btn);
    btn_mngr.add_button(btn1);
    btn_mngr.add_button(btn2);

    // Set LaPintura
    Point pintura_size{500, 500};
    Point pintura_center{-100, 0};
    LaPintura pintura{pintura_center, pintura_size.get_x(), pintura_size.get_y(), Colors::WHITE};

    // Set user system
    Point real_size{1280,720};
    Point pixel_resolution{real_size.get_x(), real_size.get_y()};
    Point window_resolution{real_size.get_x(), real_size.get_y()};

    Point cnvs_center{window_resolution.get_x() / 2, window_resolution.get_y() / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};

    Drawer drwr{window_resolution};

    while (drwr.is_opened())
    {
        // Events
        Event event;
        drwr.poll_event(event);
        std::cout << "Poll events" << std::endl;
        switch (event.type)
        {
            case Event::EventType::Closed:
                drwr.close();
                break;

            case Event::EventType::MouseButtonReleased:
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {std::cout << "MousePressed\n";
                    btn_mngr.catch_click(to_canvas_coords(cnvs, drwr.get_mouse_pos()));}
                break;

            default:
                break;
        }
        std::cout << "Stop polling events" << std::endl;
        EventGUI gui_event;

        drwr.poll_gui_event(gui_event);
        std::cout << "Poll GUI events" << std::endl;
        switch (gui_event.type)
        {
            case EventGUI::EventType::PenColorChange:
                std::cout << "Pen colour change to: " << std::hex << (int) gui_event.color << std::endl;
                break;

            default:
                break;
        }
        std::cout << "Stop polling GUI events" << std::endl;
    
        // Draw
        drwr.clear();
        drwr.draw(cnvs);
        drwr.draw(to_window_coords(cnvs, pintura));
        drwr.draw(cnvs, btn_mngr);
        drwr.display();
    }

    return 0;
    // two_vectors();
}