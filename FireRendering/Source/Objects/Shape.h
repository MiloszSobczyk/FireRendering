#pragma once

#include <string>
#include <imgui/imgui.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "Utils/ColorPalette.h"
#include "Objects/Components/Transformations.h"


class Shape
{
protected:
    glm::vec4 color;
    glm::mat4x4 initialMatrix;

public:
    Shape(glm::vec4 inColor = { 1.f, 1.f, 1.f, 1.f});
    virtual ~Shape() = default;

    virtual void Render() = 0;
    virtual void RenderUI() {};

    inline glm::vec4 GetColor() const { return color; }
    inline void SetColor(glm::vec4 color) { this->color = color; }

    virtual glm::mat4x4 GetModelMatrix();
    inline virtual void SetInitialMatrix(const glm::mat4x4 inInitialMatrix) { initialMatrix = inInitialMatrix; }
};