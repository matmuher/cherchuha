#include <Chertila.hpp>

// [CTORS]

Canvas::Canvas (Point &center) : 
    m_center{center}
{}

Canvas::Canvas () :
    m_center{}
{}

Canvas::Canvas(Point center, Point real_size, Point pixel_size) :
    m_center{center},
    m_prop_coefs{ pixel_size.get_x() / real_size.get_x(), pixel_size.get_y() / real_size.get_y()},
    m_edges{set_edges(center, pixel_size)}
{}

edge_type Canvas::set_edges (Point &center, Point &pixel_size)
{
    edge_type edges = {};

    edges.left_up       =   Point{center.get_x() - pixel_size.get_x() / 2, center.get_y() - pixel_size.get_y() / 2};
    edges.left_down     =   Point{center.get_x() - pixel_size.get_x() / 2, center.get_y() + pixel_size.get_y() / 2};
    edges.right_up      =   Point{center.get_x() + pixel_size.get_x() / 2, center.get_y() - pixel_size.get_y() / 2};
    edges.right_down    =   Point{center.get_x() + pixel_size.get_x() / 2, center.get_y() + pixel_size.get_y() / 2};

    // std::cout << "Edges:\n";
    // std::cout << edges.left_up << ' ' << edges.left_down << ' ' << edges.right_up << ' ' << edges.right_down << std::endl;

    return edges;
}

// [FUNCS]

Point Canvas::get_center ()
{
    return m_center;
}

Point Canvas::get_prop_coefs ()
{
    return m_prop_coefs;
}

edge_type Canvas::get_edges()
{
    return m_edges;
}

Point to_window_coords(Canvas cnvs, Point pnt)
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

ConcreteVector to_window_coords(Canvas cnvs, ConcreteVector cvec)
{
    Point new_start = to_window_coords(cnvs, cvec.get_start());
    Point new_end   = to_window_coords(cnvs, cvec.get_end());

    return ConcreteVector{new_start, new_end};
}

Point to_canvas_coords(Canvas cnvs, Point pnt)
{
    Point cnvs_center = cnvs.get_center();
    FreeVector center_vec{cnvs_center};
    FreeVector pnt_vec{pnt};

    FreeVector result_vec = center_vec - pnt_vec;

    Point prop_coefs = cnvs.get_prop_coefs();
    // [!] Cringe form of matrix mlt
    Point result_point = Point{FreeVector{-1, 0} * result_vec / prop_coefs.get_x(), FreeVector{0, 1} * result_vec / prop_coefs.get_y()};

    return result_point;
}