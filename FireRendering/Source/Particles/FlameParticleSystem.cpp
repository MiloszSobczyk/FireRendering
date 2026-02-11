#include "FlameParticleSystem.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cstdlib>

FlameParticleSystem::FlameParticleSystem(std::size_t inMaxParticles)
    : IParticleSystem(inMaxParticles)
{
    quadMesh = std::make_shared<Quad>();
    particleTexture = std::make_shared<Texture>();
    dissolveTexture = std::make_shared<Texture>();

    particleTexture->LoadFromFile("Resources/Textures/Fire01.png");
    dissolveTexture->LoadFromFile("Resources/Textures/Voronoi01.png");

    for (auto& p : particles)
    {
        p.life = 0.0f;
    }
}

void FlameParticleSystem::Emit(const glm::vec3& position)
{
    for (auto& p : particles)
    {
        if (p.life <= 0.0f)
        {
            float life = minLife + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (maxLife - minLife);

            p.position = position;

            glm::vec3 velocity = glm::vec3(
                (rand() % 100 - 50) / 100.0f,
                (rand() % 100) / 40.0f,
                (rand() % 100 - 50) / 100.0f
            );
            p.velocity = glm::normalize(velocity);

            p.color = glm::vec4(1.0f, 0.5f, 0.2f, 1.0f);
            p.life = life;

            break;
        }
    }
}

void FlameParticleSystem::Update(float deltaTime)
{
    emitAccumulator += deltaTime * emitRate;

    while (emitAccumulator >= 1.0f)
    {
        Emit(glm::vec3(0.0f));
        emitAccumulator -= 1.0f;
    }

    for (auto& p : particles)
    {
        if (p.life > 0.0f)
        {
            p.life -= deltaTime;
            p.position += p.velocity * deltaTime;
            p.color.a = p.life / maxLife;
        }
    }
}

void FlameParticleSystem::Render()
{
    auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Billboard);
    shader->Bind();

    shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    shader->SetUniformVec3f("u_cameraWorldPos", App::GetCameraWorldPosition());
    shader->SetUniformFloat("u_time", App::GetTime());

    shader->SetUniformVec4f("u_color", glm::vec4(1.f, 0.5f, 0.2f, 1.f));
    shader->SetUniformFloat("u_dissolveStrength", 0.5f);
    shader->SetUniformFloat("u_tiling", 4.0f);
    shader->SetUniformFloat("u_edgeWidth", 0.1f);

    particleTexture->Bind(0);
    shader->SetUniformInt("u_texture", 0);

    dissolveTexture->Bind(1);
    shader->SetUniformInt("u_dissolveTex", 1);

    for (const auto& p : particles)
    {
        if (p.life <= 0.0f) continue;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, p.position);
        model = glm::scale(model, glm::vec3(0.5f * p.life / maxLife));

        shader->SetUniformMat4f("u_modelMatrix", model);

        quadMesh->Render();
    }

    shader->Unbind();
}
