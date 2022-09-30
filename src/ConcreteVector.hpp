#pragma once

#include <Point.hpp>
#include <FreeVector.hpp>
#include <ConcreteVector.hpp>

class ConcreteVector // inheritance from free vector or vice versa?
{
    Point m_start {};
    Point m_end {};
    float m_len {};

public:

    ConcreteVector (Point &pnt, FreeVector &fvec); // apply fvec to pnt in user coords
    ConcreteVector (Point &start, Point &end);
    Point get_start ();
    Point get_end ();
    float get_len ();
};
