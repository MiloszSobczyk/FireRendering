#include "EmberParticleSystem.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cstdlib>

EmberParticleSystem::EmberParticleSystem(std::size_t inMaxParticles)
    : IParticleSystem(inMaxParticles)
{
    quadMesh = std::make_shared<Quad>();

    for (auto& p : particles)
    {
        p.life = 0.0f;
    }
}

void EmberParticleSystem::Emit(const glm::vec3& position)
{
    for (auto& p : particles)
    {
        if (p.life <= 0.0f)
        {
            float life = minLife + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (maxLife - minLife);

            float u = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            float v = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            float w = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

            float theta = 2.0f * glm::pi<float>() * u;
            float phi = acos(2.0f * v - 1.0f);

            float r = spawnRadius * cbrt(w);

            glm::vec3 offset;
            offset.x = r * sin(phi) * cos(theta);
            offset.y = r * sin(phi) * sin(theta);
            offset.z = r * cos(phi);

            p.position = position + offset;

            glm::vec3 velocity = glm::vec3(
                (rand() % 100 - 50) / 100.0f,
                (rand() % 100) / 50.0f,
                (rand() % 100 - 50) / 100.0f
            );
            p.velocity = glm::normalize(velocity) * 4.0f;

            p.velocity = glm::normalize(velocity);

            p.color = glm::vec4(1.0f, 0.5f, 0.2f, 1.0f);
            p.life = life;

            break;
        }
    }
}


void EmberParticleSystem::Update(float deltaTime)
{
    emitAccumulator += deltaTime * emitRate;

    while (emitAccumulator >= 1.0f)
    {
        Emit(startingPosition + glm::vec3(0.f, 2 * spawnRadius, 0.f));
        emitAccumulator -= 1.0f;
    }

    for (auto& p : particles)
    {
        if (p.life > 0.0f)
        {
            p.life -= deltaTime;

            glm::vec3 upwardForce = glm::vec3(0.0f, 2.5f, 0.0f);
            glm::vec3 wind = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 turbulence = glm::vec3(
                (rand() % 100 - 50) / 500.0f,
                (rand() % 100 - 50) / 100.0f,
                (rand() % 100 - 50) / 500.0f
            );
            p.velocity += (upwardForce + wind + turbulence) * deltaTime;
            p.velocity *= 0.99f;

            p.position += p.velocity * deltaTime;

            p.color.a = p.life / maxLife;
        }
    }
}

void EmberParticleSystem::Render()
{
    auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Ember);
    shader->Bind();

    shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    shader->SetUniformVec3f("u_cameraWorldPos", App::GetCameraWorldPosition());

    for (const auto& p : particles)
    {
        if (p.life <= 0.0f)
            continue;

        float normalizedLife = p.life / maxLife;
        float baseSize = 0.05f;
        float speed = glm::length(p.velocity);
        float stretch = glm::clamp(speed * 0.05f, 0.0f, 0.1f);

        glm::vec3 scaleVec(baseSize, baseSize + stretch, 1.0f);

        glm::mat4 model(1.0f);
        model = glm::translate(model, p.position);
        model = glm::scale(model, scaleVec);

        shader->SetUniformMat4f("u_modelMatrix", model);

        glm::vec3 velDir;
        if (glm::length(p.velocity) < 0.001f)
            velDir = glm::vec3(0.0f, 1.0f, 0.0f);
        else
            velDir = glm::normalize(p.velocity);

        shader->SetUniformVec3f("u_velocityDir", velDir);

        shader->SetUniformFloat("u_life", normalizedLife);

        quadMesh->Render();
    }

    shader->Unbind();
}

