#include "ParticleSystem.h"
#include "Managers/ShaderManager.h"
#include "Core/App.h"

ParticleSystem::ParticleSystem(std::size_t inMaxParticles)
	: maxParticles(inMaxParticles), quadMesh(std::make_shared<Quad>())
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
            float life =
                minLife +
                static_cast<float>(rand()) /
                static_cast<float>(RAND_MAX) *
                (maxLife - minLife);

            p.position = position;

            auto velocity = glm::vec3(
                (rand() % 100 - 50) / 100.0f,
                (rand() % 100) / 40.0f,
                (rand() % 100 - 50) / 100.0f
            );
            p.velocity = glm::normalize(velocity);

            p.life = life;
            p.color = glm::vec4(1.0f, 0.5f, 0.2f, 1.0f);

            break;
        }
    }
}


void ParticleSystem::Update(float dt)
{
    std::cout << "Updating particles with dt: " << dt << std::endl;

    emitAccumulator += dt * emitRate;

    while (emitAccumulator >= 1.0f)
    {
        Emit(glm::vec3(0.0f));
        emitAccumulator -= 1.0f;
    }

    for (auto& p : particles)
    {
        if (p.life > 0.0f)
        {
            p.life -= dt;
            p.position += p.velocity * dt;
            p.color.a = p.life / maxLife;
        }
    }
}

// TODO: Sehr wichtig! Right now every particle is drawn as a separate draw call, which is very inefficient. 
// We should batch them together in a single draw call using instancing or a dynamic vertex buffer.
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
            glm::vec3(0.05f * p.life / maxLife)
        );

        shader->SetUniformMat4f("u_modelMatrix", model);

		quadMesh->Render();
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
