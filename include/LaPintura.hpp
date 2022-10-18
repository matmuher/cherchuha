#pragma once

#include <Rectangle.hpp>
#include <SFML/Graphics.hpp>
#include <VectorService.hpp>

/*
LaPintura:

array of pixels, num of pixels = width * height
Textute
Sprite

draw on texture

update texture / sprite
*/
typedef unsigned pixel_color;

class LaPintura
{
Colors m_pen_color;
Colors m_pintura_color;

size_t m_pintura_resolution;
float m_width;
float m_height;
edge_type m_edges;

Point m_pintura_center;

pixel_color* m_pixels;

void put_color(pixel_color* pixel, Colors color);
edge_type set_edges(const Point& pintura_center,  float width, float height);
size_t get_pixel_id(const Point& pnt);

public:

    // [Ctors]

    LaPintura(const Point& pintura_center, float width, float height, 
              Colors pintura_color = Colors::WHITE, Colors pen_color = Colors::RED);
    
    ~LaPintura();
    
    LaPintura(const LaPintura& pintura);

    // [Functions]

    void paint_dot(const Point& pnt);
    void fill(Colors fill_color);
    
    // [Getters]

    Point get_center() const;
    float get_width() const;
    float get_height() const;
    const pixel_color* get_array() const;
    edge_type get_edges() const;

    // [Setters]

    void set_center(const Point& new_center);
    void set_pen_color(Colors color);
};