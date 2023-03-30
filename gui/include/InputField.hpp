#pragma once

#include <LaButton.hpp>
#include <Decorators.hpp>
#include <Molbert.hpp>

class InputField : public Widget
{
protected:

    LaButton descript_btn; // TODO Static button that is not clickable
    TextButton descript_text;

    LaButton input_btn;
    TextButton input_text;

    bool is_enter_mode = false;

public:

    InputField(const std::string& descript_msg, Point descript_center, float height,
               float descript_len, float input_len,
               pixel_color clr = Colors::WHITE)
    :
        descript_btn{descript_center, Point{descript_len, height}, Colors::GRAY},
        descript_text{descript_btn, descript_msg},
        input_btn{descript_center + Point{descript_len / 2 + input_len / 2, 0},
                  Point{input_len, height}, Colors::RED},
        input_text{input_btn, ""} {}

    // Adopt for string length
    InputField(const std::string& descript_msg, Point descript_center, float height,
               size_t max_symbols_num)
    :
        descript_btn{descript_center, height, descript_msg.size(), Colors::GRAY},
        descript_text{descript_btn, descript_msg},
        input_btn{
                    descript_btn.right_center() +
                    Point::horizontal_shift(LaButton::compute_width_for_text(height, max_symbols_num) / 2),
                    height,
                    max_symbols_num,
                    Colors::BLUE
                 },
        input_text{input_btn, "", max_symbols_num} {}

    virtual void proc_click(const Point& pnt) override
    {
        input_btn.proc_click(pnt);
        is_enter_mode = input_btn.get_press_status();
    }

    virtual bool is_in_area(const Point& pnt) override
    {
        return descript_btn.is_in_area(pnt) || input_btn.is_in_area(pnt);
    }

    void catch_char(char c)
    {
        if (is_enter_mode)
        {
            TextButton::ASCII_PROC ret_code = input_text.process_ascii(c);

            if (ret_code == TextButton::ASCII_PROC::ENTER)
            {
                send_field();
            }
        }
    }

    virtual void send_field() = 0;

    virtual void draw(Drawer& drwr, Canvas& cnvs) const override
    {
        descript_text.draw(drwr, cnvs);
        input_text.draw(drwr, cnvs);
    }
};

class LoadFileInputField : public InputField
{
    Molbert& _mlbrt;

public:

    LoadFileInputField(Molbert& mlbrt, Point descript_center, float height, size_t max_symbols_num)
    :
        InputField("open file:", descript_center, height, max_symbols_num),
        _mlbrt{mlbrt}
    {}

    virtual void send_field()
    {
        std::string text = input_text.get_text();

        if (!text.empty())
        {
            _mlbrt.load_from_file(text);
        }
    }
};