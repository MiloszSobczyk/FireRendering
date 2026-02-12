#include "ColorPalette.h"

std::unordered_map<Color, glm::vec4> ColorPalette::colors = {
    { Color::Red,       glm::vec4(1.f, 0.f, 0.f, 1.f) },
    { Color::Green,     glm::vec4(0.f, 1.f, 0.f, 1.f) },
    { Color::Blue,      glm::vec4(0.f, 0.f, 1.f, 1.f) },
    { Color::Purple,    glm::vec4(.5f, .1f, .5f, 1.f) },
    { Color::Teal,      glm::vec4(0.f, .8f, .8f, 1.f) },
    { Color::Emerald,   glm::vec4(0.f, .8f, 0.f, 1.f) },
    { Color::DarkBrown, glm::vec4(0.2f, 0.13f, 0.09f, 1.f) },
    { Color::White,     glm::vec4(1.f, 1.f, 1.f, 1.f) },
    { Color::Gray,      glm::vec4(0.83f, 0.83f, 0.83f, 1.f) },
    { Color::Black,     glm::vec4(0.f, 0.f, 0.f, 1.f) },
    { Color::LightBlueTransparent, glm::vec4(.4f, .7f, 1.f, .5f) },
    { Color::PurpleTransparent,    glm::vec4(.5f, .1f, .5f, .5f) },
};

const glm::vec4& ColorPalette::Get(Color color)
{
    return colors.at(color);
}