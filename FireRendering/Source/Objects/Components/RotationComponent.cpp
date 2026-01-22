#include "RotationComponent.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

RotationComponent::RotationComponent()
    : rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
{
}

RotationComponent::RotationComponent(const glm::quat& rotation)
    : rotation(rotation)
{
}

glm::quat RotationComponent::GetRotation() const
{
    return rotation;
}

void RotationComponent::SetRotation(const glm::quat& rotation)
{
    this->rotation = rotation;
}

void RotationComponent::AddRotation(const glm::quat& delta)
{
    rotation = glm::normalize(delta * rotation);
}

glm::mat4x4 RotationComponent::GetMatrix() const
{
    return glm::toMat4(rotation);
}

void RotationComponent::RenderUI()
{
    // Display and edit rotation using Euler angles
    glm::vec3 euler = glm::eulerAngles(rotation);
    euler = glm::degrees(euler);

    if (ImGui::InputFloat3("Rotation (degrees)", &euler.x, "%.2f"))
    {
        rotation = glm::quat(glm::radians(euler));
    }
}
