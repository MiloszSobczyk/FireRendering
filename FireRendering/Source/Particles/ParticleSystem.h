#pragma once

#include "Particle.h"
#include "Engine/VertexLayout.h"

class ParticleSystem
{
public:
    ParticleSystem(std::size_t inMaxParticles);

    void Emit(const glm::vec3& position);
    void Update(float deltaTime);

    std::size_t WriteRenderData(std::vector<PositionColorVertexData> outBuffer, std::size_t maxCount) const;

private:
    std::vector<Particle> particles;

    std::size_t maxParticles;
};
