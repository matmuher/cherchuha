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
        LaButton{size, color},
        _mlbrt{mlbrt},
        _tool{tool},
        _texture{texture_name, size}
    {}

    virtual void proc_click(const Point& pnt) override
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
#include <cstdlib>
class Pourer : public MolbertTool
{

public:

    Pourer(Molbert& mlbrt) : MolbertTool{mlbrt} {};

    // here we implement DFS-color spreading
    void apply(Point pos)
    {
        ParsedColor filler_clr = _mlbrt.get_color();
        Cell cur_cell = _mlbrt.get_cell(pos);

        if (cur_cell == ERROR_CELL)
        {
            std::cout << "[ERROR] Error cell in pourer\n";
            return;
        }

        ParsedColor old_clr = _mlbrt[cur_cell.y][cur_cell.x];
        std::queue<Cell> cell_queue;

        if (old_clr == filler_clr)
        {
            std::cout << "[INFO] Filler color is same as old color\n";
            return;
        }
        else
        {
            cell_queue.push(cur_cell);
        }

        while (!cell_queue.empty())
        {
            cur_cell = cell_queue.front();
            cell_queue.pop();

            // If have not already processed cell
            if (_mlbrt[cur_cell.y][cur_cell.x] == old_clr)
            {
                _mlbrt[cur_cell.y][cur_cell.x] = filler_clr;
                std::cout << "Main cell: " << cur_cell.y << ' ' << cur_cell.x << '\n';

                for (auto shift : shifts)
                {
                    int new_x = cur_cell.x + shift.x;
                    int new_y = cur_cell.y + shift.y;

                    std::cout << "Process cell [ " << new_y << ", " << new_x << "]\n" <<
                    "Cell color: " << _mlbrt[new_y][new_x] << "\n" <<
                    "Old color: "  << ParsedColor{old_clr} << "\n" <<
                    "Fill color: " << ParsedColor{filler_clr} << "\n";

                    if (
                        0 <= new_x && new_x < _mlbrt.iwidth() &&
                        0 <= new_y && new_y < _mlbrt.iheight() &&
                        pixel_color(_mlbrt[new_y][new_x]) == old_clr
                    )
                        {
                            std::cout << "Push " << new_y << ' ' << new_x << '\n' <<
                            "shift: " << shift.y << ' ' << shift.x << '\n'; 
                            //_mlbrt[new_y][new_x] = ParsedColor{filler_clr};
                            cell_queue.push(Cell{new_x, new_y});
                        }

                    std::cout << '\n';
                }
            }
        }
    }
};
