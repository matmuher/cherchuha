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
    m_pintura_collection[m_collection_size++] = &pintura; 
}

LaPintura& PinturaManager::get_pintura(size_t index) const
{
    return *(m_pintura_collection[index]);
}

void PinturaManager::catch_click(const Point& mouse_position)
{
    std::cout << "Collection size is : " << m_collection_size << std::endl;
    for (size_t pintura_id = 0; pintura_id < m_collection_size; pintura_id++)
    {
        std::cout << "Mouse click caught" << std::endl;
        LaPintura& pintura = get_pintura(pintura_id);
        if (is_in_area(pintura.get_edges(), mouse_position))
        {
            pintura.paint_dot(mouse_position);
        }
    }
}
