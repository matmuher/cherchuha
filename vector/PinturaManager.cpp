#include <PinturaManager.hpp>
#include <ButtonManager.hpp>
#include <Drawer.hpp>

/*
ROADMAP: Pintura

I need rasterized canvas, where I can put figures by coordinate
To to this I should got to raycast folder and user its pixel array
*/

PinturaManager::PinturaManager(size_t collection_capacity) : 
    m_collection_capacity{collection_capacity}
{
    try
    {
        m_pintura_collection = new LaPintura*[collection_capacity];
    }
    catch (std::bad_alloc& e)
    {
        std::cout << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}

PinturaManager::~PinturaManager()
{
    delete [] m_pintura_collection;
}

size_t PinturaManager::get_size() const
{
    return m_collection_size;
}

void PinturaManager::add_pintura(LaPintura& pintura)
{
    m_pinruta_collection[m_collection_size++] = &pintura; 
}

LaPintura& PinturaManager::get_pintura(size_t index) const
{
    return *(m_button_collection[index]);
}

void PinturaManager::catch_click(const Point& mouse_position)
{
    std::cout << "Collection size is : " << m_collection_size << std::endl;
    for (size_t pintura_id = 0; pintura_id < m_collection_size; pintura_id++)
    {
        std::cout << "Mouse click caught" << std::endl;
        Button& pintura = get_button(pintura_id);
        if (is_in_area(btn.get_edges(), mouse_position))
        {
            if (!pintura.is_pressed())
            {   
                EventGUI event{EventGUI::EventType::PenColorChange};
                event.color = pintura.get_color();

                Drawer::push_gui_event(event);

                std::cout << "Pressed button with id " << pintura_id << std::endl;
                mutex_press(pintura_id);
            }
            else
            {
                std::cout << "You pressed: " << pintura_id << std::endl;
                std::cout << "If you want to change color, please choose another one" << std::endl;
            }
            break;
        }
    }
}
