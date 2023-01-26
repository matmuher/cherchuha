#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <Point.hpp>
#include <VectorService.hpp>

class Texture
{
    sf::Texture sf_texture;

public:

    Texture(const std::string& name, Point size)
    {
        if (!sf_texture.loadFromFile(name, sf::IntRect(0, 0, size.x(), size.y())))
        {
            std::cout << "[ERROR] Cant load texture " << name << std::endl;
        }
    }

    const sf::Texture& get() const { return sf_texture; };

};