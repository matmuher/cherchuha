#include <iostream>
#include <Chertila.hpp>
//#include <MaButton.hpp>
//#include <MaButtonManager.hpp>
//#include <ButtonManager.hpp>
//#include <LaPintura.hpp>
#include <bitset>
//#include <PinturaManager.hpp>

#include <LaButton.hpp>

int main()
{
    // Set button
    Point btn_size{80, 40};
    Point btn_cntr{0, 0}; 

    WidgetManager Desktop;

    LaButtonManagerMutex clr_plt; // pallete
    Desktop.addChild(&clr_plt);

    LaButton btn_g{btn_cntr, btn_size, Colors::GREEN};
    clr_plt.addChild(&btn_g);

    LaButton btn_r{btn_cntr + Point{200, 0}, btn_size, Colors::RED};
    clr_plt.addChild(&btn_r);

    LaButton btn_b{btn_cntr + Point{-200, 0}, btn_size, Colors::BLUE};
    clr_plt.addChild(&btn_b);

    // Set user system
    Point real_size{1280,720};
    Point pixel_resolution{real_size};
    Point window_resolution{real_size};

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

            case Event::EventType::MouseButtonPressed:

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    Point mouse_pos_cnvs = to_canvas_coords(cnvs, drwr.get_mouse_pos()); 
                    
                    std::cout << mouse_pos_cnvs << std::endl;

                    Desktop.catch_click(mouse_pos_cnvs);

                    std::cout << "MousePressed" << std::endl;
                }
                break;

            default:
                break;
        }

        // Draw
        drwr.clear();
        drwr.draw(cnvs);
        Desktop.draw(drwr, cnvs);
        drwr.display();
    }   
}

/*
int main()
{
    // Set button
    Point button_size{80, 40};
    Point btn1_cntr{-200, 0}, btn2_cntr{0, 0}, btn3_cntr{200, 0}; 

    WidgetManager Desktop;

    MaButton btn1;
    MaButtonCntrl btn_cntrl{btn1}; 
    MaButtonView btn1_vw{btn1, btn_cntrl, btn1_cntr, button_size, Colors::RED};

    MaButton btn2;
    MaButtonCntrl btn2_cntrl{btn2}; 
    MaButtonView btn2_vw{btn2, btn2_cntrl, btn2_cntr, button_size, Colors::GREEN};

    MaButton btn3;
    MaButtonCntrl btn3_cntrl{btn3}; 
    MaButtonView btn3_vw{btn3, btn3_cntrl, btn3_cntr, button_size, Colors::BLUE};

    MutexMaButtonManager btn_mngr;

    btn_mngr.addChild(&btn1_vw);
    btn_mngr.addChild(&btn2_vw);
    btn_mngr.addChild(&btn3_vw);

    Desktop.addChild(&btn_mngr);

    // Set user system
    Point real_size{1280,720};
    Point pixel_resolution{real_size};
    Point window_resolution{real_size};

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

            case Event::EventType::MouseButtonPressed:
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        Point mouse_pos_cnvs = to_canvas_coords(cnvs, drwr.get_mouse_pos()); 
                        std::cout << mouse_pos_cnvs << std::endl;
                        Desktop.catch_click(mouse_pos_cnvs);

                        std::cout << "MousePressed" << std::endl;
                        break;
                    }
                }
            default:
                break;
        }

        // Draw
        drwr.clear();
        drwr.draw(cnvs);
        Desktop.draw(drwr, cnvs);
        drwr.display();
    }   
}
*/

/*
int main1()
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

    PinturaManager pnt_mngr;
    pnt_mngr.add_pintura(pintura);

    // Set user system
    Point real_size{1280,720};
    Point pixel_resolution{real_size.get_x(), real_size.get_y()};
    Point window_resolution{real_size.get_x(), real_size.get_y()};

    Point cnvs_center{window_resolution.get_x() / 2, window_resolution.get_y() / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};

    Drawer drwr{window_resolution};

    bool MousePressed = false;

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

            case Event::EventType::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        MousePressed = true;
                        std::cout << "MousePressed" << std::endl;
                    }
                break;

            case Event::EventType::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        MousePressed = false;
                        std::cout << "MouseRealesed" << std::endl;
                    }
                break;

            default:
                break;
        }

        if (MousePressed)
        {
            btn_mngr.catch_click(to_canvas_coords(cnvs, drwr.get_mouse_pos()));
            pnt_mngr.catch_click(to_canvas_coords(cnvs, drwr.get_mouse_pos()));
        }

        std::cout << "Stop polling events" << std::endl;
        EventGUI gui_event;

        drwr.poll_gui_event(gui_event);
        std::cout << "Poll GUI events" << std::endl;
        switch (gui_event.type)
        {
            case EventGUI::EventType::PenColorChange:
                std::cout << "Pen colour change to: " << std::hex << (int) gui_event.color << std::endl;
                pintura.set_pen_color(gui_event.color);
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
*/