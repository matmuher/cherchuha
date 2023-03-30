#pragma once

#include <chrono>

class CoolDowner
{
    double _cooldown; // milisecs
    decltype(std::chrono::steady_clock::now()) last_click_time;

public:

    CoolDowner(double cooldown = 10) : _cooldown{cooldown} {}

    bool is_valid_action()
    {
        auto click_time = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>
                        (click_time - last_click_time);

        bool is_valid = diff.count() > _cooldown;
    
        last_click_time = click_time;

        return is_valid;
    }
};