#include "ScalingComponent.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

ScalingComponent::ScalingComponent()
    : scaling(1.0f, 1.0f, 1.0f)
{
}

ScalingComponent::ScalingComponent(const glm::vec3& scaling)
    : scaling(scaling)
{
}

glm::vec3 ScalingComponent::GetScaling() const
{
    return scaling;
}

void ScalingComponent::SetScaling(const glm::vec3& scaling)
{
    this->scaling = scaling;
}

void ScalingComponent::AddScaling(const glm::vec3& delta)
{
    this->scaling += delta;
}

glm::mat4x4 ScalingComponent::GetMatrix() const
{
    glm::mat4x4 matrix(1.0f);
    matrix = glm::scale(matrix, scaling);
    return matrix;
}

void ScalingComponent::RenderUI()
{
    ImGui::InputFloat3("Scaling", &scaling.x, "%.3f");
}
