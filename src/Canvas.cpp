#include <Chertila.hpp>

// [CTORS]

Canvas::Canvas (Point &center) : 
    m_center{center}
{}

Canvas::Canvas () :
    m_center{}
{}

// [FUNCS]

Point Canvas::get_center ()
{
    return m_center;
}

Point apply_canvas(Canvas &cnvs, Point pnt)
{
    // is it okay to constantly make transforamtions point-abstract vector only because 
    // there are no sensible ariphmetic operations for point

    // can i only use FreeVectors?

    Point cnvs_center = cnvs.get_center();
    FreeVector center_vec{cnvs_center};
    
    FreeVector pnt_vec{pnt};

    // [!] Cringe form of matrix mlt
    FreeVector transformed_point = FreeVector{FreeVector{1, 0} * pnt_vec, FreeVector{0, -1} * pnt_vec} + center_vec;

    return transformed_point.get_pos();
}

ConcreteVector apply_canvas(Canvas &cnvs, ConcreteVector &cvec)
{
    Point new_start = apply_canvas(cnvs, cvec.get_start());
    Point new_end   = apply_canvas(cnvs, cvec.get_end());

    return ConcreteVector{new_start, new_end};
}