#include "ParticleSystem.h"
#include <Managers/ShaderManager.h>
#include "Core/App.h"

ParticleSystem::ParticleSystem(std::size_t inMaxParticles)
	: maxParticles(inMaxParticles), cubeMesh(std::make_shared<Cube>())
{
    particles.resize(maxParticles);

    for (auto& p : particles)
    {
        p.life = 0.0f;
    }
}

void ParticleSystem::Emit(const glm::vec3& position)
{
    for (auto& p : particles)
    {
        if (p.life <= 0.0f)
        {
            p.position = position;
            p.velocity = glm::vec3(
                (rand() % 100 - 50) / 50.0f,
                (rand() % 100) / 50.0f,
                0.0f
            );
            p.life = 1.0f;
            p.color = glm::vec4(1.0f, 0.5f, 0.2f, 1.0f);
            break;
        }
    }
}

void ParticleSystem::Update(float dt)
{
	std::cout << "Updating particles with dt: " << dt << std::endl;
    for (auto& p : particles)
    {
        if (p.life > 0.0f)
        {
            p.life -= dt;
            p.position += p.velocity * dt;
            p.color.a = p.life;
        }
    }
    Emit(glm::vec3(0.f));
}

void ParticleSystem::Render() const
{
    auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

    shader->Bind();
    shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    shader->SetUniformVec4f("u_color", glm::vec4(1.f));
    
    for (const auto& p : particles)
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            p.position
        );

        model = glm::scale(
            model,
            glm::vec3(0.05f)
        );
        shader->SetUniformMat4f("u_modelMatrix", model);

		cubeMesh->Render();
    }

    shader->Unbind();
}

std::size_t ParticleSystem::WriteRenderData(std::vector<PositionColorVertexData> outBuffer, std::size_t maxCount) const
{
    std::size_t count = 0;

    for (const auto& p : particles)
    {
        if (p.life > 0.0f && count < maxCount)
        {
            outBuffer[count++] =
            {
                glm::vec4(p.position, 1.0f),
                p.color
            };
        }
    }

    return count;
}
