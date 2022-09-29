#include <FreeVector.hpp>

// [CTORS]

FreeVector::FreeVector (Point &end) : m_end{end} // Construct by end point
{
    //std::cout << "[VectorCtor] by end point" << m_end << std::endl;
}

FreeVector::FreeVector (float x, float y) : m_end{Point(x, y)}
{
    //std::cout << "[VectorCtor] by end coords" << m_end << std::endl;
}

FreeVector::FreeVector (const FreeVector &vec) // Copy constructor
{
    //std::cout << "[VectorCtor] cpy ctor" << std::endl; 
    m_end = vec.m_end;
}

// [OVERLOAD]

std::ostream& operator<< (std::ostream &cout, FreeVector vec)
{
    return cout << "(0,0)" << "--->" << vec.m_end;
}

float operator* (FreeVector vec1, FreeVector vec2)
{
    return vec1.m_end.get_x() * vec2.m_end.get_x() + vec1.m_end.get_y() * vec2.m_end.get_y(); 
}

FreeVector operator* (float k, FreeVector &vec)
{
    std::cout << "left scalar\n";
    // Vector is created and then copied to place of function call
    return FreeVector{k * vec.m_end.get_x(), k * vec.m_end.get_y()};
}

FreeVector operator* (FreeVector &vec, float k)
{
    std::cout << "right scalar\n";
    return k * vec;
}

FreeVector operator+ (FreeVector vec1, FreeVector vec2)
{
    float x_res = vec1.m_end.get_x() + vec2.m_end.get_x();
    float y_res = vec1.m_end.get_y() + vec2.m_end.get_y();

    Point end_pnt{x_res, y_res};

    return FreeVector(end_pnt);
}

// [FUNCTIONS]

float FreeVector::get_len () // I made it member function as it changes condition of object
{
    return m_len = sqrt((*this) * (*this)); // is "this" here ok?
}

Point FreeVector::get_pos () // Candidate to get out of member functions
{
    return m_end;
}
