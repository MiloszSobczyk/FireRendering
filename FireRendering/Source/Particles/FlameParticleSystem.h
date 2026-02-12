#pragma once

#include "IParticleSystem.h"
#include "Objects/Quad.h"
#include "Texture/Texture.h"
#include <memory>

class FlameParticleSystem : public IParticleSystem
{
public:
    explicit FlameParticleSystem(std::size_t inMaxParticles);

    void Emit(const glm::vec3& position) override;
    void Update(float deltaTime) override;
    void Render() override;
    void RenderUI();

    bool addFlameRandomness = false;
    float coneRadius = 0.1f;
    float diskRadius = 0.05f;

private:
    std::shared_ptr<Quad> quadMesh;
    std::shared_ptr<Texture> particleTexture;
    std::shared_ptr<Texture> dissolveTexture;
    std::shared_ptr<Texture> dissolveTexture2;
    std::shared_ptr<Texture> dissolveTexture3;

	glm::vec3 colorStart = glm::vec3(1.0f, 0.2f, 0.0f);
	glm::vec3 colorMid = glm::vec3(1.0f, 1.0f, 0.2f);
	glm::vec3 colorEnd = glm::vec3(1.0f, 1.0f, 1.0f);
};