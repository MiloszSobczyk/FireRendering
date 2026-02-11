#pragma once

#include <memory>
#include <vector>

#include "Particle.h"

class IParticleSystem
{
public:
    virtual ~IParticleSystem() = default;

    virtual void Emit(const glm::vec3& position) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    inline std::size_t GetMaxParticles() const { return maxParticles; }

protected:
    explicit IParticleSystem(std::size_t inMaxParticles);

    std::vector<Particle> particles;

    std::size_t maxParticles;

    float emitRate = 100.0f;
    float emitAccumulator = 0.0f;

    float minLife = 0.8f;
    float maxLife = 1.6f;
};
