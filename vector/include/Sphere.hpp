#pragma once

#include <Point.hpp>
#include <FreeVector.hpp>
#include <ConcreteVector.hpp>
#include <VectorService.hpp>

class Sphere
{
public:
    // why use getters if i can make variables const?
    Point m_center;
    const float m_R;
    Material material;

    Sphere(const Point& center, float R) : m_center{center}, m_R{R} {};
    Sphere(const Point& center, float R, Material m) : m_center{center}, m_R{R}, material{m} {};
    FreeVector get_norm(const Point& pnt); // no belong check

    // d - ray direction, t1 - first intersect, t2 - second
    bool ray_intersect(FreeVector d, float& t1, float& t2);
};
