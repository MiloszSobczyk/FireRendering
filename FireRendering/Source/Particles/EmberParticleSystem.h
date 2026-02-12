#pragma once

#include "IParticleSystem.h"
#include "Objects/Quad.h"
#include "Texture/Texture.h"
#include <memory>

class EmberParticleSystem : public IParticleSystem
{
public:
    explicit EmberParticleSystem(std::size_t inMaxParticles);

    void Emit(const glm::vec3& position) override;
    void Update(float deltaTime) override;
    void Render() override;
    void RenderUI();

private:
    std::shared_ptr<Quad> quadMesh;

    float spawnRadius = 0.25f;

    glm::vec3 colorStart = glm::vec3(0.25f, 0.03f, 0.0f);
    glm::vec3 colorMid = glm::vec3(0.7f, 0.3f, 0.05f);
    glm::vec3 colorEnd = glm::vec3(0.9f, 0.8f, 0.5f);
};