#pragma once

#include <unordered_map>
#include <glm/vec4.hpp>

enum class Color
{
    Red,
    Green,
    Blue,
    Purple,
    Teal,
    Emerald,
    DarkBrown,
    White,
    Gray,
    Black,
    LightBlueTransparent,
    PurpleTransparent,
};

class ColorPalette
{
private:
    ColorPalette() = delete;
    ~ColorPalette() = delete;
    ColorPalette(const ColorPalette&) = delete;
    ColorPalette& operator=(const ColorPalette&) = delete;

    static std::unordered_map<Color, glm::vec4> colors;

public:
    static const glm::vec4& Get(Color color);
};
