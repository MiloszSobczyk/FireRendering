#include "FlameParticleSystem.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cstdlib>
#include <imgui/implot_demo.cpp>
#include <glm/gtx/quaternion.hpp>

FlameParticleSystem::FlameParticleSystem(std::size_t inMaxParticles)
    : IParticleSystem(inMaxParticles)
{
    quadMesh = std::make_shared<Quad>();
    particleTexture = std::make_shared<Texture>();
    dissolveTexture = std::make_shared<Texture>();
    dissolveTexture2 = std::make_shared<Texture>();
    dissolveTexture3 = std::make_shared<Texture>();

    particleTexture->LoadFromFile("Resources/Textures/Fire01.png");
    dissolveTexture->LoadFromFile("Resources/Textures/Noise02.png");
    dissolveTexture2->LoadFromFile("Resources/Textures/Noise03.png");
    dissolveTexture3->LoadFromFile("Resources/Textures/Noise06.png");

    for (auto& p : particles)
    {
        p.life = 0.0f;
    }
}

float randf(float a, float b)
{
    return a + (b - a) * (rand() / float(RAND_MAX));
}


glm::vec3 randomInCone(float radius)
{
    glm::vec3 dir = glm::normalize(glm::vec3(
        randf(-0.5f, 0.5f),
        1.0f,
        randf(-0.5f, 0.5f)
    ));
    return dir * randf(0, radius);
}


glm::vec3 randomInDisk(float radius)
{
    float angle = randf(0, 2 * PI);
    float r = sqrt(randf(0, 1)) * radius;
    return glm::vec3(cos(angle) * r, 0, sin(angle) * r);
}

void FlameParticleSystem::Emit(const glm::vec3& position)
{
    for (auto& p : particles)
    {
        if (p.life <= 0.0f)
        {
            float life = minLife + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (maxLife - minLife);

            p.position = position + randomInCone(0.2f) + randomInDisk(0.05f);

            glm::vec3 velocity = glm::vec3(
                (rand() % 100 - 50) / 100.0f,
                (rand() % 100) / 10.0f,
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
        Emit(startingPosition);
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
    auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Fire);
    shader->Bind();

    shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    shader->SetUniformVec3f("u_cameraWorldPos", App::GetCameraWorldPosition());
    shader->SetUniformFloat("u_time", App::GetTime());

    dissolveTexture->Bind(0);
    shader->SetUniformInt("u_dissolveTexture", 0);

    dissolveTexture2->Bind(1);
    shader->SetUniformInt("u_dissolveTexture2", 1);

    dissolveTexture3->Bind(2);
    shader->SetUniformInt("u_dissolveTexture3", 2);

    for (const auto& p : particles)
    {
        if (p.life <= 0.0f) continue;

        float rx = randf(-2.f * PI, 2.0f * PI);
        float ry = randf(-2.f * PI, 2.0f * PI);
        float rz = randf(-2.f * PI, 2.0f * PI);

        glm::quat q = glm::quat(glm::vec3(rx, ry, rz));
        glm::mat4 rotation = glm::toMat4(q);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, p.position);
        model = model * rotation;
        model = glm::scale(model, glm::vec3(0.5f * p.life / maxLife));

        shader->SetUniformMat4f("u_modelMatrix", model);
        shader->SetUniformFloat("u_life", p.life);
        if(addFlameRandomness)
            shader->SetUniformFloat("u_random", randf(-2.f * PI, 2.0f * PI));

        quadMesh->Render();
    }

    shader->Unbind();
}
