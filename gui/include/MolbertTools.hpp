#pragma once

#include <Point.hpp>
#include <Molbert.hpp>
#include <LaButton.hpp>
#include <ImageProcess.hpp>
#include <queue> // for DFS-filling
#include <Texture.hpp>
#include <string>

class MolbertTool
{
protected:

    Molbert& _mlbrt;

public:

    MolbertTool(Molbert& mlbrt) : _mlbrt{mlbrt} {};

    virtual void apply(Point pos) = 0;
};

class ToolButton : public LaButton
{
    Molbert& _mlbrt;
    MolbertTool& _tool;
    Texture _texture;

public:

    ToolButton(Molbert& mlbrt, MolbertTool& tool, Point size, pixel_color color,
               const std::string& texture_name) : 
        _mlbrt{mlbrt},
        LaButton{size, color},
        _tool{tool},
        _texture{texture_name, size}
    {}

    virtual bool proc_click(const Point& pnt) override
    {
        _mlbrt.set_tool(&_tool);
    }

    virtual void draw(Drawer& drwr, Canvas& cnvs) const override
    {
        drwr.draw(to_window_coords(cnvs, _rect), _texture);
    }
};

class Brush : public MolbertTool
{

public:

    Brush(Molbert& mlbrt) : MolbertTool{mlbrt} {};

    void apply(Point pos)
    {
        _mlbrt.make_dot(pos, _mlbrt.get_color());
    }
};

class Eraser : public MolbertTool
{

public:

    Eraser(Molbert& mlbrt) : MolbertTool{mlbrt} {};

    void apply(Point pos)
    {
        _mlbrt.make_dot(pos, Colors::WHITE);
    }
};

class Pourer : public MolbertTool
{

public:

    Pourer(Molbert& mlbrt) : MolbertTool{mlbrt} {};

    // here we implement DFS-color spreading
    void apply(Point pos)
    {
        pixel_color filler_clr = _mlbrt.get_color();

        std::queue<Cell> cell_queue;
        Cell cur_cell = _mlbrt.get_cell(pos);

        if (cur_cell != ERROR_CELL)
            cell_queue.push(cur_cell);

        pixel_color old_clr = pixel_color(_mlbrt[cur_cell.y][cur_cell.x]);

        if (old_clr == filler_clr)
            return; // all work is done

        while (!cell_queue.empty())
        {
            cur_cell = cell_queue.front();
            cell_queue.pop();

            for (auto shift : shifts)
            {
                int new_x = cur_cell.x + shift.x;
                int new_y = cur_cell.y + shift.y;
                std::cout << "Applying to " << new_x << ' ' << new_y << '\n';

                if (
                    0 <= new_x < int(_mlbrt.get_width()) &&
                    0 <= new_y < int(_mlbrt.get_height()) &&
                    pixel_color(_mlbrt[new_y][new_x]) == old_clr
                   )
                    {
                        _mlbrt[new_y][new_x] = filler_clr;
                        cell_queue.push(Cell{new_x, new_y});
                    }
            }
        }
    }
};
