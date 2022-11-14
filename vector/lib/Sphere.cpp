#include <Sphere.hpp>
#include <math.h>

FreeVector Sphere::get_norm(const Point& pnt)
{
    FreeVector vec{pnt - m_center};
    vec.norm();

    return vec;
}

bool Sphere::ray_intersect(FreeVector d, float& t1, float& t2)
{
    t1 = 0;
    t2 = 0;

    FreeVector OC{m_center};
    d.norm();

    FreeVector OP{d * (OC * d)};
    float OP_len = get_len(OP);    
    FreeVector n = OC - OP;
    float n_len = get_len(n);
    
    if (n_len > m_R)
    {
        return false;
    }
    else if (n_len == m_R)
    {
        t1 = OP_len;
        if (t1 == 0) std::cerr << "wtf\n";
        return true;
    }
    else
    {
        float x = sqrt(m_R * m_R - n*n);
        FreeVector En = OP - d * x; // Entry
        FreeVector Ex = OP + d * x; // Exit

        t1 = get_len(En); 
        t2 = get_len(Ex);

        // std::cout << t1 << " " << t2 << std::endl;
        // std::cout << get_len(d*t1 - OC) << std::endl;
        return true;
    }
}