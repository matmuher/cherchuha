#pragma once

#include <ButtonManager.hpp>
#include <LaPintura.hpp>

class PinturaManager
{
    // Use dynamic array from standard librarty (if it exists)??
    LaPintura** m_pintura_collection = NULL; // Storage for button pointers
    size_t  m_collection_capacity = 0;
    size_t  m_collection_size = 0;

public:

    PinturaManager(size_t collection_capacity = 3);
    ~PinturaManager();

    void add_pintura(LaPintura& pintura);
    void catch_click(const Point& mouse_position);
    void mutex_press(size_t pressed_button_id);

    Button& get_pintura(size_t index) const;
    size_t get_size() const;
};