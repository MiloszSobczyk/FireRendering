#include "SmokeParticleSystem.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cstdlib>

SmokeParticleSystem::SmokeParticleSystem(std::size_t inMaxParticles)
	: IParticleSystem(inMaxParticles)
{
    quadMesh = std::make_shared<Quad>();
    noise1Texture = std::make_shared<Texture>();
    noise2Texture = std::make_shared<Texture>();
	noiseDetailTexture = std::make_shared<Texture>();

    noise1Texture->LoadFromFile("Resources/Textures/Noise03.png");
    noise2Texture->LoadFromFile("Resources/Textures/Noise05.png");
    noiseDetailTexture->LoadFromFile("Resources/Textures/Noise05.png");

    for (auto& p : particles)
    {
        p.life = 0.0f;
    }
}


void SmokeParticleSystem::Emit(const glm::vec3& position)
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
                (rand() % 100 - 50) / 300.0f,
                (rand() % 100) / 5.0f,
                (rand() % 100 - 50) / 300.0f
            );
            p.velocity = glm::normalize(velocity);

            p.color = glm::vec4(1.0f, 0.5f, 0.2f, 1.0f);
            p.life = life;

            break;
        }
    }
}

void SmokeParticleSystem::Update(float deltaTime)
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
            p.position += p.velocity * deltaTime;
            p.color.a = p.life / maxLife;
        }
    }
}

void SmokeParticleSystem::Render()
{
    auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Smoke);
    shader->Bind();

    shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    shader->SetUniformVec3f("u_cameraWorldPos", App::GetCameraWorldPosition());
    shader->SetUniformFloat("u_time", App::GetTime());

    noise1Texture->Bind(0);
    shader->SetUniformInt("u_noise1", 0);

    noise2Texture->Bind(1);
    shader->SetUniformInt("u_noise2", 1);

    noiseDetailTexture->Bind(2);
    shader->SetUniformInt("u_noiseDetail", 2);

    for (const auto& p : particles)
    {
        if (p.life <= 0.0f) continue;

        float normalizedLife = p.life / maxLife;
        float age = 1.0f - normalizedLife;

        float peakPoint = 0.4f;
        float alpha = 0.0f;

        if (age < peakPoint)
        {
            alpha = age / peakPoint;
        }
        else
        {
            alpha = 1.0f - ((age - peakPoint) / (1.0f - peakPoint));
        }

        alpha = glm::clamp(alpha, 0.0f, 1.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, p.position);
        model = glm::scale(model, glm::vec3(0.5f * normalizedLife));

        shader->SetUniformMat4f("u_modelMatrix", model);
        shader->SetUniformFloat("u_life", p.life);
        shader->SetUniformVec4f("u_color", glm::vec4(0.2f, 0.2f, 0.2f, alpha));

        quadMesh->Render();
    }

    shader->Unbind();
}
