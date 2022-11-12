#include <Point.hpp>

Point::Point () : m_x{}, m_y{}, m_z{}
{
    //std::cout << "[CALL] Default ctor\n";
}

Point::Point (float x, float y) : m_x{x}, m_y{y}, m_z{}
{
    //std::cout << "[CALL] Float ctor: " << m_x << ' ' << m_y << ' ' << this << std::endl;
}

Point::Point (float x, float y, float z) : m_x{x}, m_y{y}, m_z{z}
{
    //std::cout << "[CALL] Float ctor: " << m_x << ' ' << m_y << ' ' << this << std::endl;
}

Point::Point (const Point &pnt) : m_x{pnt.m_x}, m_y{pnt.m_y}, m_z{pnt.m_z} // const here express our wish not to change donor object
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
    m_z = pnt.m_z;

    return *this;   // Dereference of current object -> but ret type is refrence and
                    // casting will happen
 }

Point operator- (const Point& pnt1,const Point& pnt2)
{
    //std::cout << "Minus operator" << std::endl;
    return Point(pnt1.m_x - pnt2.m_x, pnt1.m_y - pnt2.m_y, pnt1.m_z - pnt2.m_z);
}

Point operator+ (const Point& pnt1,const Point& pnt2)
{
    //std::cout << "Minus operator" << std::endl;
    return Point(pnt1.m_x + pnt2.m_x, pnt1.m_y + pnt2.m_y, pnt1.m_z + pnt2.m_z);
}

float Point::get_x () const
{
    return m_x;
}

float Point::get_y () const
{
    return m_y;
}

float Point::get_z () const
{
    return m_z;
}

std::ostream& operator<< (std::ostream &cout, const Point& pnt)
{
    return cout << '(' << pnt.m_x << ',' << pnt.m_y <<  ',' << pnt.m_z << ')';
}
