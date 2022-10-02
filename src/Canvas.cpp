#include <Chertila.hpp>

// [CTORS]

Canvas::Canvas (Point &center) : 
    m_center{center}
{}

Canvas::Canvas () :
    m_center{}
{}

Canvas::Canvas(Point &center, Point &real_size, Point &pixel_size) :
    m_center{center},
    m_prop_coefs{ pixel_size.get_x() / real_size.get_x(), pixel_size.get_y() / real_size.get_y()}
{}

// [FUNCS]

Point Canvas::get_center ()
{
    return m_center;
}

Point Canvas::get_prop_coefs ()
{
    return m_prop_coefs;
}

Point apply_canvas(Canvas &cnvs, Point pnt)
{
    // is it okay to constantly make transforamtions point-abstract vector only because 
    // there are no sensible ariphmetic operations for point

    // can i only use FreeVectors?

    Point cnvs_center = cnvs.get_center();
    FreeVector center_vec{cnvs_center};
    
    Point prop_coefs = cnvs.get_prop_coefs();
    FreeVector pnt_vec{pnt.get_x() * prop_coefs.get_x(), pnt.get_y() * prop_coefs.get_y()};

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