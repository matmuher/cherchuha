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

float ConcreteVector::get_len ()
{
    return m_len = sqrt(m_fvec * m_fvec);
}

 void ConcreteVector::set_fvec (FreeVector fvec)
{
    m_fvec = fvec;
    m_end = (FreeVector(m_start) + fvec).get_pos();
}

FreeVector ConcreteVector::get_fvec()
{
    return m_fvec;
}
