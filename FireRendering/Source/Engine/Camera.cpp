#include "Camera.h"
#include <algorithm>

Camera::Camera(float distance, float fov, float nearPlane, float farPlane)
    : distance(distance),
    fov(fov),
    nearPlane(nearPlane),
    farPlane(farPlane),
    yaw(0.0f),
    pitch(0.0f)
{
}

void Camera::HandleInput()
{
    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
        float sensitivity = 0.005f;
        yaw -= delta.x * sensitivity;
        pitch += delta.y * sensitivity;

        pitch = std::clamp(pitch, -glm::half_pi<float>() + 0.01f, glm::half_pi<float>() - 0.01f);

        ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
    }

    if (io.MouseWheel != 0.0f)
    {
        distance -= io.MouseWheel * 2.0f;
        distance = std::clamp(distance, 1.0f, 500.0f);
    }
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::vec3 position = GetWorldPosition();
    glm::vec3 target(0.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    return glm::lookAtRH(position, target, up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspectiveRH(glm::radians(fov), aspect, nearPlane, farPlane);
}

glm::vec3 Camera::GetWorldPosition() const
{
    float x = distance * cosf(pitch) * sinf(yaw);
    float y = distance * sinf(pitch);
    float z = distance * cosf(pitch) * cosf(yaw);

    return glm::vec3(x, y, z);
}
