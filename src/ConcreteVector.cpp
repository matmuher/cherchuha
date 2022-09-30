#include <ConcreteVector.hpp>

// [CTORS]

ConcreteVector::ConcreteVector (Point &pnt, FreeVector &fvec) : 
    m_start{pnt},
    m_end{(FreeVector(pnt) + fvec).get_pos()}
{}

ConcreteVector::ConcreteVector (Point &start, Point &end) : 
    m_start{start},
    m_end{end}
{}

// [FUNKS]

Point ConcreteVector::get_start ()
{
    return m_start;
}

Point ConcreteVector::get_end ()
{
    return m_end;
}

float ConcreteVector::get_len () // Can be done via FreeVector, but seems tough
{
    float diff_x = m_start.get_x() - m_end.get_x(),
          diff_y = m_start.get_y() - m_end.get_y();

    return m_len = sqrt(diff_x * diff_x + diff_y * diff_y);
}