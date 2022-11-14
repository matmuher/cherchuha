#include <FreeVector.hpp>

// [CTORS]

FreeVector::FreeVector () : m_end{} {};

FreeVector::FreeVector (Point end) : m_end{end} // Construct by end point
{
    //std::cout << "[VectorCtor] by end point" << m_end << std::endl;
}

FreeVector::FreeVector (float x, float y) : m_end{Point(x, y)}
{
    //std::cout << "[VectorCtor] by end coords" << m_end << std::endl;
}

FreeVector::FreeVector (float x, float y, float z) :
    FreeVector{Point(x, y, z)}
{}

FreeVector::FreeVector (const FreeVector &vec) // Copy constructor
{
    //std::cout << "[VectorCtor] cpy ctor" << std::endl; 
    m_end = vec.m_end;
}

// [OVERLOAD]

std::ostream& operator<< (std::ostream &cout, FreeVector vec)
{
    return cout << "(0,0,0)" << "--->" << vec.m_end;
}

float operator* (FreeVector vec1, FreeVector vec2)
{
    return vec1.m_end.get_x() * vec2.m_end.get_x() + 
           vec1.m_end.get_y() * vec2.m_end.get_y() +
           vec1.m_end.get_z() * vec2.m_end.get_z(); 
}

FreeVector operator* (float k, FreeVector vec)
{
    // Vector is created and then copied to place of function call
    return FreeVector{{k * vec.m_end.get_x(), k * vec.m_end.get_y(), k * vec.m_end.get_z()}};
}

FreeVector operator* (FreeVector vec, float k)
{
    return k * vec;
}

FreeVector operator+ (FreeVector vec1, FreeVector vec2)
{
    float x_res = vec1.m_end.get_x() + vec2.m_end.get_x();
    float y_res = vec1.m_end.get_y() + vec2.m_end.get_y();
    float z_res = vec1.m_end.get_z() + vec2.m_end.get_z();

    Point end_pnt{x_res, y_res, z_res};

    return FreeVector(end_pnt);
}

FreeVector operator- (FreeVector vec1, FreeVector vec2)
{
    return vec1 + (-1) * vec2;
}

// [FUNCTIONS]

float FreeVector::get_len () // I made it member function as it changes condition of object
{
    return m_len = sqrt((*this) * (*this)); // is "this" here ok?
}

float get_len (FreeVector vec)
{
    return sqrt(vec * vec);
}

Point FreeVector::get_pos () // Candidate to get out of member functions
{
    return m_end;
}

FreeVector& FreeVector::norm()
{
    float len = get_len();

    if (m_len != 0)
        (*this) = (*this) * (1 / m_len);

    return *this;
}

void FreeVector::set_end(const Point& end)
{
    m_end = end;
}

FreeVector reflect_surface (FreeVector surface_norm, FreeVector ray)
{
    return ray - 2.0 * (ray * surface_norm) * surface_norm;
}
