#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class ScalingComponent
{
private:
    glm::vec3 scaling;

public:
    ScalingComponent();
    ScalingComponent(const glm::vec3& scaling);

    glm::vec3 GetScaling() const;
    virtual void SetScaling(const glm::vec3& scaling);
    virtual void AddScaling(const glm::vec3& delta);
    glm::mat4x4 GetMatrix() const;

    void RenderUI();
};
