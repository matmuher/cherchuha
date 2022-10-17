#include <ButtonManager.hpp>

ButtonManager::ButtonManager(size_t collection_capacity) : 
    m_collection_capacity{collection_capacity}
{
    try
    {
        m_button_collection = new Button*[collection_capacity];
    }
    catch (std::bad_alloc& e)
    {
        std::cout << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}

ButtonManager::~ButtonManager()
{
    delete [] m_button_collection;
}

size_t ButtonManager::get_size() const
{
    return m_collection_size;
}

void ButtonManager::add_button(Button& btn)
{
    m_button_collection[m_collection_size++] = &btn; 
}

Button& ButtonManager::get_button(size_t index) const
{
    return *(m_button_collection[index]);
}

void ButtonManager::catch_click(const Point& mouse_position)
{
    std::cout << "Collection size is : " << m_collection_size << std::endl;
    for (size_t btn_id = 0; btn_id < m_collection_size; btn_id++)
    {
        std::cout << "Mouse click caught" << std::endl;
        Button& btn = get_button(btn_id);
        if (is_in_area(btn.get_edges(), mouse_position))
        {
            if (!btn.is_pressed())
            {   
                std::cout << "Pressed button with id " << btn_id << std::endl;
                mutex_press(btn_id);
            }
            else
            {
                std::cout << "You pressed: " << btn_id << std::endl;
                std::cout << "If you want to change color, please choose another one" << std::endl;
            }
            break;
        }
    }
}

void ButtonManager::mutex_press(size_t pressed_button_id)
{
    for (size_t btn_id = 0; btn_id < m_collection_size; btn_id++)
    {
        Button& btn = get_button(btn_id);
        if (btn_id == pressed_button_id)
        {
            std::cout << "Pressed button with id: " << btn_id << std::endl;
            btn.press();
        }
        else
        {
            std::cout << "UN pressed button with id: " << btn_id << std::endl;
            btn.unpress();
        }
    }
}

bool is_in_area(const edge_type& edges, const Point& pnt)
{
    if (edges.left_up.get_x() <= pnt.get_x() && pnt.get_x() <= edges.right_up.get_x())
        if (edges.left_down.get_y() <= pnt.get_y() && pnt.get_y() <= edges.left_up.get_y())
            return true;
    return false;
}