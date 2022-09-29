#include <Point.hpp>

Point::Point () : m_x{}, m_y{} 
{
    //std::cout << "[CALL] Default ctor\n";
}

Point::Point (float x, float y) : m_x{x}, m_y{y} 
{
    //std::cout << "[CALL] Float ctor: " << m_x << ' ' << m_y << ' ' << this << std::endl;
}

Point::Point (const Point &pnt) : m_x{pnt.m_x}, m_y{pnt.m_y} // const here express our wish not to change donor object
{
    //std::cout << "[CALL] Copy ctorL: \n" << pnt.m_y << "->" << m_y << std::endl;
}

Point::~Point () 
{
    //std::cout << "[CALL] Dtor:" << m_x << ' ' << m_y << ' ' << this << std::endl;
}

 Point& Point::operator= (const Point& pnt)
 {
    //std::cout << "Assignment operator here" <<std::endl;

    m_x = pnt.m_x;
    m_y = pnt.m_y;

    return *this;   // Dereference of current object -> but ret type is refrence and
                    // casting will happen
 }

Point operator- (Point &pnt1, Point &pnt2)
{
    //std::cout << "Minus operator" << std::endl;
    return Point(pnt1.m_x - pnt2.m_x, pnt1.m_y - pnt2.m_y);
}

float Point::get_x ()
{
    return m_x;
}

float Point::get_y ()
{
    return m_y;
}

std::ostream& operator<< (std::ostream &cout, Point pnt)
{
    return cout << '(' << pnt.m_x << ',' << pnt.m_y << ')';
}
