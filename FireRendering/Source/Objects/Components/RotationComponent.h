#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

class RotationComponent
{
private:
    glm::quat rotation;

public:
    RotationComponent();
    RotationComponent(const glm::quat& rotation);

    glm::quat GetRotation() const;
    virtual void SetRotation(const glm::quat& rotation);
    virtual void AddRotation(const glm::quat& delta);

    glm::mat4x4 GetMatrix() const;

    void RenderUI();
};
