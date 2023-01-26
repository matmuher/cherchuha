#pragma once

#include <LaButton.hpp>
#include <Texture.hpp>
#include <SFML/Graphics.hpp>

class DecoButton : public Widget
{
    LaButton& _btn;

public:

    DecoButton(LaButton& btn) : _btn{btn} {};

    virtual void draw(Drawer& drwr, Canvas& cnvs) const override
    {
        _btn.draw(drwr, cnvs);
    } 
}

class TexturedButton : public DecoButton
{
    Texture _texture;

public:

    TexturedWidget(LaButton& btn) : _btn{btn} {};
};

class TextButton : public Widget
{

    LaButton& _btn;
    const std::string& _text;

public:

    TextButton(const std::string& text) : _text{text} {};
};