#include "IParticleSystem.h"

IParticleSystem::IParticleSystem(std::size_t inMaxParticles)
    : maxParticles(inMaxParticles)
{
    particles.resize(maxParticles);
    for (auto& p : particles)
    {
        p.life = 0.0f;
    }
}
