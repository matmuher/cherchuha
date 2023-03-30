#pragma once

#include <vector>
#include <Molbert.hpp>
#include <LaButton.hpp> 

struct ImageKernel
{
    float k;
    std::vector<std::vector<int>> kernel_matrix;
};

extern ImageKernel identity, box_blur;

class MolbertFilter
{
protected:

    Molbert& _mlbrt;
    const ImageKernel& _kernel;

public:

    MolbertFilter(Molbert& mlbrt, const ImageKernel& kernel = box_blur)
    :
        _mlbrt{mlbrt},
        _kernel{kernel} {};

    void apply()
    {
        DynamicArray<ParsedColor> copied_pixels = _mlbrt.copy_pixels();

        for (int y = 0; y < _mlbrt.iheight(); ++y)
        {
            for (int x = 0; x < _mlbrt.iwidth(); ++x)
            {
                _mlbrt[y][x] = process_one_pixel(x, y, copied_pixels);
            }
        }
    };

    ParsedColor process_one_pixel(int x, int y, const DynamicArray<ParsedColor>& copied_pixels)
    {
        if (x == 30 && y == 30)
        {
            return Colors::GREEN;
            std::cout << "molbert color: " << _mlbrt[y][x] << '\n';
        }

        int range = _kernel.kernel_matrix.size() / 2;
        FreeVector accumulator;

        for (int y_shift = -range; y_shift <= range; ++y_shift)
        {
            for (int x_shift = -range; x_shift <= range; ++x_shift)
            {
                int new_x = x + x_shift;
                int new_y = y + y_shift;

                if (_mlbrt.in_range(new_x, new_y))
                {
                    //std::cout << '\n';
                    int weight = _kernel.kernel_matrix[range + y_shift][range + x_shift];
                    //std::cout << FreeVector(copied_pixels[new_y][new_x]) * weight << '\n';
                    accumulator += FreeVector(copied_pixels[new_y][new_x]) * weight;
                    // std::cout << "w: " << weight << '\n';
                    // std::cout << "c: " << accumulator << '\n'; 
                    // std::cout << "k: " << _kernel.k << "\n\n";
                }
            }
        }

        accumulator *=_kernel.k;

        if (x == 30 && y == 30)
        {
            std::cout << "old color: " << copied_pixels[y][x] << '\n';
            std::cout << "acc: " << accumulator << '\n';
            std::cout << "res color: " << accumulator.to_color() << '\n'; 
            exit(1);
        }
        return accumulator.to_color();
    }
};

class FilterButton : public LaButton
{
    MolbertFilter& _filter;
    // Texture _texture;

public:

    FilterButton(MolbertFilter& filter, Point center, Point size, pixel_color color) : 
        LaButton{center, size, color},
        _filter{filter}
        // _texture{texture_name, size}
    {}

    virtual void proc_click(const Point& pnt) override
    {
        _filter.apply();
    }

    virtual void draw(Drawer& drwr, Canvas& cnvs) const override
    {
        LaButton::draw(drwr, cnvs);
        // drwr.draw(to_window_coords(cnvs, _rect), _texture);
    }
};
