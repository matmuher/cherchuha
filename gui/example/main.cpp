#include <iostream>
#include <Chertila.hpp>
// #include <MaButton.hpp>
// #include <MaButtonManager.hpp>
// #include <ButtonManager.hpp>
// #include <LaPintura.hpp>
#include <bitset>
// #include <PinturaManager.hpp>

#include <LaButton.hpp>
#include <ColorButton.hpp>
#include <Molbert.hpp>
#include <MolbertTools.hpp>
#include <Decorators.hpp>
#include <InputField.hpp>
#include <MolbertFilters.hpp>

int main()
{
    // Set button
    Point btn_size{80, 40};

    WidgetManager Desktop;

    Molbert mlbrt{{0, 0}, {500, 500}, 10};
    //mlbrt.load_from_file("test_car.jpg");

    Desktop.addChild(&mlbrt);

    LoadFileInputField input{mlbrt, Point{100, -300}, 40, 15};
    // LaButton test_btn{Point{300, -300}, btn_size, Colors::GRAY};
    // TexturedButton texture_btn{test_btn, "textures/pourer.jpg"};
    // TextButton text_btn{texture_btn, "MEOW"};
    Desktop.addChild(&input);

    Point filter_bar_center{320, 200};
    ButtonBar filter_bar{filter_bar_center, btn_size, BarMode::V, 10};
    Desktop.addChild(&filter_bar);

    MolbertFilter box_blur_filter{mlbrt, box_blur};
    MolbertFilter edge_filter{mlbrt, edge_detection};
    MolbertFilter gauss_filter{mlbrt, gauss_blur};
    MolbertFilter sharpen_filter{mlbrt, sharpen};

    Point flt_btn_size{110, 40};

    FilterButton box_blur_filter_btn{box_blur_filter, flt_btn_size, Colors::CYAN};
    FilterButton edge_filter_btn{edge_filter, flt_btn_size, Colors::CYAN};
    FilterButton gauss_filter_btn{gauss_filter, flt_btn_size, Colors::CYAN};
    FilterButton sharpen_filter_btn{sharpen_filter, flt_btn_size, Colors::CYAN};

    TextButton f1{box_blur_filter_btn, "Box blur"};
    TextButton f2{edge_filter_btn, "Edge detect"};
    TextButton f3{gauss_filter_btn, "Gauss blur"};
    TextButton f4{sharpen_filter_btn, "Sharpen"};

    filter_bar.add_button(&f1);
    filter_bar.add_button(&f2);
    filter_bar.add_button(&f3);
    filter_bar.add_button(&f4);

    Point color_bar_cntr{-240, 300};
    ColorButtonManager clr_plt{mlbrt, color_bar_cntr, btn_size}; // pallete
    Desktop.addChild(&clr_plt);

    clr_plt.add_color_button(Colors::RED);
    clr_plt.add_color_button(Colors::GREEN);
    clr_plt.add_color_button(Colors::BLUE);
    clr_plt.add_color_button(Colors::GRAY);
    clr_plt.add_color_button(Colors::CYAN);
    clr_plt.add_color_button(Colors::YELLOW);
    clr_plt.add_color_button(Colors::LAVENDER);

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
    Point real_size{1280, 720};
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

        case Event::EventType::TextEntered:

            std::cout << "Entered: " << static_cast<int>(event.text.unicode) << '\n';
            input.catch_char(static_cast<char>(event.text.unicode));
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
