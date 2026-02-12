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

private:
    std::shared_ptr<Quad> quadMesh;

    float spawnRadius = 0.25f;
};