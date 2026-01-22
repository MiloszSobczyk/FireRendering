#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

class Camera
{
private:
    float distance;
    float fov;
    float nearPlane;
    float farPlane;
    float yaw;
    float pitch;
    float aspect;

public:
    Camera(float distance = 100.0f, float fov = 45.0f, float nearPlane = 0.1f, float farPlane = 1000.0f);

    void HandleInput();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    glm::vec3 GetWorldPosition() const;

    inline void SetAspect(float aspect) { this->aspect = aspect; }
};
