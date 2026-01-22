#include "Line.h"

#include "Managers/ShaderManager.h"
#include "Core/App.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void Line::UpdateTransform()
{
    glm::vec3 dir = point2 - point1;
    float length = glm::length(dir);

    if (length < 1e-6f)
    {
        scalingComponent->SetScaling(glm::vec3(0.0f));
        return;
    }

    glm::vec3 dirNorm = glm::normalize(dir);
    glm::vec3 defaultDir = glm::vec3(1.0f, 0.0f, 0.0f);

    float dot = glm::dot(defaultDir, dirNorm);
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;

    float angle = glm::acos(dot);
    glm::vec3 axis = glm::cross(defaultDir, dirNorm);

    if (glm::length(axis) < 1e-6f)
    {
        axis = glm::vec3(0, 1, 0);
        angle = 0.0f;
    }
    else
    {
        axis = glm::normalize(axis);
    }

    rotationComponent->SetRotation(glm::angleAxis(angle, axis));
    translationComponent->SetTranslation(glm::vec4(point1, 1.0f));
    scalingComponent->SetScaling(glm::vec3(length, 1.0f, 1.0f));
}

Line::Line()
	: Shape(ColorPalette::Get(Color::Purple)), renderer(VertexDataType::PositionVertexData),
	translationComponent(std::make_shared<TranslationComponent>()),
	rotationComponent(std::make_shared<RotationComponent>()),
	scalingComponent(std::make_shared<ScalingComponent>()),
	point1(glm::vec3(0.f)), point2(glm::vec3(1.f, 0.f, 0.f))
{
    std::vector<PositionVertexData> vertices = {
		{{ 0.f, 0.f, 0.f, 1.f }}, 
		{{ 1.f, 0.f, 0.f, 1.f }}
	};

    std::vector<unsigned int> indices = { 0, 1 };

    renderer.SetVertices(vertices);
    renderer.SetIndices(indices);
}

void Line::Render()
{
	auto shader = ShaderManager::GetInstance().GetShader(ShaderName::Default);

	shader->Bind();
    shader->SetUniformVec4f("u_color", color);
	shader->SetUniformMat4f("u_viewMatrix", App::GetViewMatrix());
	shader->SetUniformMat4f("u_projectionMatrix", App::GetProjectionMatrix());
	shader->SetUniformMat4f("u_modelMatrix", GetModelMatrix());

	renderer.Render(GL_LINES);
	shader->Unbind();
}

void Line::SetPoint1(const glm::vec3& p1)
{
	point1 = p1;
	UpdateTransform();
}

void Line::SetPoint2(const glm::vec3& p2)
{
	point2 = p2;
	UpdateTransform();
}

std::shared_ptr<TranslationComponent> Line::GetTranslationComponent()
{
	return translationComponent;
}

std::shared_ptr<ScalingComponent> Line::GetScalingComponent()
{
	return scalingComponent;
}

std::shared_ptr<RotationComponent> Line::GetRotationComponent()
{
	return rotationComponent;
}

glm::mat4x4 Line::GetModelMatrix()
{
	return translationComponent->GetMatrix()
		* rotationComponent->GetMatrix()
		* scalingComponent->GetMatrix();
}
