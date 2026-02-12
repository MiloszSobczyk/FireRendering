#pragma once

#include "IParticleSystem.h"
#include "Objects/Quad.h"
#include "Texture/Texture.h"
#include <memory>

class SmokeParticleSystem : public IParticleSystem
{
public:
    explicit SmokeParticleSystem(std::size_t inMaxParticles);

    void Emit(const glm::vec3& position) override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    std::shared_ptr<Quad> quadMesh;
    std::shared_ptr<Texture> particleTexture;
    std::shared_ptr<Texture> dissolveTexture;
};