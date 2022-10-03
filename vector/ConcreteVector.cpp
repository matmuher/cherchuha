#include <ConcreteVector.hpp>

// [CTORS]

ConcreteVector::ConcreteVector (Point &pnt, FreeVector &fvec) : 
    m_start{pnt},
    m_end{(FreeVector(pnt) + fvec).get_pos()},
    m_fvec{fvec}
{}

ConcreteVector::ConcreteVector (Point &start, Point &end) : 
    m_start{start},
    m_end{end},
    m_fvec{FreeVector{end} - FreeVector{start}}
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

 void ConcreteVector::set_fvec (FreeVector fvec)
{
    m_fvec = fvec;
    m_end = (FreeVector(m_start) + fvec).get_pos();
}