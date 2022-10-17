#pragma once

#include <Button.hpp>

class ButtonManager
{
    // Use dynamic array from standard librarty (if it exists)??
    Button** m_button_collection = NULL; // Storage for button pointers
    size_t  m_collection_capacity = 0;
    size_t  m_collection_size = 0;

public:

    ButtonManager(size_t collection_capacity = 3);
    ~ButtonManager();

    void add_button(Button& btn);
    void catch_click(const Point& mouse_position);
    void mutex_press(size_t pressed_button_id);

    Button& get_button(size_t index) const;
    size_t get_size() const;
};

bool is_in_area(const edge_type& edges, const Point& pnt);