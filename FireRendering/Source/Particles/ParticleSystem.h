#pragma once

#include "Particle.h"
#include "Engine/VertexLayout.h"
#include <memory>
#include "Objects/Cube.h"

class ParticleSystem
{
public:
    ParticleSystem(std::size_t inMaxParticles);

    void Emit(const glm::vec3& position);
    void Update(float deltaTime);
    void Render() const;

    std::size_t WriteRenderData(std::vector<PositionColorVertexData> outBuffer, std::size_t maxCount) const;

private:
    std::vector<Particle> particles;
    std::shared_ptr<Cube> cubeMesh;

    std::size_t maxParticles;
};
