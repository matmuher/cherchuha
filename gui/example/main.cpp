#include <iostream>
#include <Chertila.hpp>
//#include <MaButton.hpp>
//#include <MaButtonManager.hpp>
//#include <ButtonManager.hpp>
//#include <LaPintura.hpp>
#include <bitset>
//#include <PinturaManager.hpp>

#include <LaButton.hpp>
#include <ColorButton.hpp>
#include <Molbert.hpp>
#include <MolbertTools.hpp>
#include <Decorators.hpp>

int main()
{
    // Set button
    Point btn_size{80, 40};

    WidgetManager Desktop;

    Molbert mlbrt{{0, 0}, {500, 500}, 10};
    Desktop.addChild(&mlbrt);

    ColorButton test_btn{Point{300, -300}, btn_size, Colors::GRAY};
    TextButton text_btn{test_btn, "gray"};
    Desktop.addChild(&text_btn);

    Point color_bar_cntr{-80, 300}; 
    ColorButtonManager clr_plt{mlbrt, color_bar_cntr, btn_size}; // pallete
    Desktop.addChild(&clr_plt);

    clr_plt.add_color_button(Colors::RED);
    clr_plt.add_color_button(Colors::GREEN);
    clr_plt.add_color_button(Colors::BLUE);

    Point tool_bar_center{-300, 200};
    ButtonBar tool_bar{tool_bar_center, btn_size, BarMode::V, 10};
    Desktop.addChild(&tool_bar);

    Brush brsh{mlbrt};
    Pourer ersr{mlbrt};
    auto brsh_btn = new ToolButton{mlbrt, brsh, btn_size, Colors::WHITE, "textures/brush.png"};
    auto ersr_btn = new ToolButton{mlbrt, ersr, btn_size, Colors::WHITE, "textures/pourer.jpg"};

    tool_bar.add_button(brsh_btn);
    tool_bar.add_button(ersr_btn);

    // Set user system
    Point real_size{1280,720};
    Point pixel_resolution{real_size};
    Point window_resolution{real_size};

    Point cnvs_center{window_resolution.get_x() / 2, window_resolution.get_y() / 2};
    Canvas cnvs{cnvs_center, real_size, pixel_resolution};

    Drawer drwr{window_resolution};

    bool mouse_pressed = false;
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

            // for smooth drawing
            case Event::EventType::MouseButtonPressed:

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    mouse_pressed = true;
                    std::cout << "Pressed" << std::endl;
                break;

            case Event::EventType::MouseButtonReleased:

                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    mouse_pressed = false;
                    std::cout << "Realeased" << std::endl;
                break;

            default:
                break;
        }

        if (mouse_pressed)
        {
            Point mouse_pos_cnvs = to_canvas_coords(cnvs, drwr.get_mouse_pos()); 
                    
            std::cout << mouse_pos_cnvs << std::endl;

            Desktop.catch_click(mouse_pos_cnvs);

            std::cout << "MousePressed" << std::endl;
        }

        // Draw
        drwr.clear();
        drwr.draw(cnvs);
        Desktop.draw(drwr, cnvs);
        drwr.display();
    }   
}
