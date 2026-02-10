#include "Quad.h"

#include "Core/App.h"
#include "Managers/ShaderManager.h"
#include "Utils/ColorPalette.h"

#include <glm/gtc/matrix_transform.hpp>

Quad::Quad()
	: Shape(ColorPalette::Get(Color::Red)), renderer(VertexDataType::PositionVertexData),
	translationComponent(std::make_shared<TranslationComponent>()), 
	scalingComponent(std::make_shared<ScalingComponent>()), 
	rotationComponent(std::make_shared<RotationComponent>())
{
	Update();
}

void Quad::Render()
{
	//auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

	//shader->Bind();
	//shader->SetUniformVec4f("u_color", color);
	//shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
	//shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
	//shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

	renderer.Render(GL_TRIANGLES);

	//shader->Unbind();
}

void Quad::Update()
{
	std::vector<PositionVertexData> vertices = {
		{{ -0.5f, -0.5f, 0.f, 1.f }},
		{{  0.5f, -0.5f, 0.f, 1.f }},
		{{  0.5f,  0.5f, 0.f, 1.f }},
		{{ -0.5f,  0.5f, 0.f, 1.f }}
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	renderer.SetVertices(vertices);
	renderer.SetIndices(indices);
}

std::shared_ptr<TranslationComponent> Quad::GetTranslationComponent()
{
	return translationComponent;
}

std::shared_ptr<ScalingComponent> Quad::GetScalingComponent()
{
	return scalingComponent;
}

std::shared_ptr<RotationComponent> Quad::GetRotationComponent()
{
	return rotationComponent;
}

glm::mat4x4 Quad::GetModelMatrix()
{
	return translationComponent->GetMatrix()
		* rotationComponent->GetMatrix()
		* scalingComponent->GetMatrix()
		* initialMatrix;
}
