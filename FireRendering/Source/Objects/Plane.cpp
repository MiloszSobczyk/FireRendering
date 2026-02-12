#include "Plane.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

Plane::Plane()
	: Shape(ColorPalette::Get(Color::DarkBrown)), renderer(VertexDataType::PositionVertexData),
	translationComponent(std::make_shared<TranslationComponent>()), 
    scalingComponent(std::make_shared<ScalingComponent>())
{
    Update();
}

void Plane::Render()
{
    auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

    shader->Bind();
    shader->SetUniformVec4f("u_color", color);
    shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
    shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
    shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

    renderer.Render(GL_TRIANGLES);
    shader->Unbind();
}

void Plane::Update()
{
    std::vector<PositionVertexData> vertices = {
        { { -1.f, -.1f, -1.f, 1.0f } },
        { {  1.f, -.1f, -1.f, 1.0f } },
        { {  1.f, -.1f,  1.f, 1.0f } },
        { { -1.f, -.1f,  1.f, 1.0f } },
    };

    std::vector<unsigned int> indices = {
        // Top face
        0, 1, 2,
        2, 3, 0,

        // Bottom face
        0, 3, 2,
        2, 1, 0
    };

    renderer.SetVertices(vertices);
    renderer.SetIndices(indices);
}

std::shared_ptr<TranslationComponent> Plane::GetTranslationComponent()
{
	return translationComponent;
}

std::shared_ptr<ScalingComponent> Plane::GetScalingComponent()
{
	return scalingComponent;
}

glm::mat4x4 Plane::GetModelMatrix()
{
	return translationComponent->GetMatrix() * scalingComponent->GetMatrix();
}
